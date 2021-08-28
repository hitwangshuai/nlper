#ifndef NLPER_HTTP_CLIENT_H
#define NLPER_HTTP_CLIENT_H

#include <string.h>
#include <curl/curl.h>
#include <map>
#include "common/common_define.h"

namespace nlper {

class HttpClient {
public:
    HttpClient();
    ~HttpClient();
    // get请求
    int curl_get(const char* url, std::string* buffer);
    // post请求
    int curl_post(const char* url, const std::map<std::string, std::string>& para_map,
            std::string* buffer);
    int curl_post(const char* url, const std::string& para_str, std::string* buffer,
            const std::string& header_str);
    // 请求结束后，读取返回数据回调函数
    static int str_write_callback(char* data, size_t size, size_t nmemb, std::string* buffer);

private:
    // curl指针
    CURL* _p_curl;
    DISALLOW_COPY_AND_ASSIGN(HttpClient);
};
} // namespace nlper

#endif  // NLPER_HTTP_CLIENT_H
