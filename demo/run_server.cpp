#include <glog/logging.h>
#include "server/http_server.h"
#include "common/utils.h"
#include "common/plugin_header.h"

int main(int argc, char* argv[]) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_stderrthreshold = google::INFO;
    nlper::HttpServer server;
    std::string nlper_brpc_conf = "./data/brpc.conf";
    if (server.init(nlper_brpc_conf) != 0) {
        FATAL_LOG("server init failed");
        return -1;
    }

    if (server.always_run() != 0) {
        FATAL_LOG("server run failed");
        return -1;
    }
    return 0;
}
