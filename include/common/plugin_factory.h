#ifndef NLPER_PLUGIN_FACTORY_H
#define NLPER_PLUGIN_FACTORY_H

#include "common/utils.h"

namespace nlper
{
// create插件的回调函数指针
typedef void* (*PluginCreateFunc)();
// 存放插件类型到插件回调函数的map
typedef std::unordered_map<std::string, PluginCreateFunc> PluginMap;

class PluginFactory {
public:
    // 注册组件回调函数
    int register_plugin(std::string plugin_type, PluginCreateFunc create_func);
    // 根据组件类型生成一个组件实例, 自己创建的实例自己销毁，工厂不负责
    void* create_plugin(std::string plugin_type);
    
    static PluginFactory& instance();

private:
    PluginMap _plugin_map;
};

#define PLUGIN_FACTORY nlper::PluginFactory::instance()

class Register {
public:
    Register(std::string plugin_type, PluginCreateFunc func) {
        PLUGIN_FACTORY.register_plugin(plugin_type, func);
    }
};

#define REGISTER_PLUGIN(plugin_type) \
namespace nlper { \
class plugin_type##Register { \
public: \
    static void* newInstance() { \
        return new plugin_type; \
    } \
private: \
    static const Register reg; \
};\
const Register plugin_type##Register::reg(#plugin_type, \
        plugin_type##Register::newInstance); \
}

} // namespace nlper

#endif  // NLPER_PLUGIN_FACTORY_H
