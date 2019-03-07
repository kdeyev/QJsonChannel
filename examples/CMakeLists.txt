cmake_minimum_required(VERSION 3.0)

set(CMAKE_INSTALL_PREFIX install)

add_subdirectory(test-beast-server)
add_subdirectory(test-tufao-server)
add_subdirectory(test-embed-qtwebchannel)
add_subdirectory(test-embed-qjsonchannel)