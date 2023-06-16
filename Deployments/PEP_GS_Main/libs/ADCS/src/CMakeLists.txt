cmake_minimum_required(VERSION 3.13)

project(ADCS)

add_library(bootloader bootloader.c)
add_library(common common.c)
add_library(cubeacp cubeacp.c)
add_library(cubeadcs cubeadcs.c)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/test/ut)

add_compile_options(-Wall -Wextra -Wpedantic)
