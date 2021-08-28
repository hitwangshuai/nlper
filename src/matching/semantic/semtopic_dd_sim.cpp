#include "matching/semantic/semtopic_dd_sim.h"
#include <exception>

namespace nlper {

SemtopicDDSimilarity::SemtopicDDSimilarity(){
    _p_semtopic_pack = NULL;
}

SemtopicDDSimilarity::~SemtopicDDSimilarity(){
    destroy();
}

int SemtopicDDSimilarity::init(DualDictWrapper* dict, const MatchingConfig& matching_config) {
    _p_semtopic_pack = (SemtopicPack*)dict->get_dict();
    DEBUG_LOG("_output_num:%d; _feature_weight:%f", get_output_num(), get_feature_weight());

    return 0;
}

int SemtopicDDSimilarity::destroy() {
    return 0;
}

int SemtopicDDSimilarity::compute_similarity(const std::vector<AnalysisItem>& analysis_items, MatchResult& candidates) {
    if (analysis_items.size() < 1) {
        return -1;
    }

    for (size_t i = 0; i < candidates.size(); ++i) {
        // 这里需要拷贝,下游接口要修改
        std::vector<float> dist1 = analysis_items[0].topics_basic.lda_dense_topic_dist;
        std::vector<float> dist2 = candidates[i].analysis_item.topics_basic.lda_dense_topic_dist;
        // 得分小代表分布差异越小,对应的相似度越大
        float sim = 1.0 - semtopic::SemanticMatching::jensen_shannon_divergence(dist1, dist2);
        //float sim = 1.0 - semtopic::SemanticMatching::hellinger_distance(dist1, dist2);
        DEBUG_LOG("sim %f", sim);

        // 权重化
        sim = sim * get_feature_weight();
        DEBUG_LOG("dd_sim_weighted %f", sim);
        candidates[i].features.emplace_back(sim);
    }

    return 0;
}

} // namespace nlper

