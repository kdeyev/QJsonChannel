cmake_minimum_required(VERSION 3.0)

project(QJsonChannelTufaoHttp VERSION 1.0)

find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
include(GenerateExportHeader)

set(CMAKE_INSTALL_PREFIX ../install)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES src/*.h)
set(CMAKE_AUTOMOC ON) # For meta object compiler

include_directories(src)
include_directories(../QJsonChannel/install/include/QJsonChannel)
include_directories(../tufao/install/include/tufao-1/Tufao)
link_directories(../QJsonChannel/install/lib)
link_directories(../tufao/install/lib)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${INCLUDE_FILES} ${META_FILES_TO_INCLUDE})
#set(CMAKE_CXX_VISIBILITY_PRESET hidden)
generate_export_header(${PROJECT_NAME})
include_directories(build)

qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Network)

target_link_libraries(${PROJECT_NAME} QJsonChannel tufao1d)

install(FILES ${INCLUDE_FILES} DESTINATION "include/${PROJECT_NAME}")
install(FILES build/qjsonchanneltufaohttp_export.h DESTINATION "include/${PROJECT_NAME}")
install(
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)
