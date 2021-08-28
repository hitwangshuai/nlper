cmake_minimum_required(VERSION 3.0)
project(NLPER C CXX)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # require at least gcc 4.8
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.8)
        message(FATAL_ERROR "GCC is too old, sys supporting C++11")
    endif()
else()
    message(WARNING "You are using an unsupported compiler!")
endif()

SET(THIRD_PARTY_PATH ${CMAKE_BINARY_DIR}/third_party)
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

SET(PROTOC_BIN ${THIRD_PARTY_PATH}/bin/protoc)
SET(PROTO_SRC ${CMAKE_SOURCE_DIR}/src/config)
SET(PROTO_INC ${CMAKE_SOURCE_DIR}/include/config)
SET(PROTO_PATH ${CMAKE_SOURCE_DIR}/proto)
execute_process(COMMAND mkdir -p ${PROTO_SRC})
execute_process(COMMAND mkdir -p ${PROTO_INC})

include(external/boost)
include(external/zlib)
include(external/curl)
include(external/protobuf)
include(external/glog)
include(external/gflags)
include(external/gtest)
include(external/jsoncpp)
include(external/leveldb)
include(external/openssl)
include(external/brpc)
include(external/eigen)
include(external/semtopic)
include(proto_build)

include_directories(
    ${CMAKE_SOURCE_DIR}/include/
    ${CMAKE_SOURCE_DIR}/include/config
    ${THIRD_PARTY_PATH}/include/
    ${THIRD_PARTY_PATH}/include/eigen
)

link_directories(
    ${THIRD_PARTY_PATH}/lib
)

set(CMAKE_CXX_FLAGS "-g -pipe -W -Wall -fPIC -std=c++11 -mfpmath=sse -msse -msse2 -msse3 -fopenmp") 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-Bsymbolic -rdynamic -zmuldefs")

file(GLOB SRCS "src/*/*.cpp" "src/*/*.cc" "src/*/*/*.cpp" "src/*/*/*.cc")

file(GLOB PROTOS "${PROTO_PATH}/*.proto")
foreach(PROTO_FILE ${PROTOS})
    GET_FILENAME_COMPONENT(FILE_NAME ${PROTO_FILE} NAME_WE)
    SET(PROTO_CPP ${PROTO_SRC}/${FILE_NAME}.pb.cc)
    LIST(APPEND SRCS ${PROTO_CPP})
endforeach()

SET_SOURCE_FILES_PROPERTIES(${SRCS} PROPERTIES GENERATED TRUE)

add_library(nlper STATIC ${SRCS})

add_dependencies(nlper 
    extern_boost 
    extern_curl
    extern_eigen 
    extern_gtest 
    extern_brpc
    extern_jsoncpp
    extern_semtopic
    proto_build)

LIST(APPEND LIBS_LIST nlper
    ${THIRD_PARTY_PATH}/lib/libsemtopic.a
    ${THIRD_PARTY_PATH}/lib/libbrpc.a
    ${THIRD_PARTY_PATH}/lib/libgtest.a
    ${THIRD_PARTY_PATH}/lib/libgtest_main.a
    ${THIRD_PARTY_PATH}/lib/libcrypto.a
    ${THIRD_PARTY_PATH}/lib/libleveldb.a
    ${THIRD_PARTY_PATH}/lib/libssl.a
    ${THIRD_PARTY_PATH}/lib/libjsoncpp.a
    ${THIRD_PARTY_PATH}/lib/libprotobuf-lite.a
    ${THIRD_PARTY_PATH}/lib/libprotobuf.a
    ${THIRD_PARTY_PATH}/lib/libprotoc.a
    ${THIRD_PARTY_PATH}/lib/libgmock.a
    ${THIRD_PARTY_PATH}/lib/libgmock_main.a
    ${THIRD_PARTY_PATH}/lib/libglog.so
    ${THIRD_PARTY_PATH}/lib/libgflags.a
    ${THIRD_PARTY_PATH}/lib/libcurl.so
    dl
    rt
    ssl
    crypt
    crypto
    z
    m)
    
add_executable(run_server ${CMAKE_SOURCE_DIR}/demo/run_server.cpp)
target_link_libraries(run_server ${LIBS_LIST})

