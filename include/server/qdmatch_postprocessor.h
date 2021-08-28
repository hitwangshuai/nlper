#ifndef NLPER_QDMATCH_POSTPROCESSOR_H
#define NLPER_QDMATCH_POSTPROCESSOR_H

#include "server/request_postprocess_interface.h"

namespace nlper {

class QDMatchPostprocessor : public ReqPostprocInterface {
public:
    QDMatchPostprocessor() {};
    virtual ~QDMatchPostprocessor() override {};
    virtual int init(const ServerConfig& config) override;
    virtual int destroy() override;
    virtual int process(NlperResult& nlper_result, Json::Value& parameters, std::string& output) override;

private:
    DISALLOW_COPY_AND_ASSIGN(QDMatchPostprocessor);
};
} // namespace nlper

#endif  // NLPER_QDMATCH_POSTPROCESSOR_H
