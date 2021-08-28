#ifndef NLPER_DUAL_DICT_WRAPPER_H
#define NLPER_DUAL_DICT_WRAPPER_H

#include <string>
#include <mutex>

#include "dict/dict_interface.h"

namespace nlper
{
// 封装DictInterface类，通过Dual Dict 实现reload机制
class DualDictWrapper {
public:
    // 保存dict的路径和配置
    DualDictWrapper(const std::string& conf_path, const DictConfig& config);

    int reload();
    
    int release();
    
    DictInterface* get();
    
    void* get_dict();
    
    ~DualDictWrapper();
    
    bool is_reload_able() {
        return _reload_able;
    }
    
    std::string get_dict_name() {
        return _dict_name;
    }

public:
    std::string _dict_name;
    std::string _dict_path;
    DictConfig _config;
    bool _reload_able;

    // 双词典
    DictInterface* _dual_dict[2];
    
    // 词典标示，通过判断标示变化决定是否reload
    std::string _last_identifier;
    
    // 互斥锁
    std::mutex _mutex;
    
    // 当前使用的词典index
    uint8_t _cur_dict;
};

} // namespace nlper
#endif  //NLPER_DUAL_DICT_WRAPPER_H
