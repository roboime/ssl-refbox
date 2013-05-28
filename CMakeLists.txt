cmake_minimum_required(VERSION 2.8.2)
project(ssl-refbox)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-2.4)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "-std=c++11")

set(src ${CMAKE_SOURCE_DIR}/src)

set(SOURCES
    ${src}/addrinfolist.cc
    ${src}/configuration.cc
    ${src}/exception.cc
    ${src}/gamecontroller.cc
    ${src}/legacypublisher.cc
    ${src}/logger.cc
    ${src}/main.cc
    ${src}/mainwindow.cc
    ${src}/protobufpublisher.cc
    ${src}/savegame.cc
    ${src}/socket.cc
    ${src}/teams.cc
    ${src}/timing.cc
    ${src}/udpbroadcast.cc
)

set(HEADERS
    ${src}/addrinfolist.h
    ${src}/configuration.h
    ${src}/exception.h
    ${src}/gamecontroller.h
    ${src}/legacypublisher.h
    ${src}/logger.h
    ${src}/mainwindow.h
    ${src}/noncopyable.h
    ${src}/protobufpublisher.h
    ${src}/publisher.h
    ${src}/savegame.h
    ${src}/socket.h
    ${src}/teams.h
    ${src}/timing.h
    ${src}/udpbroadcast.h
)

set(PROTOS
    ${src}/referee.proto
    ${src}/savestate.proto
)


protobuf_generate_cpp(PROTO_SOURCES PROTO_HEADERS ${PROTOS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${src}/referee.conf DESTINATION ${CMAKE_BINARY_DIR})

set(APPNAME sslrefbox)
add_executable(${APPNAME} WIN32 ${SOURCES} ${HEADERS} ${PROTO_SOURCES} ${PROTO_HEADERS})
target_link_libraries(${APPNAME} ${GTKMM_LIBRARIES} ${PROTOBUF_LIBRARIES})

option(BUILD_SCOREBOARD "Also build scoreboard along with the refbox?" ON)
if(BUILD_SCOREBOARD)
    add_subdirectory(src/scoreboard)
endif()

option(BUILD_TESTCLIENT "Also build testclient along with the refbox?" ON)
if(BUILD_TESTCLIENT)
    add_subdirectory(src/client)
endif()
