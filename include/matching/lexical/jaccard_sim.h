#ifndef NLPER_JACCARD_SIM_H
#define NLPER_JACCARD_SIM_H

#include "matching/matching_interface.h"
#include "common/utils.h"

namespace nlper {
// 该特征表示query与候选的字符串Jaccard相似度
class JaccardSimilarity : public MatchingInterface {
public:
    JaccardSimilarity();
    virtual ~JaccardSimilarity() override;
    virtual int init(DualDictWrapper* dict, const MatchingConfig& matching_config) override;
    virtual int destroy() override;
    float jaccard_similarity(const std::string& sent1, const std::string& sent2);
    virtual int compute_similarity(const std::vector<AnalysisItem>& analysis_items, MatchResult& candidates) override;

private:
    DISALLOW_COPY_AND_ASSIGN(JaccardSimilarity);
};

} // namespace nlper

#endif  // NLPER_JACCARD_SIMILARITY_H
