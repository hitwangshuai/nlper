#include "server/semtopic_postprocessor.h"
#include "common/utils.h"

namespace nlper {

int SemtopicPostprocessor::init(const ServerConfig& config) {
    if (!config.semtopic_postproc_plugin().has_type()) {
        FATAL_LOG("ReqPostprocPluginConfig.type unset!");
        return -1;
    }
    if (!config.semtopic_postproc_plugin().has_name()) {
        FATAL_LOG("ReqPostprocPluginConfig.name unset!");
        return -1;
    }
    init_base(config.semtopic_postproc_plugin().name());
    return 0;
}

int SemtopicPostprocessor::destroy() {
    return 0;
}

// semtopic后处理
int SemtopicPostprocessor::process(NlperResult& nlp_result, Json::Value& parameters, std::string& output) {
    for (size_t i = 0; i < nlp_result.analysis_items.size(); i++) {
        Json::Value result_item;
        result_item["input"] = parameters["text"].asString();
        std::vector<semtopic::Topic>& lda_doc_topic_dist = nlp_result.analysis_items[i].topics_basic.lda_spase_topic_dist;
        
        DEBUG_LOG("semtopic lda_doc_topic_dist size=%d", lda_doc_topic_dist.size());
        
        Json::Value lda_dists = Json::Value(Json::arrayValue);
        for (size_t j = 0; j < lda_doc_topic_dist.size() && j < 20; j++) {
            semtopic::Topic& topic = lda_doc_topic_dist[j];
            Json::Value dist;
            dist["tid"] = topic.tid;
            dist["prob"] = topic.prob;
            lda_dists.append(dist);
        }
        result_item["output_lda_dists"] = lda_dists;
        
        output = json_dumps(result_item);
    }

    return 0;
}

} // namespace nlper
