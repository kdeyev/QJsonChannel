cmake_minimum_required(VERSION 3.0)

project(QJsonChannelBeast VERSION 1.0)

find_package(Qt5Core REQUIRED)
find_package(Boost 1.69 COMPONENTS date_time REQUIRED )

include(GenerateExportHeader)

set(CMAKE_INSTALL_PREFIX ../install)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES src/*.h)

add_definitions(-D_WIN32_WINNT=0x0601)

include_directories(src)
include_directories(../QJsonChannel/install/include/QJsonChannel)
link_directories(../QJsonChannel/install/lib)
include_directories( ${Boost_INCLUDE_DIR} )
link_directories(${Boost_LIBRARY_DIRS})

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${INCLUDE_FILES})
generate_export_header(${PROJECT_NAME})
include_directories(build)

qt5_use_modules(${PROJECT_NAME} Core)
target_link_libraries(${PROJECT_NAME} QJsonChannel)

install(FILES ${INCLUDE_FILES} DESTINATION "include/${PROJECT_NAME}")
install(FILES build/QJsonChannelBeast_export.h DESTINATION "include/${PROJECT_NAME}")
install(
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)
