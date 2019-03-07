cmake_minimum_required(VERSION 3.0)

project(test-tufao-server VERSION 1.0)

find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp ${SERVICE_SRC_DIR}/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES src/*.h)
set(CMAKE_AUTOMOC ON) # For meta object compiler

include_directories(src)
include_directories(${SERVICE_SRC_DIR})
include_directories(${QJsonChannel_INCLUDE_DIR})
include_directories(${QJsonChannelTufao_INCLUDE_DIR})
include_directories(${TUFAO_INCLUDE_DIR})
link_directories(${TUFAO_LIB_DIR})

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${INCLUDE_FILES})

qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Network)

target_link_libraries(${PROJECT_NAME} QJsonChannelTufao QJsonChannel tufao1d)

install(
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)