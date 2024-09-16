cmake_minimum_required(VERSION 3.15.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include GoogleTest
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


add_executable(
    MessagesTest
    Test_DelimitedMessagesStreamParser.cpp
    Test_Helpers.cpp
)

# Link GTest and pthread to your test executable
target_link_libraries(
    MessagesTest 
    GTest::gtest GTest::gtest_main
    Messages)

# Add tests
add_test(NAME MessagesTest COMMAND MessagesTest)