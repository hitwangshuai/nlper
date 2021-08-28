#ifndef NLPER_SESSION_DATA_FACTORY_H
#define NLPER_SESSION_DATA_FACTORY_H

#include <string>
#include "brpc/data_factory.h"
#include "strategy/qdmatch_strategy.h"
#include "strategy/ddmatch_strategy.h"
#include "strategy/semtopic_strategy.h"

namespace nlper {

// 线程级数据
class SessionData {
public:
    SessionData();
    ~SessionData();
    // 使用全局字典和配置初始化nlper_strategy 
    int init(DictManager* ptr_dict_manager, const std::string& nlper_conf_file);
    
    QDMatchStrategy* get_qdmatch_strategy() {
        return &_qdmatch_strategy;
    }

    DDMatchStrategy* get_ddmatch_strategy() {
        return &_ddmatch_strategy;
    }

    SemtopicStrategy* get_semtopic_strategy() {
        return &_semtopic_strategy;
    }

private:
    QDMatchStrategy _qdmatch_strategy;
    DDMatchStrategy _ddmatch_strategy;
    SemtopicStrategy _semtopic_strategy;
    DISALLOW_COPY_AND_ASSIGN(SessionData);
};

class SessionDataFactory : public brpc::DataFactory
{
public:
    SessionDataFactory();
    SessionDataFactory(DictManager* ptr_dict_manager, const std::string& nlper_conf_file);
    ~SessionDataFactory();

    void* CreateData() const;
    void DestroyData(void* session_data) const;

private:
    // 词典是进程数据，以指针的形式传入，内存中只有一份词典
    DictManager* _dict_manager;
    std::string _nlper_conf_file;
    DISALLOW_COPY_AND_ASSIGN(SessionDataFactory);
};

} // namespace nlper

#endif  // NLPER_SESSION_DATA_FACTORY_H
