#ifndef NLPER_CONTAIN_SIM_H
#define NLPER_CONTAIN_SIM_H

#include "matching/matching_interface.h"
#include "common/utils.h"

namespace nlper {

//该特征表示query与候选之间是否存在包含关系
class ContainSimilarity : public MatchingInterface {
public:
    ContainSimilarity();
    virtual ~ContainSimilarity() override;
    virtual int init(DualDictWrapper* dict, const MatchingConfig& matching_config) override;
    virtual int destroy();
    // 判断analysis中query是否与召回query存在包含的关系
    virtual bool contain(const AnalysisItem& analysis_item, const MatchItem& match_item);
    // 特征计算
    virtual int compute_similarity(const std::vector<AnalysisItem>& analysis_items, MatchResult& candidates) override;
private:
    DISALLOW_COPY_AND_ASSIGN(ContainSimilarity);
};

} // namespace nlper

#endif  // NLPER_CONTAIN_SIMILARITY_H
