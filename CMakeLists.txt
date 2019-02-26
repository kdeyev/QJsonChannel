cmake_minimum_required(VERSION 3.0)

project(QJsonChannel VERSION 1.0)

find_package(Boost 1.69 REQUIRED)
find_package(Qt5Core REQUIRED)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES src/*.h)
set(CMAKE_AUTOMOC ON) # For meta object compiler

add_definitions(-DQJSONRPC_BUILD)

add_library("${PROJECT_NAME}" SHARED ${SOURCE_FILES} ${INCLUDE_FILES} ${META_FILES_TO_INCLUDE})

qt5_use_modules(${PROJECT_NAME} Core)