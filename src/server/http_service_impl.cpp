#include "server/http_service_impl.h"
#include "brpc/http_method.h"
#include "server/session_data_factory.h"
#include "common/utils.h"
#include "common/plugin_factory.h"
#include "nlper.pb.h"

namespace nlper {

HttpServiceImpl::HttpServiceImpl() : _qdmatch_preproc_plugin(NULL),
                                    _qdmatch_postproc_plugin(NULL),
                                    _ddmatch_preproc_plugin(NULL),
                                    _ddmatch_postproc_plugin(NULL),
                                    _semtopic_preproc_plugin(NULL),
                                    _semtopic_postproc_plugin(NULL) {
}

HttpServiceImpl::~HttpServiceImpl() {
    if (destroy() != 0) {
        FATAL_LOG("release HttpServiceImpl error");
    }
}

int HttpServiceImpl::init_qdmatch(const ServerConfig& server_config) {
    const ReqPreprocPluginConfig& qdmatch_preproc_plugin_config = server_config.qdmatch_preproc_plugin();
    const ReqPostprocPluginConfig& qdmatch_postproc_plugin_config = server_config.qdmatch_postproc_plugin();
    std::string qdmatch_pre_plugin_type = qdmatch_preproc_plugin_config.type();
    std::string qdmatch_pre_plugin_name = qdmatch_preproc_plugin_config.name();
    _qdmatch_preproc_plugin = 
        static_cast<ReqPreprocInterface*>(PLUGIN_FACTORY.create_plugin(qdmatch_pre_plugin_type));
    if (_qdmatch_preproc_plugin == NULL) {
        FATAL_LOG("can't find req qdmatch preproc plugin_type:%s", qdmatch_pre_plugin_type.c_str());
        return -1;
    }
    if (_qdmatch_preproc_plugin->init(qdmatch_preproc_plugin_config) != 0) {
        FATAL_LOG("init req qdmatch preproc plugin error %s", qdmatch_pre_plugin_name.c_str());
        return -1;
    }
    TRACE_LOG("create req qdmatch preproc plugin %s success", qdmatch_pre_plugin_name.c_str());

    std::string qdmatch_post_plugin_type = qdmatch_postproc_plugin_config.type();
    std::string qdmatch_post_plugin_name = qdmatch_postproc_plugin_config.name();
    _qdmatch_postproc_plugin =
        static_cast<ReqPostprocInterface*>(PLUGIN_FACTORY.create_plugin(qdmatch_post_plugin_type));
    if (_qdmatch_postproc_plugin == NULL) {
        FATAL_LOG("can't find req qdmatch postproc plugin_type:%s", qdmatch_post_plugin_type.c_str());
        return -1;
    }
    if (_qdmatch_postproc_plugin->init(server_config) != 0) {
        FATAL_LOG("init req qdmatch postproc plugin error %s", qdmatch_post_plugin_name.c_str());
        return -1;
    }
    TRACE_LOG("create req qdmatch postproc plugin %s success", qdmatch_post_plugin_name.c_str());
    return 0;
}

int HttpServiceImpl::init_ddmatch(const ServerConfig& server_config) {
    const ReqPreprocPluginConfig& ddmatch_preproc_plugin_config = server_config.ddmatch_preproc_plugin();
    const ReqPostprocPluginConfig& ddmatch_postproc_plugin_config = server_config.ddmatch_postproc_plugin();
    std::string ddmatch_pre_plugin_type = ddmatch_preproc_plugin_config.type();
    std::string ddmatch_pre_plugin_name = ddmatch_preproc_plugin_config.name();
    _ddmatch_preproc_plugin = 
        static_cast<ReqPreprocInterface*>(PLUGIN_FACTORY.create_plugin(ddmatch_pre_plugin_type));
    if (_ddmatch_preproc_plugin == NULL) {
        FATAL_LOG("can't find req ddmatch preproc plugin_type:%s", ddmatch_pre_plugin_type.c_str());
        return -1;
    }
    if (_ddmatch_preproc_plugin->init(ddmatch_preproc_plugin_config) != 0) {
        FATAL_LOG("init req ddmatch preproc plugin error %s", ddmatch_pre_plugin_name.c_str());
        return -1;
    }
    TRACE_LOG("create req ddmatch preproc plugin %s success", ddmatch_pre_plugin_name.c_str());

    std::string ddmatch_post_plugin_type = ddmatch_postproc_plugin_config.type();
    std::string ddmatch_post_plugin_name = ddmatch_postproc_plugin_config.name();
    _ddmatch_postproc_plugin =
        static_cast<ReqPostprocInterface*>(PLUGIN_FACTORY.create_plugin(ddmatch_post_plugin_type));
    if (_ddmatch_postproc_plugin == NULL) {
        FATAL_LOG("can't find req ddmatch postproc plugin_type:%s", ddmatch_post_plugin_type.c_str());
        return -1;
    }
    if (_ddmatch_postproc_plugin->init(server_config) != 0) {
        FATAL_LOG("init req ddmatch postproc plugin error %s", ddmatch_post_plugin_name.c_str());
        return -1;
    }
    TRACE_LOG("create req ddmatch postproc plugin %s success", ddmatch_post_plugin_name.c_str());
    return 0;
}

int HttpServiceImpl::init_semtopic(const ServerConfig& server_config) {
    const ReqPreprocPluginConfig& semtopic_preproc_plugin_config = server_config.semtopic_preproc_plugin();
    const ReqPostprocPluginConfig& semtopic_postproc_plugin_config = server_config.semtopic_postproc_plugin();
    std::string semtopic_pre_plugin_type = semtopic_preproc_plugin_config.type();
    std::string semtopic_pre_plugin_name = semtopic_preproc_plugin_config.name();
    _semtopic_preproc_plugin = 
        static_cast<ReqPreprocInterface*>(PLUGIN_FACTORY.create_plugin(semtopic_pre_plugin_type));
    if (_semtopic_preproc_plugin == NULL) {
        FATAL_LOG("can't find req semtopic preproc plugin_type:%s", semtopic_pre_plugin_type.c_str());
        return -1;
    }
    if (_semtopic_preproc_plugin->init(semtopic_preproc_plugin_config) != 0) {
        FATAL_LOG("init req semtopic preproc plugin error %s", semtopic_pre_plugin_name.c_str());
        return -1;
    }
    TRACE_LOG("create req semtopic preproc plugin %s success", semtopic_pre_plugin_name.c_str());

    std::string semtopic_post_plugin_type = semtopic_postproc_plugin_config.type();
    std::string semtopic_post_plugin_name = semtopic_postproc_plugin_config.name();
    _semtopic_postproc_plugin =
        static_cast<ReqPostprocInterface*>(PLUGIN_FACTORY.create_plugin(semtopic_post_plugin_type));
    if (_semtopic_postproc_plugin == NULL) {
        FATAL_LOG("can't find req semtopic postproc plugin_type:%s", semtopic_post_plugin_type.c_str());
        return -1;
    }
    if (_semtopic_postproc_plugin->init(server_config) != 0) {
        FATAL_LOG("init req semtopic postproc plugin error %s", semtopic_post_plugin_name.c_str());
        return -1;
    }
    TRACE_LOG("create req semtopic postproc plugin %s success", semtopic_post_plugin_name.c_str());
    return 0;
}

int HttpServiceImpl::init(const ServerConfig& server_config) {
    int ret = 0;
    ret = init_qdmatch(server_config);
    ret = init_ddmatch(server_config);
    ret = init_semtopic(server_config);
    _method = server_config.method();
    return ret;
}

int HttpServiceImpl::destroy() {
    if (_qdmatch_postproc_plugin != NULL) {
        if (_qdmatch_postproc_plugin->destroy() != 0) {
            FATAL_LOG("req qdmatch postproc plugin %s destroy error",
                _qdmatch_postproc_plugin->plugin_name().c_str());
            return -1;
        }
        delete _qdmatch_postproc_plugin;
        _qdmatch_postproc_plugin = NULL;
    }
    
    if (_ddmatch_postproc_plugin != NULL) {
        if (_ddmatch_postproc_plugin->destroy() != 0) {
            FATAL_LOG("req ddmatch postproc plugin %s destroy error",
                _ddmatch_postproc_plugin->plugin_name().c_str());
            return -1;
        }
        delete _ddmatch_postproc_plugin;
        _ddmatch_postproc_plugin = NULL;
    }
    
    if (_semtopic_postproc_plugin != NULL) {
        if (_semtopic_postproc_plugin->destroy() != 0) {
            FATAL_LOG("req semtopic postproc plugin %s destroy error",
                _semtopic_postproc_plugin->plugin_name().c_str());
            return -1;
        }
        delete _semtopic_postproc_plugin;
        _semtopic_postproc_plugin = NULL;
    }
    
    return 0;
}

int HttpServiceImpl::normalize_input(brpc::Controller* cntl, Json::Value& parameters) {
    brpc::HttpMethod req_method = cntl->http_request().method();
    if (req_method == brpc::HTTP_METHOD_GET) {
        brpc::URI* uri = &cntl->http_request().uri();
        for (brpc::URI::QueryIterator it = uri->QueryBegin(); it != uri->QueryEnd(); ++it) {
            parameters[it->first] = url_decode(it->second);
        }
    } else if (req_method == brpc::HTTP_METHOD_POST) {
        const std::string req_body = cntl->request_attachment().to_string();
        if (req_body.length() == 0) {
            FATAL_LOG("POST body Null Error.");
            return -1;
        }
        Json::Reader reader;
        if (!reader.parse(req_body, parameters)
            || (parameters.type() != Json::objectValue && parameters.type() != Json::arrayValue)) {
            FATAL_LOG("POST body Parsing Error.");
            return -1;
        }
    } else {
        FATAL_LOG("invalid http request method!");
        return -1;
    }
    return 0;
}

// qdmatch总处理入口
void HttpServiceImpl::run_qdmatch(google::protobuf::RpcController* cntl_base,
        const HttpRequest*, HttpResponse*, google::protobuf::Closure* done) {
    brpc::ClosureGuard done_guard(done);
    brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);
    cntl->http_response().set_content_type("application/json;charset=utf8");
    if (_method == "POST") {
        cntl->http_request().set_method(brpc::HTTP_METHOD_POST);
    } else {
        cntl->http_request().set_method(brpc::HTTP_METHOD_GET);
    }
    
    // 预处理
    Json::Value parameters;
    if (this->normalize_input(cntl, parameters) != 0
        || parameters.type() != Json::objectValue) {
        FATAL_LOG("qdmatch normalize input failed!");
        return;
    }
    
    std::string str_nlper_input;
    if (_qdmatch_preproc_plugin->process(cntl, parameters, str_nlper_input) != 0) {
        FATAL_LOG("qdmatch preproc_plugin failed!");
        return;
    }
    
    // 核心策略
    SessionData* sd = static_cast<SessionData*>(cntl->session_local_data());
    if (sd == NULL) {
        cntl->SetFailed("qdmatch Require ServerOptions.session_local_data_factory to be set!");
        FATAL_LOG("%s", cntl->ErrorText().c_str());
        return;
    }

    NlperResult result;
    if (sd->get_qdmatch_strategy()->run_strategy(str_nlper_input, result) != 0) {
        FATAL_LOG("qdmatch run_strategy failed!");
        return;
    }

    // 后处理
    std::string output;
    if (_qdmatch_postproc_plugin->process(result, parameters, output) != 0) {
        FATAL_LOG("qdmatch postproc_plugin %s process error", _qdmatch_postproc_plugin->plugin_name().c_str());
        return;
    }

    butil::IOBufBuilder os;
    os << output;
    os.move_to(cntl->response_attachment());
}

// ddmatch总处理入口
void HttpServiceImpl::run_ddmatch(google::protobuf::RpcController* cntl_base,
        const HttpRequest*, HttpResponse*, google::protobuf::Closure* done) {
    brpc::ClosureGuard done_guard(done);
    brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);
    cntl->http_response().set_content_type("application/json;charset=utf8");
    if (_method == "POST") {
        cntl->http_request().set_method(brpc::HTTP_METHOD_POST);
    } else {
        cntl->http_request().set_method(brpc::HTTP_METHOD_GET);
    }
    
    // 预处理
    Json::Value parameters;
    if (this->normalize_input(cntl, parameters) != 0
        || parameters.type() != Json::objectValue) {
        FATAL_LOG("ddmatch normalize input failed!");
        return;
    }
    
    std::string str_nlper_input;
    if (_ddmatch_preproc_plugin->process(cntl, parameters, str_nlper_input) != 0) {
        FATAL_LOG("ddmatch preproc_plugin failed!");
        return;
    }
    
    // 核心策略
    SessionData* sd = static_cast<SessionData*>(cntl->session_local_data());
    if (sd == NULL) {
        cntl->SetFailed("ddmatch Require ServerOptions.session_local_data_factory to be set!");
        FATAL_LOG("%s", cntl->ErrorText().c_str());
        return;
    }

    NlperResult result;
    if (sd->get_ddmatch_strategy()->run_strategy(str_nlper_input, result) != 0) {
        FATAL_LOG("ddmatch run_strategy failed!");
        return;
    }

    // 后处理
    std::string output;
    if (_ddmatch_postproc_plugin->process(result, parameters, output) != 0) {
        FATAL_LOG("ddmatch postproc_plugin %s process error", _ddmatch_postproc_plugin->plugin_name().c_str());
        return;
    }

    butil::IOBufBuilder os;
    os << output;
    os.move_to(cntl->response_attachment());
}

// semtopic总处理入口
void HttpServiceImpl::run_semtopic(google::protobuf::RpcController* cntl_base,
        const HttpRequest*, HttpResponse*, google::protobuf::Closure* done) {
    brpc::ClosureGuard done_guard(done);
    brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);
    cntl->http_response().set_content_type("application/json;charset=utf8");
    if (_method == "POST") {
        cntl->http_request().set_method(brpc::HTTP_METHOD_POST);
    } else {
        cntl->http_request().set_method(brpc::HTTP_METHOD_GET);
    }
    
    // 预处理
    Json::Value parameters;
    if (this->normalize_input(cntl, parameters) != 0
        || parameters.type() != Json::objectValue) {
        FATAL_LOG("semtopic normalize input failed!");
        return;
    }
    
    std::string str_nlper_input;
    if (_semtopic_preproc_plugin->process(cntl, parameters, str_nlper_input) != 0) {
        FATAL_LOG("semtopic preproc_plugin failed!");
        return;
    }
    
    // 核心策略
    SessionData* sd = static_cast<SessionData*>(cntl->session_local_data());
    if (sd == NULL) {
        cntl->SetFailed("semtopic Require ServerOptions.session_local_data_factory to be set!");
        FATAL_LOG("%s", cntl->ErrorText().c_str());
        return;
    }

    NlperResult result;
    if (sd->get_semtopic_strategy()->run_strategy(str_nlper_input, result) != 0) {
        FATAL_LOG("semtopic run_strategy failed!");
        return;
    }

    // 后处理
    std::string output;
    if (_semtopic_postproc_plugin->process(result, parameters, output) != 0) {
        FATAL_LOG("semtopic postproc_plugin %s process error", _semtopic_postproc_plugin->plugin_name().c_str());
        return;
    }

    butil::IOBufBuilder os;
    os << output;
    os.move_to(cntl->response_attachment());
}

} // namespace nlper
