#include "strategy/semtopic_strategy.h"
#include "common/utils.h"

namespace nlper {

SemtopicStrategy::SemtopicStrategy() {}

SemtopicStrategy::~SemtopicStrategy() {
    release_resource();
}

// 创建线程资源
int SemtopicStrategy::create_resource(DictManager& dm, const std::string& conf_path) {
    DictMap* dict_map = dm.get_dict();
    if (dict_map == NULL) {
        FATAL_LOG("get_dict error");
        return -1;
    }
    NlperStrategyConfig nlper_config;
    load_config_from_file(conf_path + std::string("/semtopic_main.conf"), nlper_config);

    std::string analysis_conf = conf_path + nlper_config.analysis_config();
    if (_analysis.init(dict_map, analysis_conf) != 0) {
        FATAL_LOG("semtopic analysis module init error");
        return -1;
    }
    
    TRACE_LOG("semtopic init success");
    return 0;
}

int SemtopicStrategy::release_resource() {
    _analysis.destroy();
    return 0;
}

// 总策略入口
int SemtopicStrategy::run_strategy(const std::string& analysis_input, NlperResult& result) {
    // 文本分析
    if (_analysis.run_strategy(analysis_input, result.analysis_items) != 0) {
        FATAL_LOG("semtopic analysis module process error");
        return -1;
    }
    return 0;
}

}
