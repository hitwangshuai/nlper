#include "matching/semantic/semtopic_qd_sim.h"
#include <exception>

namespace nlper {

SemtopicQDSimilarity::SemtopicQDSimilarity(){
    _p_semtopic_pack = NULL;
}

SemtopicQDSimilarity::~SemtopicQDSimilarity(){
    destroy();
}

int SemtopicQDSimilarity::init(DualDictWrapper* dict, const MatchingConfig& matching_config) {
    _p_semtopic_pack = (SemtopicPack*)dict->get_dict();
    DEBUG_LOG("_output_num:%d; _feature_weight:%f", get_output_num(), get_feature_weight());

    return 0;
}

int SemtopicQDSimilarity::destroy() {
    return 0;
}

int SemtopicQDSimilarity::compute_similarity(const std::vector<AnalysisItem>& analysis_items, MatchResult& candidates) {
    if (analysis_items.size() < 1) {
        return -1;
    }
     
    for (size_t i = 0; i < candidates.size(); ++i) {
       float sim = semtopic::SemanticMatching::twe_based_similarity(analysis_items[0].topics_basic.tokens,
               candidates[i].analysis_item.topics_basic.lda_spase_topic_dist, *(_p_semtopic_pack->twe)); 
       //float sim = semtopic::SemanticMatching::likelihood_based_similarity(analysis_items[0].topics_basic.tokens,
       //        candidates[i].analysis_item.topics_basic.lda_spase_topic_dist, _p_semtopic_pack->lda_engine->get_model());
       DEBUG_LOG("qd sim %f", sim);
       // 权重化
       sim = sim * get_feature_weight();
       DEBUG_LOG("qd_sim_weighted %f", sim);
       candidates[i].features.emplace_back(sim);
    }

    return 0;
}

} // namespace nlper
