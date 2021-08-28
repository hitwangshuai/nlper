#!/bin/bash

make clean

rm -rf ./third_party/install ./third_party/ssl ./third_party/lib ./third_party/bin ./third_party/include ./third_party/share
rm -rf CMakeFiles/ proto_build-prefix/ CMakeCache.txt cmake_install.cmake Makefile

rm -rf ./third_party/boost/src ./third_party/boost/tmp ./third_party/boost/boost_1_64_0 ./third_party/boost/boost_1_41_0
rm -rf ./third_party/brpc/src ./third_party/brpc/tmp ./third_party/brpc/brpc
rm -rf ./third_party/curl/src ./third_party/curl/tmp ./third_party/curl/curl
rm -rf ./third_party/eigen/src ./third_party/eigen/tmp ./third_party/eigen/eigen
rm -rf ./third_party/gflags/src ./third_party/gflags/tmp ./third_party/gflags/gflags
rm -rf ./third_party/glog/src ./third_party/glog/tmp ./third_party/glog/glog
rm -rf ./third_party/gtest/src ./third_party/gtest/tmp ./third_party/gtest/googletest
rm -rf ./third_party/jsoncpp/src ./third_party/jsoncpp/tmp ./third_party/jsoncpp/jsoncpp
rm -rf ./third_party/leveldb/src ./third_party/leveldb/tmp ./third_party/leveldb/leveldb
rm -rf ./third_party/lucenecpp/src ./third_party/lucenecpp/tmp ./third_party/lucenecpp/lucenecpp
rm -rf ./third_party/openssl/src ./third_party/openssl/tmp ./third_party/openssl/openssl
rm -rf ./third_party/paddle/src ./third_party/paddle/tmp ./third_party/paddle/Paddle
rm -rf ./third_party/protobuf/src ./third_party/protobuf/tmp ./third_party/protobuf/protobuf
rm -rf ./third_party/semword/src ./third_party/semword/tmp ./third_party/semword/semword
rm -rf ./third_party/semtopic/src ./third_party/semtopic/tmp ./third_party/semtopic/semtopic
rm -rf ./third_party/zlib/src ./third_party/zlib/tmp ./third_party/zlib/zlib

