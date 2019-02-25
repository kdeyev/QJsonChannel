# Project QJsonChannel
project(QJsonChannel)

# Metadata
set(QJSONCHANNEL_VERSION_MAJOR 1)
set(QJSONCHANNEL_VERSION_MINOR 0)
set(QJSONCHANNEL_VERSION_PATCH 0)
set(QJSONCHANNEL_VERSION ${QJSONCHANNEL_VERSION_MAJOR}.${QJSONCHANNEL_VERSION_MINOR}.${QJSONCHANNEL_VERSION_PATCH})
set(QJSONCHANNEL_BRIEF "JSON-RPC Server side binding using Qt MOC")

# Dependencies
cmake_minimum_required(VERSION 2.8.11)
find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Boost 1.55 REQUIRED)

# CMake since 3.1 has ability to use particular C/C++ standarts.
# For versions before 3.1 use FindCXX11 module as fallback.
if("${CMAKE_VERSION}" VERSION_LESS "3.1")
    set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})
    find_package(CXX11 REQUIRED)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX11_FLAGS}")
endif()

get_target_property(QMAKE_EXECUTABLE Qt5::qmake LOCATION)
function(QUERY_QMAKE VAR RESULT)
    exec_program("${QMAKE_EXECUTABLE}" ARGS "-query ${VAR}" RETURN_VALUE return_code OUTPUT_VARIABLE output)
    if(NOT return_code)
        file(TO_CMAKE_PATH "${output}" output)
        set(${RESULT} ${output} PARENT_SCOPE)
    endif(NOT return_code)
endfunction(QUERY_QMAKE)

query_qmake(QT_INSTALL_PLUGINS QT_PLUGINS_DIR)
query_qmake(QT_HOST_DATA QT_DATA_DIR)

set(QT_MKSPECS_DIR ${QT_DATA_DIR}/mkspecs)

# Debug version of library should have 'd' postfix on Windows
# and '_debug' on Mac OS X
if(WIN32)
    set(CMAKE_DEBUG_POSTFIX "d")
elseif(APPLE)
    set(CMAKE_DEBUG_POSTFIX "_debug")
endif()

# Build info
set(QJSONCHANNEL_LIBRARY "QJsonChannel${QJSONCHANNEL_VERSION_MAJOR}")

# Install info
set(includedir include/QJsonChannel-${QJSONCHANNEL_VERSION_MAJOR})
set(libdir "lib${LIB_SUFFIX}")

# Targets
add_subdirectory(src)

# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

# cmake-modules
set(QJSONCHANNEL_CONFIG_INSTALL_DIR "${libdir}/cmake/QJsonChannel${QJSONCHANNEL_VERSION_MAJOR}")
include(CMakePackageConfigHelpers)
configure_package_config_file(
  QJsonChannelConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/QJsonChannel${QJSONCHANNEL_VERSION_MAJOR}Config.cmake"
  INSTALL_DESTINATION ${QJSONCHANNEL_CONFIG_INSTALL_DIR}
  PATH_VARS libdir
            includedir)

write_basic_config_version_file(QJsonChannel${QJSONCHANNEL_VERSION_MAJOR}ConfigVersion.cmake VERSION ${QJSONCHANNEL_VERSION} COMPATIBILITY ExactVersion)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QJsonChannel${QJSONCHANNEL_VERSION_MAJOR}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/QJsonChannel${QJSONCHANNEL_VERSION_MAJOR}ConfigVersion.cmake
        DESTINATION ${QJSONCHANNEL_CONFIG_INSTALL_DIR})

install(EXPORT "${QJSONCHANNEL_LIBRARY}-export" DESTINATION ${QJSONCHANNEL_CONFIG_INSTALL_DIR} FILE QJsonChannel${QJSONCHANNEL_VERSION_MAJOR}Targets.cmake)
