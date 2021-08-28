#include "server/ddmatch_postprocessor.h"
#include "common/utils.h"

namespace nlper {

int DDMatchPostprocessor::init(const ServerConfig& config) {
    if (!config.ddmatch_postproc_plugin().has_type()) {
        FATAL_LOG("ReqPostprocPluginConfig.type unset!");
        return -1;
    }
    if (!config.ddmatch_postproc_plugin().has_name()) {
        FATAL_LOG("ReqPostprocPluginConfig.name unset!");
        return -1;
    }
    init_base(config.ddmatch_postproc_plugin().name());
    return 0;
}

int DDMatchPostprocessor::destroy() {
    return 0;
}

// ddmatch后处理
int DDMatchPostprocessor::process(NlperResult& nlp_result, Json::Value& parameters, std::string& output) {
    for (size_t i = 0; i < nlp_result.match_items.size(); i++) {
        Json::Value result_item;
        result_item["aimd"] = parameters["aimd"].asString();
        result_item["candd"] = nlp_result.match_items[i].query;
        result_item["confidence"] = nlp_result.match_items[i].confidence;
        output = json_dumps(result_item);
    }
    
    return 0;
}

} // namespace nlper
