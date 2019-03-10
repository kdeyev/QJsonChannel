cmake_minimum_required(VERSION 3.0)

set(CMAKE_INSTALL_PREFIX install)


set(TUFAO_LIB_DIR ${PROJECT_SOURCE_DIR}/tufao/install/lib)
set(TUFAO_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/tufao/install/include/tufao-1/Tufao)

add_subdirectory(QJsonChannelCore)
add_subdirectory(QJsonChannelBeast)

add_subdirectory(QJsonChannelTufao)

add_subdirectory(QJsonChannelEmbed)

add_subdirectory(examples)

