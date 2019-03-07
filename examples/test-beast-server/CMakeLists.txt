cmake_minimum_required(VERSION 3.0)

project(test-beast-server VERSION 1.0)

find_package(Qt5Core REQUIRED)
find_package(Boost 1.69 COMPONENTS date_time REQUIRED )

file(GLOB_RECURSE SOURCE_FILES src/*.cpp ${SERVICE_SRC_DIR}/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES src/*.h)
set(CMAKE_AUTOMOC ON) # For meta object compiler

add_definitions(-D_WIN32_WINNT=0x0601)

include_directories(src)
include_directories(${SERVICE_SRC_DIR})
include_directories(${QJsonChannel_INCLUDE_DIR})
include_directories(${QJsonChannelBeast_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${INCLUDE_FILES})

qt5_use_modules(${PROJECT_NAME} Core)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} QJsonChannel QJsonChannelBeast)
install(
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)
