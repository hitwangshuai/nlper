#ifndef NLPER_DDMATCH_POSTPROCESSOR_H
#define NLPER_DDMATCH_POSTPROCESSOR_H

#include "server/request_postprocess_interface.h"

namespace nlper {

class DDMatchPostprocessor : public ReqPostprocInterface {
public:
    DDMatchPostprocessor() {};
    virtual ~DDMatchPostprocessor() override {};
    virtual int init(const ServerConfig& config) override;
    virtual int destroy() override;
    virtual int process(NlperResult& nlper_result, Json::Value& parameters, std::string& output) override;

private:
    DISALLOW_COPY_AND_ASSIGN(DDMatchPostprocessor);
};
} // namespace nlper

#endif  // NLPER_DDMATCH_POSTPROCESSOR_H
