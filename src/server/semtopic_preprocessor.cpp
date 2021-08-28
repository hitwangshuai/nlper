#include "server/semtopic_preprocessor.h"
#include "common/utils.h"

namespace nlper {

int SemtopicPreprocessor::init(const ReqPreprocPluginConfig& config) {
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

int SemtopicPreprocessor::destroy() {
    return 0;
}

// semtopic预处理
int SemtopicPreprocessor::process(brpc::Controller* cntl, Json::Value& parameters, std::string& str_nlper_input) {
    if (!parameters.isMember("text")) {
        FATAL_LOG("semtopic Query field text is required.");
        return 1;
    }
    
    Json::Value json_analysis_input;
    Json::Value json_analysis_info;
    Json::Value::Members mem = parameters.getMemberNames();
    for (Json::Value::Members::iterator it = mem.begin(); it != mem.end(); ++it) {
        if (*it == "text") {
            Json::Value analysis_item;
            if (parameters.isMember("id")) {
                analysis_item["id"] = parameters["id"].asString();
            }
            analysis_item["query"] = parameters["text"].asString();
            analysis_item["type"] = 0;
            json_analysis_input["aim_item"] = analysis_item;
		} else {
            json_analysis_info[*it] = parameters[*it];
        }
    }
    json_analysis_input["info"] = json_analysis_info;
    str_nlper_input = json_dumps(json_analysis_input);

    return 0;
}

} // namespace nlper
