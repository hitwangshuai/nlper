INCLUDE(ExternalProject)
SET(OPTIONAL_ARGS
    "-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}"
    "-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}"
    "-DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}"
    "-DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}"
     "-Dprotobuf_WITH_ZLIB=ON"
     "-DZLIB_ROOT:FILEPATH=${ZLIB_ROOT}"
      ${EXTERNAL_OPTIONAL_ARGS})

SET(OPTIONAL_CACHE_ARGS "-DZLIB_ROOT:STRING=${ZLIB_ROOT}")
SET(PROTOBUF_SOURCES_DIR ${THIRD_PARTY_PATH}/protobuf)
SET(PROTOBUF_INSTALL_DIR ${THIRD_PARTY_PATH})

ExternalProject_Add(
    extern_protobuf
    ${EXTERNAL_PROJECT_LOG_ARGS}
    DEPENDS             extern_zlib
    DOWNLOAD_DIR        ${PROTOBUF_SOURCES_DIR}
    DOWNLOAD_COMMAND    cd ${PROTOBUF_SOURCES_DIR} && tar zxvf protobuf_3_1_0.tar.gz && cd ./protobuf
    PREFIX              ${PROTOBUF_SOURCES_DIR}
    CONFIGURE_COMMAND   cd ${PROTOBUF_SOURCES_DIR}/protobuf && ${CMAKE_COMMAND} -DCMAKE_SKIP_RPATH=ON
                        -Dprotobuf_BUILD_TESTS=OFF
                        -DCMAKE_POSITION_INDEPENDENT_CODE=ON
                        -DCMAKE_INSTALL_PREFIX=${PROTOBUF_INSTALL_DIR}
                        -DCMAKE_INSTALL_LIBDIR=lib ./cmake
    BUILD_COMMAND       cd ${PROTOBUF_SOURCES_DIR}/protobuf && make -j8 && make install
    UPDATE_COMMAND      ""
    INSTALL_COMMAND     ""
)

add_custom_command(TARGET extern_protobuf POST_BUILD
    COMMAND cp ${PROTOBUF_INSTALL_DIR}/bin/protoc ${PROTOBUF_INSTALL_DIR}/lib
)
