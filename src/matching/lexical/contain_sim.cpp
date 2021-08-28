#include "matching/lexical/contain_sim.h"

namespace nlper {

ContainSimilarity::ContainSimilarity() {
}

ContainSimilarity::~ContainSimilarity() {
    destroy();
}
 
int ContainSimilarity::init(DualDictWrapper* dict, const MatchingConfig& matching_config) {
    return 0;
}

int ContainSimilarity::destroy() {
    return 0;
}

// 判断analysis中query是否与召回query存在包含的关系
bool ContainSimilarity::contain(const AnalysisItem& analysis_item, const MatchItem& match_item) {
    if (analysis_item.query.length() < 4) {
        return false;
    }
    if (match_item.analysis_item.query.length() < 4) {
        return false;
    }
    if (analysis_item.query.find(match_item.analysis_item.query) != std::string::npos) {
        return true;
    }
    if (match_item.analysis_item.query.find(analysis_item.query) != std::string::npos) {
        return true;
    }
    return false;
}

int ContainSimilarity::compute_similarity(const std::vector<AnalysisItem>& analysis_items, MatchResult& candidates) {
    if (analysis_items.size() < 1) {
        return -1;
    }
    for (int i = 0; i < candidates.size(); i++) {
        bool fea_value = contain(analysis_items[0], candidates[i]);
        // 如果存在包含关系，特征值为1,否则为0
        float sim = 0.0;
		if (fea_value) {
			sim = 1.0;
		}
        DEBUG_LOG("contain =  %d", fea_value);
		// 权重化
		sim = sim * get_feature_weight();
		DEBUG_LOG("contain_weighted =  %d", sim);
		candidates[i].features.emplace_back(sim);
    }

    return 0;
}

} // namespace nlper
