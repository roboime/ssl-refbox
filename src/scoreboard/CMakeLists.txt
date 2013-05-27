cmake_minimum_required(VERSION 2.8.2)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-2.4)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})


find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "-std=c++11")


set(src .)

set(PROTOS
    ${src}/../referee.proto
    #${src}/../savestate.proto
)

set(SOURCES
    ${src}/addrinfolist.cc
    ${src}/exception.cc
    ${src}/gamestate.cc
    ${src}/imagedb.cc
    ${src}/main.cc
    ${src}/mainwindow.cc
    ${src}/socket.cc
)

set(HEADERS
    ${src}/addrinfolist.h
    ${src}/exception.h
    ${src}/gamestate.h
    ${src}/imagedb.h
    ${src}/mainwindow.h
    ${src}/noncopyable.h
    ${src}/socket.h
)


protobuf_generate_cpp(PROTO_SOURCES PROTO_HEADERS ${PROTOS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(APPNAME scoreboard)
add_executable(${APPNAME} WIN32 ${SOURCES} ${HEADERS} ${PROTO_SOURCES} ${PROTO_HEADERS})
target_link_libraries(${APPNAME} ${GTKMM_LIBRARIES} ${PROTOBUF_LIBRARIES})
