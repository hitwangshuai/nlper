#include "server/session_data_factory.h"

namespace nlper {

SessionData::SessionData() {
}

SessionData::~SessionData() {
}

int SessionData::init(DictManager* ptr_dict_manager, const std::string& nlper_conf_file) {
    if (ptr_dict_manager == NULL) {
        FATAL_LOG("ptr_dict_manager is NULL");
        return -1;
    }
    
    if (_qdmatch_strategy.create_resource(*ptr_dict_manager, nlper_conf_file) != 0) {
        FATAL_LOG("qdmatch_strategy create resource failed, nlper_conf_file=%s", nlper_conf_file.c_str());
        return -1;
    }
    if (_ddmatch_strategy.create_resource(*ptr_dict_manager, nlper_conf_file) != 0) {
        FATAL_LOG("ddmatch_strategy create resource failed, nlper_conf_file=%s", nlper_conf_file.c_str());
        return -1;
    }
    if (_semtopic_strategy.create_resource(*ptr_dict_manager, nlper_conf_file) != 0) {
        FATAL_LOG("semtopic_strategy create resource failed, nlper_conf_file=%s", nlper_conf_file.c_str());
        return -1;
    }
    return 0;
}

SessionDataFactory::SessionDataFactory() {
}

SessionDataFactory::~SessionDataFactory() {
}

SessionDataFactory::SessionDataFactory(DictManager* ptr_dict_manager,
        const std::string& nlper_conf_file) {
    _dict_manager = ptr_dict_manager;
    _nlper_conf_file = nlper_conf_file;
}

void* SessionDataFactory::CreateData() const {
    if (_dict_manager == NULL) {
        FATAL_LOG("_dict_manager is NULL");
        return NULL;
    }
    SessionData* sd = new SessionData();
    if (sd->init(_dict_manager, _nlper_conf_file) != 0) {
        FATAL_LOG("session data init failed.");
        return NULL;
    }
    DEBUG_LOG("session data init success!!!");

    return static_cast<void*>(sd);
}

void SessionDataFactory::DestroyData(void* session_data) const {
    delete static_cast<SessionData*>(session_data);
}

}
