cmake_minimum_required(VERSION 3.8)

# Project
project(CompressStudio)

option(BUILD_CLI "Build Console application" ON)

add_subdirectory(vendor/minizip)
add_subdirectory(utils)

if (BUILD_CLI)
    add_subdirectory(cli)
endif()