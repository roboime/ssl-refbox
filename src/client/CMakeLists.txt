cmake_minimum_required(VERSION 2.8.2)

find_package(Threads)
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-2.4)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "-std=c++11")


set(src .)

set(SOURCES
   ${src}/testclient.cc
)

set(PROTOS
    ${src}/../referee.proto
)


protobuf_generate_cpp(PROTO_SOURCES PROTO_HEADERS ${PROTOS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(APPNAME testclient)
add_executable(${APPNAME} WIN32 ${SOURCES} ${PROTO_SOURCES} ${PROTO_HEADERS})
target_link_libraries(${APPNAME} ${GTKMM_LIBRARIES} ${PROTOBUF_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
