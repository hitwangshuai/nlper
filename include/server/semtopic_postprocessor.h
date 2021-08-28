#ifndef NLPER_SEMTOPIC_POSTPROCESSOR_H
#define NLPER_SEMTOPIC_POSTPROCESSOR_H

#include "server/request_postprocess_interface.h"

namespace nlper {

class SemtopicPostprocessor : public ReqPostprocInterface {
public:
    SemtopicPostprocessor() {};
    virtual ~SemtopicPostprocessor() override {};
    virtual int init(const ServerConfig& config) override;
    virtual int destroy() override;
    virtual int process(NlperResult& nlper_result, Json::Value& parameters, std::string& output) override;

private:
    DISALLOW_COPY_AND_ASSIGN(SemtopicPostprocessor);
};
} // namespace nlper

#endif  // NLPER_SEMTOPIC_POSTPROCESSOR_H
