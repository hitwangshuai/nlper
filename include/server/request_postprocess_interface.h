#ifndef NLPER_REQUEST_POSTPROCESS_INTERFACE_H
#define NLPER_REQUEST_POSTPROCESS_INTERFACE_H

#include "json/json.h"
#include "common/utils.h"
#include "nlper.pb.h"

namespace nlper {

class ReqPostprocInterface
{
public:
    ReqPostprocInterface() {};
    virtual ~ReqPostprocInterface() {};
    int init_base(const std::string& plugin_name){
        _plugin_name = plugin_name;
        return 0;
    }; 
    virtual int init(const ServerConfig&) = 0;
    virtual int destroy() = 0;
    const std::string& plugin_name(){
        return _plugin_name;
    }
    virtual int process(NlperResult& nlper_result,
            Json::Value& parameters, std::string& output) = 0;

private:
    std::string _plugin_name;
    DISALLOW_COPY_AND_ASSIGN(ReqPostprocInterface);
};

} // namespace nlper

#endif  // NLPER_REQUEST_PROCESSOR_INTERFACE_H
