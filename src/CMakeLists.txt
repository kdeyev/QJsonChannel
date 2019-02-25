# Source files
set(QJsonChannel_SRC
    qjsonrpcmessage.cpp
    qjsonrpcservice.cpp
    qjsonrpcserviceprovider.cpp
)

add_definitions(-DQJSONRPC_BUILD)
if(NOT MSVC)
    add_definitions(
#        -Wall
#        -Wextra
#        -Wpedantic
#        -Weffc++
    )
endif()

add_library("${QJSONCHANNEL_LIBRARY}" SHARED ${QJsonChannel_SRC})

target_link_libraries("${QJSONCHANNEL_LIBRARY}" Qt5::Core)

set_target_properties(
    "${QJSONCHANNEL_LIBRARY}"
    PROPERTIES
    SOVERSION ${QJSONCHANNEL_VERSION_MAJOR}
    VERSION ${QJSONCHANNEL_VERSION}
    VS_KEYWORD Qt4VSv1.0
    AUTOMOC ON
    INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/${libdir}"
)

# CXX_STANDARD was introduced in CMake 3.1
if("${CMAKE_VERSION}" VERSION_GREATER "3.0")
    set_target_properties(
        "${QJSONCHANNEL_LIBRARY}"
        PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
    )
endif()

if("${CMAKE_VERSION}" VERSION_LESS "2.8.12")
  target_include_directories("${QJSONCHANNEL_LIBRARY}" INTERFACE "${CMAKE_INSTALL_PREFIX}/${includedir}")
  install(TARGETS "${QJSONCHANNEL_LIBRARY}" EXPORT "${QJSONCHANNEL_LIBRARY}-export"
          LIBRARY DESTINATION "${libdir}"
          ARCHIVE DESTINATION "${libdir}"
          RUNTIME DESTINATION bin
          PUBLIC_HEADER DESTINATION "${includedir}"
  )
else()
  # Support relocatable packages. It can be usefull on Windows
  install(TARGETS "${QJSONCHANNEL_LIBRARY}" EXPORT "${QJSONCHANNEL_LIBRARY}-export"
          LIBRARY DESTINATION "${libdir}"
          ARCHIVE DESTINATION "${libdir}"
          RUNTIME DESTINATION bin
          PUBLIC_HEADER DESTINATION "${includedir}" INCLUDES DESTINATION "${includedir}"
  )
endif()

# Tests
if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Install info
install(TARGETS "${QJSONCHANNEL_LIBRARY}"
    DESTINATION "${libdir}"
    COMPONENT runtime
)
install(DIRECTORY .
    DESTINATION "${includedir}/QJsonChannel"
    COMPONENT development
    FILES_MATCHING PATTERN *.h
    PATTERN doc EXCLUDE
    PATTERN priv EXCLUDE
    PATTERN tests EXCLUDE
)
