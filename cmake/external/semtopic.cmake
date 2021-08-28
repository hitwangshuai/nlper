INCLUDE(ExternalProject)

SET(SEMTOPIC_SOURCES_DIR ${THIRD_PARTY_PATH}/semtopic)
SET(SEMTOPIC_INSTALL_DIR ${THIRD_PARTY_PATH}/)
ExternalProject_Add(
    extern_semtopic
    ${EXTERNAL_PROJECT_LOG_ARGS}
    DEPENDS                 extern_protobuf extern_glog extern_gflags
    DOWNLOAD_DIR            ${SEMTOPIC_SOURCES_DIR}
    DOWNLOAD_COMMAND        cd ${SEMTOPIC_SOURCES_DIR} && tar zxvf semtopic_0_0_0.tar.gz
                            && cd ${SEMTOPIC_SOURCES_DIR}/semtopic/third_party
                            && tar -zxf protobuf_3_1_0.tar.gz && tar -zxf gflags_2_2_1.tar.gz && tar -zxf glog_0_3_5.tar.gz
                            && cd ./gflags && export CFLAGS=-fPIC && export CXXFLAGS=-fPIC
                            && cmake -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_LIBS=ON -DBUILD_TESTING=OFF -DCMAKE_INSTALL_PREFIX=${SEMTOPIC_SOURCES_DIR}/semtopic/third_party ./
                            && make -j8 && make install
    DOWNLOAD_NO_PROGRESS    1
    PREFIX                  ${SEMTOPIC_SOURCES_DIR}
    BUILD_COMMAND           cd ${SEMTOPIC_SOURCES_DIR}/semtopic/third_party/protobuf && export CFLAGS=-fPIC && export CXXFLAGS=-fPIC
                            && ./configure --disable-shared --prefix=${SEMTOPIC_SOURCES_DIR}/semtopic/third_party
                            && make -j8 && make install
    UPDATE_COMMAND          "" 
    CONFIGURE_COMMAND       cd ${SEMTOPIC_SOURCES_DIR}/semtopic/third_party/glog && export CFLAGS=-fPIC && export CXXFLAGS=-fPIC
                            && ./configure --prefix=${SEMTOPIC_SOURCES_DIR}/semtopic/third_party --with-gflags=${SEMTOPIC_SOURCES_DIR}/semtopic/third_party
                            && make -j8 && make install
    INSTALL_COMMAND         cd ${SEMTOPIC_SOURCES_DIR}/semtopic && make -j20
    BUILD_IN_SOURCE         1
)

add_custom_command(TARGET extern_semtopic POST_BUILD
    COMMAND mkdir -p ${SEMTOPIC_INSTALL_DIR}/include/
    COMMAND mkdir -p ${SEMTOPIC_INSTALL_DIR}/lib/
    COMMAND cp -rf ${SEMTOPIC_SOURCES_DIR}/semtopic/include/* ${SEMTOPIC_INSTALL_DIR}/include/
    COMMAND cp -rf ${SEMTOPIC_SOURCES_DIR}/semtopic/build/libsemtopic.a ${SEMTOPIC_INSTALL_DIR}/lib/
)
