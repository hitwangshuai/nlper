#ifndef NLPER_SEMTOPIC_DD_SIM_H
#define NLPER_SEMTOPIC_DD_SIM_H

#include "matching/matching_interface.h"

namespace nlper {

class SemtopicDDSimilarity : public MatchingInterface {
public:
    SemtopicDDSimilarity();
    virtual ~SemtopicDDSimilarity() override;
    virtual int init(DualDictWrapper* dict, const MatchingConfig& matching_config) override;
    virtual int destroy() override;
    virtual int compute_similarity(const std::vector<AnalysisItem>& analysis_items, MatchResult& candidates) override;

private:
    // semtopic dict 指针
    SemtopicPack* _p_semtopic_pack;
    DISALLOW_COPY_AND_ASSIGN(SemtopicDDSimilarity);
};

} // namespace nlper

#endif  // NLPER_SEMTOPIC_DD_SIM_H

