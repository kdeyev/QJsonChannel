cmake_minimum_required(VERSION 3.0)

project(QJsonChannelBeast VERSION 1.0)

set(${PROJECT_NAME}_INCLUDE_DIR  ${PROJECT_SOURCE_DIR}/src PARENT_SCOPE)

find_package(Qt5Core REQUIRED)
find_package(Boost 1.69 COMPONENTS date_time REQUIRED )

include(GenerateExportHeader)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES src/*.h)

add_definitions(-D_WIN32_WINNT=0x0601)

include_directories(src)
include_directories(${QJsonChannelCore_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${INCLUDE_FILES})

generate_export_header(${PROJECT_NAME})
file(COPY ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_export.h DESTINATION ${PROJECT_SOURCE_DIR}/src)

qt5_use_modules(${PROJECT_NAME} Core)
target_link_libraries(${PROJECT_NAME} QJsonChannelCore)

install(FILES ${INCLUDE_FILES} DESTINATION "include/${PROJECT_NAME}")
install(
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)
