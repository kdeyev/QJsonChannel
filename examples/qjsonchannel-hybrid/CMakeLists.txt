cmake_minimum_required(VERSION 3.0)

project(qjsonchannel-hybrid VERSION 1.0)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5WebChannel REQUIRED)
find_package(Qt5WebEngineWidgets REQUIRED)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp ${SERVICE_SRC_DIR}/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES src/*.h)
set(CMAKE_AUTOMOC ON) # For meta object compiler
set(CMAKE_AUTORCC ON) 

include_directories(src)
include_directories(${SERVICE_SRC_DIR})
include_directories(${QJsonChannelCore_INCLUDE_DIR})
include_directories(${QJsonChannelEmbed_INCLUDE_DIR})

qt5_add_resources(QRCS src/resources.qrc)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${INCLUDE_FILES} ${QRCS})

qt5_use_modules(${PROJECT_NAME} Core Widgets WebChannel WebEngineWidgets)

target_link_libraries(${PROJECT_NAME} QJsonChannelCore QJsonChannelEmbed)
install(
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# PATH variable for VS
configure_file(../project.vcxproj.user.in ${CMAKE_BINARY_DIR}/examples/${PROJECT_NAME}/${PROJECT_NAME}.vcxproj.user @ONLY) 