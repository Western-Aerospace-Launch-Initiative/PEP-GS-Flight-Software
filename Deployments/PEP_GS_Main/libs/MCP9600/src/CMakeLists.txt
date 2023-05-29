cmake_minimum_required(VERSION 3.18)

project(MCP9600)

add_library(MCP9600 MCP9600.c)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/test/ut)
