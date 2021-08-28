INCLUDE(ExternalProject)

SET(BRPC_SOURCES_DIR ${THIRD_PARTY_PATH}/brpc)
SET(BRPC_INSTALL_DIR ${THIRD_PARTY_PATH}/)
ExternalProject_Add(
    extern_brpc
    ${EXTERNAL_PROJECT_LOG_ARGS}
    DEPENDS                extern_protobuf extern_glog extern_gflags extern_leveldb extern_openssl 
    DOWNLOAD_DIR           ${BRPC_SOURCES_DIR}
    DOWNLOAD_COMMAND       cd ${BRPC_SOURCES_DIR} && tar zxvf brpc_0_9_0.tar.gz
    DOWNLOAD_NO_PROGRESS   1
    PREFIX                 ${BRPC_SOURCES_DIR}
    BUILD_COMMAND          ""
    UPDATE_COMMAND         ""
    CONFIGURE_COMMAND      ""
    INSTALL_COMMAND        cd ${BRPC_SOURCES_DIR}/brpc && export PATH=${THIRD_PARTY_PATH}/bin:$ENV{PATH}
                           && bash config_brpc.sh --headers=${BRPC_INSTALL_DIR}/include --libs=${BRPC_INSTALL_DIR}/lib --with-glog
                           && make
    BUILD_IN_SOURCE 1

)

add_custom_command(TARGET extern_brpc POST_BUILD
    COMMAND mkdir -p third_party/lib/
    COMMAND mkdir -p third_party/include/
    COMMAND cp -r ${BRPC_SOURCES_DIR}/brpc/output/* ${BRPC_INSTALL_DIR}/
)
