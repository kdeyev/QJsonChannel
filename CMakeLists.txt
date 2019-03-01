cmake_minimum_required(VERSION 3.0)

set(CMAKE_INSTALL_PREFIX install)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY .)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY .)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY .)


add_subdirectory(src)
add_subdirectory(tufao)
add_subdirectory(QJsonChannelTufaoHttp)
add_subdirectory(examples/test-http-server)
