cmake_minimum_required(VERSION 3.0)

project(QJsonChannelTufaoHttp VERSION 1.0)

find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
include(GenerateExportHeader)

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE INCLUDE_FILES *.h)
set(CMAKE_AUTOMOC ON) # For meta object compiler

include_directories(src)
include_directories(../install/include)
include_directories(../install/include/QJsonChannel)
include_directories(../install/include/tufao-1)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${INCLUDE_FILES} ${META_FILES_TO_INCLUDE})
#set(CMAKE_CXX_VISIBILITY_PRESET hidden)
generate_export_header(${PROJECT_NAME})

qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Network)

target_link_libraries(${PROJECT_NAME} QJsonChannel tufao1)

install(FILES ${INCLUDE_FILES} DESTINATION "include/${PROJECT_NAME}")
install(
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)
