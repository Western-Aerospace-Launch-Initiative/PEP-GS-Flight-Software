cmake_minimum_required(VERSION 3.13)

project(ADCS_Tests)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include_directories(../../)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
#FetchContent_MakeAvailable(googletest)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()
enable_testing()

add_executable(
    ADCS_Tests
  TestMain.cpp
)
target_link_libraries(
    ADCS_Tests
    GTest::gtest_main
    bootloader
    common
    cubeacp
    cubeadcs
)

include(GoogleTest)
gtest_discover_tests(ADCS_Tests)

#Autorun UT
#add_custom_command(
#        TARGET MCP9600_Tests
#        POST_BUILD
#        COMMENT "Running Unit Tests..."
#        COMMAND ./MCP9600_Tests
#        )

