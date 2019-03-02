cmake_minimum_required(VERSION 3.0)

project(test_http_server VERSION 1.0)

find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES src/*.h)
set(CMAKE_AUTOMOC ON) # For meta object compiler

include_directories(src)
include_directories(../../QJsonChannel/install/include/QJsonChannel)
include_directories(../../tufao/install/include/tufao-1/Tufao)
include_directories(../../QJsonChannelTufaoHttp/install/include/QJsonChannelTufaoHttp)
link_directories(../../QJsonChannel/install/lib)
link_directories(../../tufao/install/lib)
link_directories(../../QJsonChannelTufaoHttp/install/lib)


add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${INCLUDE_FILES})

qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Network)

target_link_libraries(${PROJECT_NAME} QJsonChannelTufaoHttp QJsonChannel tufao1d)

