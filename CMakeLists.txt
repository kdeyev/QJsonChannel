cmake_minimum_required(VERSION 3.0)

project(QJsonChannel VERSION 1.0)

set(SOURCE_FILES
    src/qjsonrpcmessage.cpp
    src/qjsonrpcservice.cpp
    src/qjsonrpcserviceprovider.cpp
)

add_definitions(-DTUFAO_LIBRARY)
if(NOT MSVC)
    add_definitions(
        -Wall
        -Wextra
#        -Wpedantic
#        -Weffc++
    )
endif()

find_package(Qt5Core REQUIRED)

set(CMAKE_AUTOMOC ON) # For meta object compiler

add_library("${PROJECT_NAME}" SHARED ${SOURCE_FILES} ${META_FILES_TO_INCLUDE})

qt5_use_modules(${PROJECT_NAME} Core)