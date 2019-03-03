cmake_minimum_required(VERSION 3.0)

project(test-embed-qtwebchannel VERSION 1.0)

find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Widgets REQUIRED)
#find_package(Qt5WebSockets REQUIRED)
find_package(Qt5WebChannel REQUIRED)
find_package(Qt5WebEngineWidgets REQUIRED)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES src/*.h)
set(CMAKE_AUTOMOC ON) # For meta object compiler
set(CMAKE_AUTORCC ON) 

include_directories(src)

qt5_add_resources(QRCS src/resources.qrc)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${INCLUDE_FILES} ${QRCS})

qt5_use_modules(${PROJECT_NAME} Core Network Widgets WebChannel WebEngineWidgets)

target_link_libraries(${PROJECT_NAME})

