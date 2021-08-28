#include "common/plugin_factory.h"

namespace nlper {

// 注册组件回调函数
int PluginFactory::register_plugin(std::string plugin_type, PluginCreateFunc create_func) {
    _plugin_map[plugin_type] = create_func;
    return 0;
}

// 根据组件类型生成一个组件实例, 自己创建的实例自己销毁，工厂不负责
void* PluginFactory::create_plugin(std::string plugin_type) {
    if (_plugin_map.count(plugin_type) < 1) {
        FATAL_LOG("create plugin[%s] failed.", plugin_type.c_str());
        return NULL;
    }
    return _plugin_map[plugin_type]();
}

PluginFactory& PluginFactory::instance() {
    static PluginFactory factory_ins;
    return factory_ins;
}

}
