cmake_minimum_required(VERSION 3.13)

# Project
project(CompressStudio)

option(BUILD_CLI "Build Console application" ON)

add_subdirectory(vendor/minizip)
add_subdirectory(CompressStudio)
if (BUILD_CLI)
    add_subdirectory(cli)
endif()