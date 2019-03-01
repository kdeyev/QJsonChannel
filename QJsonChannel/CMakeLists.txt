cmake_minimum_required(VERSION 3.0)

project(QJsonChannel VERSION 1.0)

find_package(Qt5Core REQUIRED)
include(GenerateExportHeader)

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE INCLUDE_FILES *.h)
set(CMAKE_AUTOMOC ON) # For meta object compiler

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${INCLUDE_FILES} ${META_FILES_TO_INCLUDE})
generate_export_header(${PROJECT_NAME})

qt5_use_modules(${PROJECT_NAME} Core)

install(FILES ${INCLUDE_FILES} DESTINATION "include/${PROJECT_NAME}")
install(FILES qjsonchannel_export.h DESTINATION "include/${PROJECT_NAME}")
install(
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)
