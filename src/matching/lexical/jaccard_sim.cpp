#include "matching/lexical/jaccard_sim.h"

namespace nlper {

JaccardSimilarity::JaccardSimilarity(){
}

JaccardSimilarity::~JaccardSimilarity(){
    destroy();
}

int JaccardSimilarity::init(DualDictWrapper* dict, const MatchingConfig& matching_config) {
    return 0;
}

int JaccardSimilarity::destroy() {
    return 0;
}

// 计算两个字符按传的jaccard相似度
float JaccardSimilarity::jaccard_similarity(const std::string& sent1, const std::string& sent2) {
    std::vector<std::string> chars_a;
    int ret = utf8_to_char(sent1, chars_a);
    if (ret != 0 || chars_a.size() == 0) {
        return 0.0;
    }
    std::vector<std::string> chars_b;
    ret = utf8_to_char(sent2, chars_b);
    if (ret != 0 || chars_b.size() == 0) {
        return 0.0;
    }

    std::sort(chars_a.begin(), chars_a.end());
    std::sort(chars_b.begin(), chars_b.end());

    // 交集
    std::vector<std::string> words_intersect;
    std::set_intersection(chars_a.begin(), chars_a.end(), chars_b.begin(), chars_b.end(),
            std::back_inserter(words_intersect));

    // 并集
    std::vector<std::string> words_union;
    std::set_union(chars_a.begin(), chars_a.end(), chars_b.begin(), chars_b.end(),
            std::back_inserter(words_union));

    // 交集长度 /并集长度
    float sim = float(words_intersect.size()) / float(words_union.size());

    return sim;
}

int JaccardSimilarity::compute_similarity(const std::vector<AnalysisItem>& analysis_items, MatchResult& candidates) {
    if (analysis_items.size() < 1) {
        return -1;
    }

    for (size_t i = 0; i < candidates.size(); i++) {
        // 计算query与候选的字符串Jaccard相似度
        float jaccard_sim = jaccard_similarity(analysis_items[0].query, candidates[i].analysis_item.query);
        DEBUG_LOG("jaccard = %f", jaccard_sim);
        // 权重化
		jaccard_sim = jaccard_sim * get_feature_weight();
		DEBUG_LOG("jaccard_weighted = %f", jaccard_sim);
		candidates[i].features.emplace_back(jaccard_sim);
    }

    return 0;
}

} // namespace nlper

