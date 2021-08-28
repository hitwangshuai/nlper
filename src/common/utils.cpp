#include "common/utils.h"
#include <algorithm>
#include <fstream>
#include <math.h>
#include <iconv.h>
#include <cassert>
#include <stdexcept>
#include <pthread.h>
#include "json/json.h"
#include "boost/algorithm/string.hpp"

namespace nlper {

int hash_load(const char* dict_file, std::unordered_map<std::string, std::string>& dict_map){
    std::fstream dict_fs(dict_file, std::fstream::in);
    if (!dict_fs.is_open()) {
        FATAL_LOG("open dict_file error");
        return -1;
    } else {
        std::string line;
        std::vector<std::string> fields;
        while (getline(dict_fs, line)) {
            split_string(line, fields, "\t");
            if (fields.size() != 2) {
                WARNING_LOG("field_size, %d", fields.size());
                WARNING_LOG("dict[%s] invalid line, %s", dict_file, line.c_str());
                continue;
            }
            dict_map[fields[0]] = fields[1];
        }
    }
    TRACE_LOG("hash load %s done", dict_file);
    return 0;
}

int hash_load(const char* dict_file, std::unordered_map<std::string, float>& dict_map){
    std::fstream dict_fs(dict_file, std::fstream::in);
    if (!dict_fs.is_open()) {
        FATAL_LOG("open dict_file error");
        return -1;
    } else {
        std::string line;
        std::vector<std::string> fields;
        while (getline(dict_fs, line)) {
            split_string(line, fields, "\t");
            if (fields.size() != 2) {
                WARNING_LOG("dict[%s] invalid line, %s", dict_file, line.c_str());
                continue;
            }
            dict_map[fields[0]] = atof(fields[1].c_str());
        }
    }
    TRACE_LOG("hash load %s done", dict_file);
    return 0;
}

int hash_load(const char* dict_file, std::unordered_map<std::string, int>& dict_map){
    std::fstream dict_fs(dict_file, std::fstream::in);
    if (!dict_fs.is_open()) {
        FATAL_LOG("open dict_file error");
        return -1;
    } else {
        std::string line;
        std::vector<std::string> fields;
        while (getline(dict_fs, line)) {
            split_string(line, fields, "\t");
            if (fields.size() != 2) {
                WARNING_LOG("dict[%s] invalid line, %s", dict_file, line.c_str());
                continue;
            }
            dict_map[fields[0]] = atoi(fields[1].c_str());
        }
    }

    TRACE_LOG("hash load %s done", dict_file);
    return 0;
}

int hash_load(const char* dict_file, std::unordered_map<int, std::string>& dict_map){
    std::fstream dict_fs(dict_file, std::fstream::in);
    if (!dict_fs.is_open()) {
        FATAL_LOG("open dict_file error");
        return -1;
    } else {
        std::string line;
        std::vector<std::string> fields;
        while (getline(dict_fs, line)) {
            split_string(line, fields, "\t");
            if (fields.size() != 2) {
                WARNING_LOG("dict[%s] invalid line, %s", dict_file, line.c_str());
                continue;
            }
            dict_map[atoi(fields[0].c_str())] = fields[1];
        }
    }
    TRACE_LOG("hash load %s done", dict_file);
    return 0;
}

int get_file_last_modified_time(const std::string& file_path, std::string& mtime_str) {
    struct stat f_stat;
    if (stat(file_path.c_str(), &f_stat) != 0) {
        WARNING_LOG("get file state error: %s", file_path.c_str()); 
        return -1;
    }
    mtime_str = ctime(&f_stat.st_mtime);
    return 0;
}

std::string cut_string(const std::string& input, const std::string& delimeter, int start, int end) {
    std::vector<std::string> fields;
    split_string(input, fields, delimeter);
    std::string ret = "";
    for (int i = start; i <= end && i < fields.size(); i++) {
        if (ret == "") {
            ret = fields[i];
        } else {
            ret += (delimeter + fields[i]);
        }
    }
    
    if (ret == "") {
        ret = input;
    }
    return ret;
}

void split_string(const std::string& input, std::vector<std::string>& result, const std::string& delimeter) {
    std::string::size_type pos1;
    std::string::size_type pos2;
    result.clear();
    pos2 = input.find(delimeter);
    pos1 = 0;

    while (std::string::npos != pos2) {
        result.emplace_back(input.substr(pos1, pos2 - pos1));
        pos1 = pos2 + delimeter.size();
        pos2 = input.find(delimeter, pos1);
    }
    result.emplace_back(input.substr(pos1, input.length()));
}

int split_sentence(const std::string& input, std::vector<std::string>& sentences) {
    sentences.clear();
    std::map<std::string, int> puncts = {{"。", 1}, {"﹔", 1}, {"！", 1}, {"﹖", 1}, {"？", 1}, {"；", 1}, {"?", 1}, {"!", 1}};
    std::vector<std::string> chars;
    utf8_to_char(input, chars);
    std::string sentence = "";
    for (int i = 0; i < chars.size(); i++) {
        if (puncts.find(chars[i]) != puncts.end()) {
            sentence += chars[i];
            sentences.push_back(sentence); //这里要拷贝
            sentence = "";
        } else {
            sentence += chars[i];
        }
    }
    if (sentence != "") {
        sentences.push_back(sentence);
    }
    return sentences.size();
}

int utf8_to_char(const std::string& sent, std::vector<std::string>& chars) {
    size_t len = sent.size();
    chars.clear();
    for (size_t i = 0; i < len;) {
        size_t beg = i;
        unsigned char p = (unsigned char) sent[i];
        if (p < 0x80) {
            if (p == ' ') {
                ++i;
            }else {
                while (i < len && p < 0x80 && p != ' ') {
                    p = (unsigned char) sent[++i];
                }
            }
        }else if (p < 0xC0) {
            return -1;
        }else if (p < 0xE0) {
            i += 2;
        }else if (p < 0xF0) {
            i += 3;
        }else if (p < 0xF8) {
            i += 4;
        }else if (p < 0xFC) {
            i += 5;
        }else if (p < 0xFE) {
            i += 6;
        }else {
            return -1;
        }
        if (i > len) {
            return -1;
        }
        chars.emplace_back(sent.substr(beg, i - beg));
    }
    return 0;
}

// 特殊字符转义,比如 , 转义为 \,
std::string escape(const std::string& str) {
    std::string escape_str;
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] & 0x80) {
            escape_str += str[i];
            if (i == (str.size() - 1)) {
                break;
            }
            i++;
            escape_str += str[i];
        } else {
            if (ESCAPE_CHAR.find(str[i]) != ESCAPE_CHAR.end()) {
                escape_str += '\\';
                escape_str += str[i];
            } else {
                escape_str += str[i];
            }
        }
    }
    return escape_str;
}

std::string url_encode(const std::string& str_source)
{
    char const *in_str = str_source.c_str();
    int in_str_len = strlen(in_str);
    unsigned char *to = (unsigned char *)malloc(3 * in_str_len + 1);
    unsigned char *start = to;
    unsigned char const *from = (unsigned char *)in_str;
    unsigned char const *end = (unsigned char *)in_str + in_str_len;
    unsigned char hexchars[] = "0123456789ABCDEF";

    while (from < end) {
        register unsigned char c = *from++;

        if (c == ' ') {
            *to++ = '+';
        }
        else if ((c < '0' && c != '-' && c != '.') ||
            (c < 'A' && c > '9') ||
            (c > 'Z' && c < 'a' && c != '_') ||
            (c > 'z')) {
            to[0] = '%';
            to[1] = hexchars[c >> 4];
            to[2] = hexchars[c & 15];
            to += 3;
        }
        else {
            *to++ = c;
        }
    }
    *to = 0;

    int out_str_len = to - start;
    std::string out_str = (char *)start;
    free(start);
    return out_str;
}

std::string url_decode(std::string text) {
    char h = 0;
    std::ostringstream escaped;
    escaped.fill('0');
    for (auto i = text.begin(), n = text.end(); i != n; ++i) {
        std::string::value_type c = (*i);
        if (c == '%') {
            if (i[1] && i[2]) {
                h = from_hex(i[1]) << 4 | from_hex(i[2]);
                escaped << h;
                i += 2;
            }
        } else if (c == '+') {
            escaped << ' ';
        } else {
            escaped << c;
        }
    }
    return escaped.str();
}

std::string utf8_to_gbk(const std::string& utf8_str) {
    if (utf8_str.size() == 0) {
        return "";
    }
    std::vector<char> gbk_buf(utf8_str.size() * 2);
    char* in_buf = const_cast<char*>(utf8_str.c_str());
    size_t in_size = utf8_str.size();
    char* out_buf = &gbk_buf[0];
    size_t out_size = gbk_buf.size();
    iconv_t cd = iconv_open("GBK", "UTF-8");
    size_t res = iconv(cd, &in_buf, &in_size, &out_buf, &out_size);
    iconv_close(cd);
    if (res == size_t(-1)) {
        return "";
    }
    std::string gbk_str(&gbk_buf[0], (gbk_buf.size() - out_size));
    return gbk_str;
}

std::string gbk_to_utf8(const std::string& gbk_str) {
    std::vector<char> utf8_buf(gbk_str.size() * 3 / 2 + 1);
    char* in_buf = const_cast<char*>(gbk_str.c_str());
    size_t in_size = gbk_str.size();
    char* out_buf = &utf8_buf[0];
    size_t out_size = utf8_buf.size();
    iconv_t cd = iconv_open("UTF-8", "GBK");
    size_t res = iconv(cd, &in_buf, &in_size, &out_buf, &out_size);
    iconv_close(cd);
    if (res == size_t(-1)) {
        return "";
    }
    std::string utf8_str(&utf8_buf[0], (utf8_buf.size() - out_size));
    return utf8_str;
}

void trans_id_to_term(const hashmap_int2str &id2term_kv,
        std::vector<int> &result_ids,
        std::vector<std::string> &tokens){
    int length = result_ids.size();
    hashmap_int2str::const_iterator got;
    for (int i = 0; i < length; i++) {
        got = id2term_kv.find(result_ids[i]);
        if (got != id2term_kv.end()){
            tokens.emplace_back(got->second);
        }
    }
}

int string_to_id_buffer(float* out_buffer,
        const int capacity,
        const std::vector<float>& id_strs) {
    if (id_strs.size() > capacity){
        WARNING_LOG("input length larger");
        return -1;
    }
    for (size_t i = 0; i < id_strs.size(); i++) {
        out_buffer[i] = id_strs[i];
    }
    return id_strs.size();
}

// 十六进制
char from_hex(char ch) {
    return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
}

std::string json_dumps(const Json::Value& value){
    std::string result;
    Json::FastWriter writer;
    result = writer.write(value);
    boost::trim(result);
    return result;
}

int json_to_map(const Json::Value& v, std::map<std::string, std::string>& info_map) {
    Json::Value::Members mem = v.getMemberNames();
    for (auto iter = mem.begin(); iter != mem.end(); ++iter)
    {
        if (v[*iter].type() == Json::stringValue)
        {
            info_map[*iter] = v[*iter].asString();
        }
    }
    return 0;
}

int json_to_analysis_item(const Json::Value& v, AnalysisItem& analysis_item){
    if (v.isMember("id") && !v["id"].isNull()){
        analysis_item.id = v["id"].asString();
        DEBUG_LOG("in json_to_analysis_item, id:%s", analysis_item.id.c_str());
    }
    if (v.isMember("query") && !v["query"].isNull()){
        analysis_item.query = v["query"].asString();
        //DEBUG_LOG("in json_to_analysis_item, query:%s", analysis_item.query.c_str());
        DEBUG_LOG("in json_to_analysis_item, query_length:%d", analysis_item.query.length());
    }
    if (v.isMember("type") && !v["type"].isNull()) {
        analysis_item.type = v["type"].asInt();
        //DEBUG_LOG("in json_to_analysis_item, type:%d", analysis_item.type);
    }
    
    return 0;
}

int json_to_analysis_items(const Json::Value& v, std::vector<AnalysisItem>& analysis_items){
    const Json::Value& tb = v;
    if (v.type() != Json::arrayValue)
    {
        DEBUG_LOG("json_to_analysis_items err");
        return -1;
    }
    DEBUG_LOG("analysis_items length: %d", (int)tb.size());
    for (int i = 0; i < (int)tb.size(); i++)
    {
		AnalysisItem analysis_item;
		
        int ret = json_to_analysis_item(tb[i], analysis_item);
		if (ret != 0) {
			continue;
		}
		analysis_items.emplace_back(analysis_item);
	}

	return 0;
}

void print_analysis_result(std::vector<AnalysisItem>& analysis_items){
    for (int i = 0; i < analysis_items.size(); i++){
        DEBUG_LOG("query:%s", analysis_items[i].query.c_str());
    }
}

} // namespace nlper
