#include "strategy/ddmatch_strategy.h"
#include "common/utils.h"

namespace nlper {

DDMatchStrategy::DDMatchStrategy() {}

DDMatchStrategy::~DDMatchStrategy() {
    release_resource();
}

// 创建线程资源
int DDMatchStrategy::create_resource(DictManager& dm, const std::string& conf_path) {
    DictMap* dict_map = dm.get_dict();
    if (dict_map == NULL) {
        FATAL_LOG("get_dict error");
        return -1;
    }
    NlperStrategyConfig nlper_config;
    load_config_from_file(conf_path + std::string("/ddmatch_main.conf"), nlper_config);

    std::string analysis_conf = conf_path + nlper_config.analysis_config();
    if (_analysis.init(dict_map, analysis_conf) != 0) {
        FATAL_LOG("ddmatch analysis module init error");
        return -1;
    }
    
	std::string match_conf = conf_path + nlper_config.match_config();
    if (_match.init(dict_map, match_conf) != 0) {
        FATAL_LOG("ddmatch match module init error");
        return -1;
    }
    TRACE_LOG("ddmatch init success");
    return 0;
}

int DDMatchStrategy::release_resource() {
    _analysis.destroy();
    _match.destroy();
    return 0;
}

// 总策略入口
int DDMatchStrategy::run_strategy(const std::string& analysis_input, NlperResult& result) {
    // 文本分析
    if (_analysis.run_strategy(analysis_input, result.analysis_items) != 0) {
        FATAL_LOG("ddmatch analysis module process error");
        return -1;
    }
	
    // 匹配计算
    if (_match.run_strategy(result.analysis_items, result) != 0) {
        FATAL_LOG("ddmatch match module process error");
        return -1;
    }
    
    return 0;
}

}
