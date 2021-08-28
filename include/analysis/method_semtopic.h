#ifndef NLPER_METHOD_SEMTOPIC_H
#define NLPER_METHOD_SEMTOPIC_H

#include "analysis/method_interface.h"

namespace nlper {

class AnalysisSemtopic: public AnalysisMethodInterface {
public:
    AnalysisSemtopic();
    virtual ~AnalysisSemtopic() override;
    virtual int init(DualDictWrapper* dict, const AnalysisMethodConfig& analysis_method) override;
    virtual int init(std::vector<DualDictWrapper*>& dicts, const AnalysisMethodConfig& analysis_method) override;
    virtual int destroy() override;
    virtual int single_process(AnalysisItem& analysis_item) override;

private:
    SemtopicPack* _p_semtopic_pack;
    DISALLOW_COPY_AND_ASSIGN(AnalysisSemtopic);
};

} // namespace nlper

#endif  // NLPER_METHOD_SEMTOPIC_H
