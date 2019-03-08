cmake_minimum_required(VERSION 3.0)

set(CMAKE_INSTALL_PREFIX install)

set(SERVICE_SRC_DIR ${PROJECT_SOURCE_DIR}/examples/service)

# server
add_subdirectory(beast-server)
add_subdirectory(tufao-server)
# hybrid
add_subdirectory(qtwebchannel-hybrid)
add_subdirectory(qjsonchannel-hybrid)