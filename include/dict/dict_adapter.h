#ifndef NLPER_DICT_ADAPTER_H
#define NLPER_DICT_ADAPTER_H

#include <fstream>
#include <mutex>
#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>
#include <stdlib.h>

#include "semtopic/tokenizer.h"
#include "semtopic/inference.h"
#include "semtopic/matcher.h"

#include "common/utils.h"
#include "dict/dict_interface.h"

namespace nlper
{

// KV词典模板类
template <class T1, class T2>
class HashAdapter : public DictInterface {
    typedef std::unordered_map<T1, T2> hash_type;
public:
    // KV类型词典支持reload
    HashAdapter() {
        set_support_reload(true);
    }

    virtual ~HashAdapter() override {
        void* dict = get_dict();
        if (dict != NULL) {
            delete static_cast<hash_type*>(dict);
        }
    }

    virtual int load(const std::string& path, const DictConfig& config) override {
        hash_type* tmp_dict = new hash_type();
        if (tmp_dict == NULL) {
            FATAL_LOG("new string2float dict error");
            return -1;
        }
        DEBUG_LOG("%s", path.c_str());
        // KV词典load
        int ret = hash_load(path.c_str(), (*tmp_dict));
        if (ret != 0) {
            FATAL_LOG("load string2float dict %s error", path.c_str());
            return -1;
        }
        set_dict((void*)tmp_dict);
        return 0;
    }

    virtual int release() override {
        void* dict = get_dict();
        if (dict != NULL) {
            hash_type* tmp_dict = static_cast<hash_type*>(dict);
            tmp_dict->clear();
            delete tmp_dict;
            set_dict(NULL);
        }
        return 0;
    }

    int get(const std::string& key, std::string& value) {
        hash_type* tmp_dict = static_cast<hash_type*>(get_dict());
        typename hash_type::const_iterator it = tmp_dict->find(key);
        if (it != tmp_dict->end()) {
            value = it->second;
        } else {
            WARNING_LOG("key[%s] not exist!", key.c_str());
            return -1;
        }
        return 0;
    }

private:
    DISALLOW_COPY_AND_ASSIGN(HashAdapter);
};

typedef HashAdapter<std::string, float> String2FloatAdapter;

typedef HashAdapter<std::string, int> String2IntAdapter;

typedef HashAdapter<std::string, std::string> String2StringAdapter;

// semtopic词典
struct SemtopicPack {
    semtopic::Tokenizer* tokenizer;
    semtopic::InferenceEngine *lda_engine;
    semtopic::InferenceEngine *slda_engine;
    semtopic::TopicalWordEmbedding* twe;
};

class SemtopicAdapter : public DictInterface {
public:
    SemtopicAdapter();
    virtual ~SemtopicAdapter() override;
    virtual int load(const std::string& path, const DictConfig& config) override;
    virtual int release() override;
private:
    DISALLOW_COPY_AND_ASSIGN(SemtopicAdapter);
};

} //namespace nlper

#endif  //NLPER_DICT_ADAPTER_H
