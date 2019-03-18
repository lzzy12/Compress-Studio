cmake_minimum_required(VERSION 3.13)

# Project
set(UTILS_SOURCES 
    archive.cpp 
    archive.h
    Core.h
    Utils.h
    zipper.cpp
    zipper.h
)
project(utils)
link_directories(${PROJECT_BINARY_DIR}/../vendor/zipper/$<CONFIGURATION>/)
add_library(${PROJECT_NAME} SHARED ${UTILS_SOURCES})
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PUBLIC CS_PLATFORM_WINDOWS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE CS_BUILD_DLL)
	target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
endif()
if(UNIX AND NOT APPLE)
    target_compile_definitions(${PROJECT_NAME} PUBLIC CS_PLATFORM_LINUX)
endif()
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../vendor/minizip)
target_link_libraries(${PROJECT_NAME} minizip)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_BINARY_DIR}/../cli/$<CONFIGURATION>/$<TARGET_FILE_NAME:${PROJECT_NAME}>
)