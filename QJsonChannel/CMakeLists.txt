cmake_minimum_required(VERSION 3.0)

project(QJsonChannel VERSION 1.0)

find_package(Qt5Core REQUIRED)
include(GenerateExportHeader)

set(CMAKE_INSTALL_PREFIX ../install)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES src/*.h)
set(CMAKE_AUTOMOC ON) # For meta object compiler

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${INCLUDE_FILES} ${META_FILES_TO_INCLUDE})
generate_export_header(${PROJECT_NAME})
include_directories(build)

qt5_use_modules(${PROJECT_NAME} Core)

install(FILES ${INCLUDE_FILES} DESTINATION "include/${PROJECT_NAME}")
install(FILES build/qjsonchannel_export.h DESTINATION "include/${PROJECT_NAME}")
install(
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)
