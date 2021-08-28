#ifndef NLPER_REQUEST_PREPROCESS_INTERFACE_H
#define NLPER_REQUEST_PREPROCESS_INTERFACE_H

#include "json/json.h"
#include "brpc/server.h"
#include "common/utils.h"
#include "nlper.pb.h"

namespace nlper {

class ReqPreprocInterface{
public:
    ReqPreprocInterface(){};
    virtual ~ReqPreprocInterface() {};
    int init_base(const std::string& plugin_name){
        _plugin_name = plugin_name;
        return 0;
    }
    virtual int init(const ReqPreprocPluginConfig& config) = 0;
    virtual int destroy() = 0;
    const std::string& plugin_name() {
        return _plugin_name;
    }
    virtual int process(brpc::Controller* cntl,
            Json::Value& parameters, std::string& str_input) = 0;

private:
    std::string _plugin_name;
    DISALLOW_COPY_AND_ASSIGN(ReqPreprocInterface);
};

}

#endif  // NLPER_REQUEST_PREPROCESS_INTERFACE_H
