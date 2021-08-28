#ifndef NLPER_HTTP_SERVER_H
#define NLPER_HTTP_SERVER_H

#include <string>
#include "nlper.pb.h"
#include "dict/dict_manager.h"
#include "server/http_service_impl.h"

namespace nlper {

class HttpServer {
public:
    HttpServer();
    ~HttpServer();

    int init(std::string& http_server_conf);
    // ����������,��������˳�,����������㵥��
    int start();
    // ����������,�������һֱ���У�ֱ��ctrl-c
    int always_run();

private:
    int32_t _idle_timeout_sec;
    int32_t _max_concurrency;

    // server����
    std::string _server_conf_dir;
    std::string _log_conf_file;
    std::string _nlper_dict_conf_dir;
    std::string _nlper_conf_dir;
    ServerConfig _server_config;
    // ���̼��ʵ�
    DictManager _dict_manager;
    std::map<int32_t, brpc::Server*> _servers; // port:server
    DISALLOW_COPY_AND_ASSIGN(HttpServer);
};

} // namespace nlper

#endif  // NLPER_HTTP_SERVER_H
