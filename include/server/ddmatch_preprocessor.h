#ifndef NLPER_DDMATCH_PREPROCESSOR_H
#define NLPER_DDMATCH_PREPROCESSOR_H

#include "server/request_preprocess_interface.h"

namespace nlper {

class DDMatchPreprocessor : public ReqPreprocInterface {
public:
    DDMatchPreprocessor() {};
    virtual ~DDMatchPreprocessor() override {};
    virtual int init(const ReqPreprocPluginConfig& config) override;
    virtual int destroy() override;
    virtual int process(brpc::Controller*, Json::Value& parameters, std::string& input) override;

private:
    DISALLOW_COPY_AND_ASSIGN(DDMatchPreprocessor);    
};

} // namespace nlper

#endif  // NLPER_PREPROCESSOR_H
