INCLUDE(ExternalProject)

SET(LEVELDB_SOURCES_DIR ${THIRD_PARTY_PATH}/leveldb)
SET(LEVELDB_INSTALL_DIR ${THIRD_PARTY_PATH}/)
ExternalProject_Add(
    extern_leveldb
    ${EXTERNAL_PROJECT_LOG_ARGS}
    DOWNLOAD_DIR             ${LEVELDB_SOURCES_DIR}
    DOWNLOAD_COMMAND         cd ${LEVELDB_SOURCES_DIR} && tar zxvf leveldb_1_20.tar.gz && cd ./leveldb
    DOWNLOAD_NO_PROGRESS     1
    PREFIX                   ${LEVELDB_SOURCES_DIR}
    BUILD_COMMAND            ""
    UPDATE_COMMAND           ""
    CONFIGURE_COMMAND        ""
    INSTALL_COMMAND          cd ${LEVELDB_SOURCES_DIR}/leveldb/ 
                             && ./build_detect_platform build_config.mk ./ 
                             && make
    BUILD_IN_SOURCE          1
)

add_custom_command(TARGET extern_leveldb POST_BUILD
    COMMAND mkdir -p third_party/lib/
    COMMAND mkdir -p third_party/include/
    COMMAND cp -r ${LEVELDB_SOURCES_DIR}/leveldb/include/* ${LEVELDB_INSTALL_DIR}/include/
    COMMAND cp -r ${LEVELDB_SOURCES_DIR}/leveldb/out-static/lib* ${LEVELDB_INSTALL_DIR}/lib/
    COMMAND cp -r ${LEVELDB_SOURCES_DIR}/leveldb/out-shared/lib* ${LEVELDB_INSTALL_DIR}/lib/
)
