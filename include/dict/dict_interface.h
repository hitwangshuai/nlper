#ifndef NLPER_DICT_INTERFACE_H
#define NLPER_DICT_INTERFACE_H

#include <string>

#include "nlper.pb.h"
#include "common/common_define.h"

namespace nlper
{

// 字典接口
class DictInterface {
public:
    // 默认不支持reload
    DictInterface() {
        _support_reload = false;
        _dict = NULL;
    }

    // 根据路径和配置加载词典
    virtual int load(const std::string& path, const DictConfig& config) = 0;

    virtual int release() = 0;
    
    // 获取词典
    void* get_dict() {
        return _dict;
    }

    // 是否支持reload
    bool support_reload() {
        return _support_reload;
    }

    virtual ~DictInterface() {
    };

protected:
    // 设置是否支持reload
    void set_support_reload(const bool& support_reload){
        _support_reload = support_reload;
    }

    void set_dict(void* dict){
        _dict = dict;
    }

private:
    bool _support_reload;
    void* _dict;
    DISALLOW_COPY_AND_ASSIGN(DictInterface);
};

} // namespace nlper
#endif  //NLPER_DICT_INTERFACE_H
