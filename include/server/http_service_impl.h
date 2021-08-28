#ifndef NLPER_HTTP_SERVICE_IMPL_H
#define NLPER_HTTP_SERVICE_IMPL_H

#include "brpc/uri.h"
#include "brpc/server.h"
#include "http_service.pb.h"
#include "nlper.pb.h"
#include "common/common_define.h"
#include "server/request_preprocess_interface.h"
#include "server/request_postprocess_interface.h"

namespace nlper {

class HttpServiceImpl : public nlper::HttpService {
public:
    HttpServiceImpl();
    ~HttpServiceImpl();
    int init_qdmatch(const ServerConfig& server_config);
    int init_ddmatch(const ServerConfig& server_config);
    int init_semtopic(const ServerConfig& server_config);
    int init(const ServerConfig& server_config);
    int destroy();
    int normalize_input(brpc::Controller* cntl, Json::Value& parameters);
    
    // 短文-长文级语义匹配
    void run_qdmatch(google::protobuf::RpcController* cntl_base,
            const HttpRequest*, HttpResponse*, google::protobuf::Closure* done);
    // 长文-长文级语义匹配
    void run_ddmatch(google::protobuf::RpcController* cntl_base,
            const HttpRequest*, HttpResponse*, google::protobuf::Closure* done);
    // 主题分析
    void run_semtopic(google::protobuf::RpcController* cntl_base,
            const HttpRequest*, HttpResponse*, google::protobuf::Closure* done);
    
    private:
    // 处理方式
    std::string _method;

    // 前处理，将server接收到的数据(get/post)处理成nlper的输入格式
    ReqPreprocInterface* _qdmatch_preproc_plugin;
    ReqPreprocInterface* _ddmatch_preproc_plugin;
    ReqPreprocInterface* _semtopic_preproc_plugin;

    // 后处理，将nlper的输出结果定制输出
    ReqPostprocInterface* _qdmatch_postproc_plugin;
    ReqPostprocInterface* _ddmatch_postproc_plugin;
    ReqPostprocInterface* _semtopic_postproc_plugin;
    
    DISALLOW_COPY_AND_ASSIGN(HttpServiceImpl);
};

} // namespace nlper
#endif  // NLPER_HTTP_SERVICE_IMPL_H
