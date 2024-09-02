cmake_minimum_required(VERSION 3.15.0)
cmake_policy(SET CMP0016 NEW)

project(protobuf-parser VERSION 1.0.0 DESCRIPTION "Разбор потока length-prefixed Protobuf сообщений")

include_directories(${CMAKE_SOURCE_DIR}/src)
enable_testing()
add_subdirectory(test)
add_subdirectory(src/protocol)

add_executable(protobuf_parser main.cpp)

target_link_libraries(protobuf_parser Messages ${PROTOBUF_DEPS})