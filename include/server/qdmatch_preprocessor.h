#ifndef NLPER_QDMATCH_PREPROCESSOR_H
#define NLPER_QDMATCH_PREPROCESSOR_H

#include "server/request_preprocess_interface.h"

namespace nlper {

class QDMatchPreprocessor : public ReqPreprocInterface {
public:
    QDMatchPreprocessor() {};
    virtual ~QDMatchPreprocessor() override {};
    virtual int init(const ReqPreprocPluginConfig& config) override;
    virtual int destroy() override;
    virtual int process(brpc::Controller*, Json::Value& parameters, std::string& input) override;

private:
    DISALLOW_COPY_AND_ASSIGN(QDMatchPreprocessor);    
};

} // namespace nlper

#endif  // NLPER_PREPROCESSOR_H
