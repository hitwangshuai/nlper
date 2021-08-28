#include "server/qdmatch_postprocessor.h"
#include "common/utils.h"

namespace nlper {

int QDMatchPostprocessor::init(const ServerConfig& config) {
    if (!config.qdmatch_postproc_plugin().has_type()) {
        FATAL_LOG("ReqPostprocPluginConfig.type unset!");
        return -1;
    }
    if (!config.qdmatch_postproc_plugin().has_name()) {
        FATAL_LOG("ReqPostprocPluginConfig.name unset!");
        return -1;
    }
    init_base(config.qdmatch_postproc_plugin().name());
    return 0;
}

int QDMatchPostprocessor::destroy() {
    return 0;
}

// qdmatch后处理
int QDMatchPostprocessor::process(NlperResult& nlp_result, Json::Value& parameters, std::string& output) {
    for (size_t i = 0; i < nlp_result.match_items.size(); i++) {
        Json::Value result_item;
        result_item["aimq"] = parameters["aimq"].asString();
        result_item["candd"] = nlp_result.match_items[i].query;
        result_item["confidence"] = nlp_result.match_items[i].confidence;
        output = json_dumps(result_item);
    }
    
    return 0;
}

} // namespace nlper
