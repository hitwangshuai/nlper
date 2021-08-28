#include "server/qdmatch_preprocessor.h"
#include "common/utils.h"

namespace nlper {

int QDMatchPreprocessor::init(const ReqPreprocPluginConfig& config) {
    if (!config.has_type()) {
        FATAL_LOG("ReqPreprocPluginConfig.type unset!");
        return -1;
    }
    if (!config.has_name()) {
        FATAL_LOG("ReqPreprocPluginConfig.name unset!");
        return -1;
    }
    init_base(config.name());
    return 0;
}

int QDMatchPreprocessor::destroy() {
    return 0;
}

// qdmatch预处理
int QDMatchPreprocessor::process(brpc::Controller* cntl, Json::Value& parameters, std::string& str_nlper_input) {
    if (!parameters.isMember("aimq")) {
        FATAL_LOG("qdmatch Query field aimq is required.");
        return 1;
    }
    if (!parameters.isMember("candd")) {
        FATAL_LOG("qdmatch Query field candd is required.");
        return 1;
    }
    
    Json::Value json_analysis_input;
    Json::Value json_analysis_info;
    Json::Value::Members mem = parameters.getMemberNames();
    for (Json::Value::Members::iterator it = mem.begin(); it != mem.end(); ++it) {
        if (*it == "aimq") {
            Json::Value analysis_item;
            analysis_item["query"] = parameters["aimq"].asString();
            analysis_item["type"] = 0;
            json_analysis_input["aim_item"] = analysis_item;
		} else if (*it == "candd") {
            Json::Value analysis_item;
            analysis_item["query"] = parameters["candd"].asString();
            analysis_item["type"] = 1;
			Json::Value analysis_items;
			analysis_items.append(analysis_item);
            json_analysis_input["cand_items"] = analysis_items;
		} else {
            json_analysis_info[*it] = parameters[*it];
        }
    }
    json_analysis_input["info"] = json_analysis_info;
    str_nlper_input = json_dumps(json_analysis_input);

    return 0;
}

} // namespace nlper
