cmake_minimum_required(VERSION 3.0)

set(CMAKE_INSTALL_PREFIX install)

set(SERVICE_SRC_DIR ${PROJECT_SOURCE_DIR}/examples/service)

add_subdirectory(beast-server)
add_subdirectory(tufao-server)
add_subdirectory(qjsonchannel-hybrid)
add_subdirectory(qtwebchannel-hybrid)