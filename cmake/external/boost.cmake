INCLUDE(ExternalProject)

SET(BOOST_SOURCES_DIR ${THIRD_PARTY_PATH}/boost)
ExternalProject_Add(
    extern_boost
    ${EXTERNAL_PROJECT_LOG_ARGS}
    DOWNLOAD_DIR          ${BOOST_SOURCES_DIR}
    DOWNLOAD_COMMAND      cd ${BOOST_SOURCES_DIR} && tar -zxvf boost_1_41_0.tar.gz
    DOWNLOAD_NO_PROGRESS  1
    PREFIX                ${BOOST_SOURCES_DIR}
    CONFIGURE_COMMAND     ""
    BUILD_COMMAND         ""
    INSTALL_COMMAND       ""
    UPDATE_COMMAND        ""
    BUILD_IN_SOURCE      1
)

add_custom_command(TARGET extern_boost POST_BUILD
    COMMAND mkdir -p ${THIRD_PARTY_PATH}/include/
    COMMAND cp -rf ${BOOST_SOURCES_DIR}/boost_1_41_0/boost ${THIRD_PARTY_PATH}/include/
)
