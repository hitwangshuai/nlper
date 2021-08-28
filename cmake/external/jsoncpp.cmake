INCLUDE(ExternalProject)

SET(JSONCPP_SOURCES_DIR ${THIRD_PARTY_PATH}/jsoncpp)
SET(JSONCPP_INSTALL_DIR ${THIRD_PARTY_PATH}/install/jsoncpp)
ExternalProject_Add(
    extern_jsoncpp
    DOWNLOAD_DIR          ${JSONCPP_SOURCES_DIR}
    DOWNLOAD_COMMAND      cd ${JSONCPP_SOURCES_DIR} && tar zxvf jsoncpp_1_8_4.tar.gz && cd ./jsoncpp
    DOWNLOAD_NO_PROGRESS  1
    PREFIX              ${JSONCPP_SOURCES_DIR}
    CONFIGURE_COMMAND   cd ${JSONCPP_SOURCES_DIR}/jsoncpp && ${CMAKE_COMMAND} -DCMAKE_INSTALL_LIBDIR=lib -DCMAKE_INSTALL_PREFIX=${THIRD_PARTY_PATH} CMakeLists.txt
    BUILD_COMMAND       cd ${JSONCPP_SOURCES_DIR}/jsoncpp && make -j8
    INSTALL_COMMAND     cd ${JSONCPP_SOURCES_DIR}/jsoncpp && make install 
    UPDATE_COMMAND      ""
)

LIST(APPEND external_project_dependencies jsoncpp)
