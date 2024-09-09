cmake_minimum_required(VERSION 3.15.0)

set(PROTOBUF_TARGET_NAME Messages)

find_package(Protobuf REQUIRED)

set(PROTO_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS Messages.proto)

add_library(${PROTOBUF_TARGET_NAME} ${PROTO_SRCS} ${PROTO_HDRS})

target_link_libraries(${PROTOBUF_TARGET_NAME} PUBLIC protobuf::libprotobuf)