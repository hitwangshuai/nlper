#include "common/utils.h"
#include "server/http_server.h"
#include "server/session_data_factory.h"

namespace brpc {
    DECLARE_bool(usercode_in_pthread);
}

namespace nlper {

HttpServer::HttpServer() {
}

HttpServer::~HttpServer() {
    std::map<int32_t, brpc::Server*>::iterator it;
    for (it = _servers.begin(); it != _servers.end(); it++) {
        int32_t port = it->first;
        if (_servers[port] != NULL) {
            delete _servers[port];
            _servers[port] = NULL;
        }
    }
    _servers.clear();
}

int HttpServer::init(std::string& http_server_conf) {
    if (load_config_from_file(http_server_conf, _server_config) != 0) {
        fprintf(stderr, "load_config_from_file failed\n");
        return -1;
    }
    _idle_timeout_sec = _server_config.idle_timeout_sec();
    _max_concurrency = _server_config.max_concurrency();
    _server_conf_dir = _server_config.server_conf_dir();
    _nlper_dict_conf_dir = _server_config.nlper_dict_conf_dir();
    _nlper_conf_dir = _server_config.nlper_conf_dir();
    
    std::string config_port = _server_config.port();
    std::vector<std::string> port_strs;
    split_string(config_port, port_strs, ",");
    for (int i = 0; i < port_strs.size(); i++) {
        int32_t port = atoi(port_strs[i].c_str());
        brpc::Server* server = new brpc::Server();
        _servers[port] = server;
    }
    if (_servers.size() == 0) {
        FATAL_LOG("servers init error!");
    }

    // 启动时加载词典:多实例也只加载一次,多进程资源共享
    if (_dict_manager.load_dict(_nlper_dict_conf_dir) != 0) {
        FATAL_LOG("load dict error, _nlper_dict_conf_dir=%s", _nlper_dict_conf_dir.c_str());
        return -1;
    }

    return 0;
}

int HttpServer::start() {
    // 开辟栈空间
    brpc::FLAGS_usercode_in_pthread = true;
    
    // 用于创建sessiondata
    std::map<int, SessionDataFactory*> session_data_factories;
    std::map<int32_t, brpc::Server*>::iterator it;
    for (it = _servers.begin(); it != _servers.end(); it++) {
        int32_t port = it->first;
        SessionDataFactory* session_data_factory = 
            new SessionDataFactory(&_dict_manager, _nlper_conf_dir);
        session_data_factories[port] = session_data_factory;
    }

    // server参数配置
    std::map<int, brpc::ServerOptions*> options;
    for (it = _servers.begin(); it != _servers.end(); it++) {
        int32_t port = it->first;
        brpc::ServerOptions* option = new brpc::ServerOptions();
        option->idle_timeout_sec = _idle_timeout_sec;
        option->max_concurrency = _max_concurrency;
        option->session_local_data_factory = session_data_factories[port];
        options[port] = option;
    }

    // service实例化
    std::map<int, HttpServiceImpl*> http_service_impls;
    for (it = _servers.begin(); it != _servers.end(); it++) {
        int32_t port = it->first;
        HttpServiceImpl* http_service_impl = new HttpServiceImpl();
        if (http_service_impl->init(_server_config) != 0) {
            WARNING_LOG("http_service_impl init failed at %d", port);
            return -1;
        }
        http_service_impls[port] = http_service_impl;
    }

    // 将service添加到server
    for (it = _servers.begin(); it != _servers.end(); it++) {
        int32_t port = it->first;
        DEBUG_LOG("instence server at %d", port); 
        int ret = _servers[port]->AddService(http_service_impls[port],
                brpc::SERVER_DOESNT_OWN_SERVICE,
                    "/qdmatch => run_qdmatch,"
                    "/ddmatch => run_ddmatch,"
                    "/semtopic => run_semtopic,"
                    );
        if (ret != 0) {
            FATAL_LOG("Fail to add service to server at %d", port);
            return -1;
        }
        
        // 启动server
        if (_servers[port]->Start(port, options[port]) != 0) {
            FATAL_LOG("Fail to start HttpServer at %d", port);
            return -1;
        }
    }

    // server资源释放
    for (it = _servers.begin(); it != _servers.end(); it++) {
        int32_t port = it->first;
        _servers[port]->Stop(0);
    }
    for (it = _servers.begin(); it != _servers.end(); it++) {
        int32_t port = it->first;
        _servers[port]->Join();
    }

    // 指针资源释放
    for (it = _servers.begin(); it != _servers.end(); it++) {
        int32_t port = it->first;
        if (http_service_impls[port] != NULL) {
            delete http_service_impls[port];
            http_service_impls[port] = NULL;
        }
        if (options[port] != NULL) {
            delete options[port];
            options[port] = NULL;
        }
        if (session_data_factories[port] != NULL) {
            delete session_data_factories[port];
            session_data_factories[port] = NULL;
        }
    }

    return 0;
}

int HttpServer::always_run() {
    // 开辟栈空间
    brpc::FLAGS_usercode_in_pthread = true;
    
    // 用于创建sessiondata
    std::map<int, SessionDataFactory*> session_data_factories;
    std::map<int32_t, brpc::Server*>::iterator it;
    for (it = _servers.begin(); it != _servers.end(); it++) {
        int32_t port = it->first;
        SessionDataFactory* session_data_factory = 
            new SessionDataFactory(&_dict_manager, _nlper_conf_dir);
        session_data_factories[port] = session_data_factory;
    }

    // server参数配置
    std::map<int, brpc::ServerOptions*> options;
    for (it = _servers.begin(); it != _servers.end(); it++) {
        int32_t port = it->first;
        brpc::ServerOptions* option = new brpc::ServerOptions();
        option->idle_timeout_sec = _idle_timeout_sec;
        option->max_concurrency = _max_concurrency;
        option->session_local_data_factory = session_data_factories[port];
        options[port] = option;
    }

    // service实例化
    std::map<int, HttpServiceImpl*> http_service_impls;
    for (it = _servers.begin(); it != _servers.end(); it++) {
        int32_t port = it->first;
        HttpServiceImpl* http_service_impl = new HttpServiceImpl();
        if (http_service_impl->init(_server_config) != 0) {
            WARNING_LOG("http_service_impl init failed at %d", port);
            return -1;
        }
        http_service_impls[port] = http_service_impl;
    }

    // 将service添加到server
    for (it = _servers.begin(); it != _servers.end(); it++) {
        int32_t port = it->first;
        DEBUG_LOG("instence server at %d", port); 
        int ret = _servers[port]->AddService(http_service_impls[port],
                brpc::SERVER_DOESNT_OWN_SERVICE,
                    "/qdmatch => run_qdmatch,"
                    "/ddmatch => run_ddmatch,"
                    "/semtopic => run_semtopic,"
                    );
        if (ret != 0) {
            FATAL_LOG("Fail to add service to server at %d", port);
            return -1;
        }
        
        // 启动server
        if (_servers[port]->Start(port, options[port]) != 0) {
            FATAL_LOG("Fail to start HttpServer at %d", port);
            return -1;
        }
    }

    // 进程终止监听:Ctrl-C
    while (!brpc::IsAskedToQuit()) {
        bthread_usleep(1000000L);
    }

    // server资源释放
    for (it = _servers.begin(); it != _servers.end(); it++) {
        int32_t port = it->first;
        _servers[port]->Stop(0);
    }
    for (it = _servers.begin(); it != _servers.end(); it++) {
        int32_t port = it->first;
        _servers[port]->Join();
    }

    // 指针资源释放
    for (it = _servers.begin(); it != _servers.end(); it++) {
        int32_t port = it->first;
        if (http_service_impls[port] != NULL) {
            delete http_service_impls[port];
            http_service_impls[port] = NULL;
        }
        if (options[port] != NULL) {
            delete options[port];
            options[port] = NULL;
        }
        if (session_data_factories[port] != NULL) {
            delete session_data_factories[port];
            session_data_factories[port] = NULL;
        }
    }
    http_service_impls.clear();
    options.clear();
    session_data_factories.clear();

    return 0;
}

} // namespace nlper
