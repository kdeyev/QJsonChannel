cmake_minimum_required(VERSION 3.0)

project(QJsonChannel VERSION 1.0)

set(${PROJECT_NAME}_INCLUDE_DIR  ${PROJECT_SOURCE_DIR}/src PARENT_SCOPE)

find_package(Qt5Core REQUIRED)
include(GenerateExportHeader)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES src/*.h)
set(CMAKE_AUTOMOC ON) # For meta object compiler

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${INCLUDE_FILES} ${META_FILES_TO_INCLUDE})

generate_export_header(${PROJECT_NAME})
file(COPY ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_export.h DESTINATION ${PROJECT_SOURCE_DIR}/src)

qt5_use_modules(${PROJECT_NAME} Core)

install(FILES ${INCLUDE_FILES} DESTINATION "include/${PROJECT_NAME}")
install(
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)
