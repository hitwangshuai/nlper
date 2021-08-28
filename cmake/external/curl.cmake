include(ExternalProject)

SET(CURL_SOURCES_DIR ${THIRD_PARTY_PATH}/curl)
ExternalProject_Add(
    extern_curl
    ${EXTERNAL_PROJECT_LOG_ARGS}
    DOWNLOAD_DIR          ${CURL_SOURCES_DIR}
    DOWNLOAD_COMMAND      cd ${CURL_SOURCES_DIR} && tar -zxvf curl_7_60_0.tar.gz
    DOWNLOAD_NO_PROGRESS  1
    PREFIX                ${CURL_SOURCES_DIR}
    CONFIGURE_COMMAND     cd ${CURL_SOURCES_DIR}/curl && ./configure --prefix=${THIRD_PARTY_PATH} --without-ssl 
    BUILD_COMMAND         cd ${CURL_SOURCES_DIR}/curl && make
    INSTALL_COMMAND       cd ${CURL_SOURCES_DIR}/curl && make install
    UPDATE_COMMAND        ""
)
