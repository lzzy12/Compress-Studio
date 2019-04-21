cmake_minimum_required(VERSION 3.13)
message(STATUS "Using CMake version ${CMAKE_VERSION}")

option(CS_SHARED_LINK "Makes the project dynamically linked" OFF)
# Project
set(UTILS_SOURCES 
    archive.cpp 
    archive.h
    Core.h
    CS.h
    zipper.cpp
    zipper.h
)
project(CompressStudio)
link_directories(${PROJECT_BINARY_DIR}/../vendor/zipper/$<CONFIGURATION>/)


if(CS_SHARED_LINK)
	add_library(${PROJECT_NAME} SHARED ${UTILS_SOURCES})
else()
	add_library(${PROJECT_NAME} STATIC ${UTILS_SOURCES})
endif()

if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PUBLIC CS_PLATFORM_WINDOWS)
#    target_compile_definitions(${PROJECT_NAME} PRIVATE CS_BUILD_DLL)
	target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
endif()
if(UNIX AND NOT APPLE)
    target_compile_definitions(${PROJECT_NAME} PUBLIC CS_PLATFORM_LINUX)
endif()
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../vendor/minizip)
target_link_libraries(${PROJECT_NAME} minizip)

if(CS_SHARED_LINK)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_BINARY_DIR}/../cli/$<CONFIGURATION>/$<TARGET_FILE_NAME:${PROJECT_NAME}>
	)
endif()