#include "analysis/analysis_strategy.h"
#include "google/protobuf/text_format.h"
#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "dict/dict_manager.h"
#include "dict/dict_adapter.h"
#include "common/utils.h"
#include "common/plugin_factory.h"

namespace nlper {

AnalysisStrategy::AnalysisStrategy() {
}

AnalysisStrategy::~AnalysisStrategy() {
    if (destroy() != 0) {
        FATAL_LOG("release analysis stategy error");
    }
}

int AnalysisStrategy::init(DictMap* dict_map, const std::string& analysis_conf){
    _dict_map = dict_map;
    AnalysisConfig analysis_config;
    if (load_config_from_file(analysis_conf, analysis_config) != 0) {
        return -1;
    }
    for (int i = 0; i < analysis_config.analysis_method_size(); i++) {
        AnalysisMethodConfig analysis_method_config = analysis_config.analysis_method(i);
        const std::string& method_type = analysis_method_config.type();
        std::string dict_name_strs("");
        bool need_dict = false;
        if (analysis_method_config.has_using_dict_name()) {
            dict_name_strs = analysis_method_config.using_dict_name();
            need_dict = true;
        }

        // 创建Analysis方法
        AnalysisMethodInterface* tmp_method = 
                static_cast<AnalysisMethodInterface*>(PLUGIN_FACTORY.create_plugin(method_type));
        if (tmp_method == NULL) {
            FATAL_LOG("can't find method_name:%s", method_type.c_str());
            return -1;
        }

        // 根据配置的词典，进行初始化，未配置词典则使用NULL
        int ret = 0;
        if (need_dict) {
            std::vector<std::string> dict_names;
            split_string(dict_name_strs, dict_names, ",");
            std::vector<DualDictWrapper*> using_dicts;
            for (std::vector<std::string>::iterator it = dict_names.begin(); it != dict_names.end(); it++) {
                std::string dict_name = *it;
                if (_dict_map->count(dict_name) < 1) {
                    FATAL_LOG("using dict %s that does not exist", dict_name.c_str());
                    return -1;
                }
                using_dicts.emplace_back((*_dict_map)[dict_name]);
            }
            ret = tmp_method->init(using_dicts, analysis_method_config);
        } else {
            DualDictWrapper* dict = NULL;
            ret = tmp_method->init(dict, analysis_method_config); 
        }

        if (ret != 0) {
            FATAL_LOG("init method error %s", dict_name_strs.c_str());
            return -1;
        }
        TRACE_LOG("create method %s success", method_type.c_str());
        _method_list.emplace_back(tmp_method);
    }
    return 0;
}

// 从json串，构建出analysis的结果形式
int AnalysisStrategy::json_parser(const std::string& analysis_input_str, std::vector<AnalysisItem>& analysis_items){
    Json::Reader reader;
    Json::Value analysis_input;
    if (!reader.parse(analysis_input_str, analysis_input))
    {
        FATAL_LOG("analysis_input_str is not json style");
        return -1;
    }

    if (analysis_input.type() != Json::objectValue)
    {
        TRACE_LOG("analysis_input data is not json style");
        return -1;
    }

	// 目标分析项输入:必传
    if (analysis_input.isMember("aim_item") && !analysis_input["aim_item"].isNull())
    {
		AnalysisItem analysis_item;
        int ret = json_to_analysis_item(analysis_input["aim_item"], analysis_item);
        if (ret != 0)
        {
            FATAL_LOG("json_to_analysis_item failed!");
            return -1;
        }
		analysis_items.emplace_back(analysis_item);
    } else {
		FATAL_LOG("aim_item is not analysis_input's memeber");
		return -1;
    }
	
    // 候选分析项输入:可选
	if (analysis_input.isMember("cand_items") && !analysis_input["cand_items"].isNull()) {
		int ret = json_to_analysis_items(analysis_input["cand_items"], analysis_items);
		if (ret != 0) {
			FATAL_LOG("json_to_analysis_items failed!");
			return -1;
		}
	}
    TRACE_LOG(" total analysis_items size: %d", analysis_items.size());
	
    return 0;
}

// 线程参数结构体
typedef struct {
    int thread_id;
    AnalysisMethodInterface* method;
    std::vector<AnalysisItem>* analysis_items;
} analysis_thread_arg;

void* analysis_thread_worker(void *arg) {
    analysis_thread_arg tharg = *(analysis_thread_arg*) arg;
    std::vector<AnalysisItem>& analysis_items = *(tharg.analysis_items);
    
    if (tharg.method->method_process(analysis_items) != 0) {
        FATAL_LOG("method_process %s error at thread: %d", (tharg.method->get_method_name()).c_str(), tharg.thread_id);
        pthread_exit(NULL);
    }
    //TRACE_LOG("method_process %s sucess at thread: %d", (tharg.method->get_method_name()).c_str(), tharg.thread_id);
    pthread_exit(NULL);
}

// 分析策略入口
int AnalysisStrategy::run_strategy(const std::string& analysis_input_str, std::vector<AnalysisItem>& analysis_items){
    float time_use = 0; // 毫秒
    struct timeval start;
    struct timeval end;
    gettimeofday(&start, NULL);
    
    // 将每个待分析项实例化到analysis_items
    if (json_parser(analysis_input_str, analysis_items) != 0) {
        FATAL_LOG("analysis_input json parser failed!");
        return -1;
    }
    
    // 分析方法拓扑分配
    int max_level = 0;
    std::map<int, std::vector<AnalysisMethodInterface*>> level_methods;
    std::vector<AnalysisMethodInterface*>::iterator it;
    for (it = _method_list.begin(); it != _method_list.end(); ++it) {
        int method_level = (*it)->get_method_level();
        if (level_methods.find(method_level) == level_methods.end()) {
            std::vector<AnalysisMethodInterface*> methods;
            level_methods[method_level] = methods;
        }
        level_methods[method_level].emplace_back(*it);
        if (max_level < method_level) {
            max_level = method_level;
        }
    }
    
    // 分析方法执行:同级并行,不同级串行
    for (int i = 0; i <= max_level; i++) {
        if (level_methods.find(i) == level_methods.end() 
                || level_methods[i].size() == 0) {
            continue;
        }
        
        // 资源初始化 
        std::vector<AnalysisMethodInterface*>& methods = level_methods[i];
        int thread_num = methods.size();
        std::map<int, analysis_thread_arg> thread_args;
        for (int j = 0; j < thread_num; j++) {
            analysis_thread_arg tharg;
            tharg.thread_id = j;
            tharg.method = methods[j];
            tharg.analysis_items = &analysis_items;
            thread_args[j] = tharg;
        }
        
        // 线程执行
        pthread_t ids[thread_num];
        for (int j = 0; j < thread_num; j++) {
            pthread_create(&ids[j], NULL, analysis_thread_worker, (void*) &(thread_args[j]));
        }
        for (int j = 0; j < thread_num; j++) {
            pthread_join(ids[j], NULL);
        }
    }

    // 分析时间打印
    gettimeofday(&end, NULL);
    time_use = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;
    DEBUG_LOG("analysis_time=%.2fms", time_use);
    return 0;
}

int AnalysisStrategy::destroy()
{
    std::vector<AnalysisMethodInterface*>::iterator it;
    int i = 0;
    for (it = _method_list.begin(); it != _method_list.end(); ++it, ++i) {
        if ((*it)->destroy() != 0) {
            FATAL_LOG("analysis_method %s destroy error", ((*it)->get_method_name()).c_str());
            return -1;
        }
        delete *it;
    }
    _method_list.clear();
    return 0;
}

} // namespace nlper
