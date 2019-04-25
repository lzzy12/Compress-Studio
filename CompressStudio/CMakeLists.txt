cmake_minimum_required(VERSION 3.13)
message(STATUS "Using CMake version ${CMAKE_VERSION}")

option(CS_SHARED_LINK "Makes the project dynamically linked" OFF)
# Project
set(UTILS_SOURCES 
    archive.cpp 
    include/archive.h
    include/Core.h
    include/CS.h
    zipper.cpp
    include/zipper.h
)
project(CompressStudio)
link_directories(${PROJECT_BINARY_DIR}/../vendor/zipper/$<CONFIGURATION>/)


if(CS_SHARED_LINK)
	add_library(${PROJECT_NAME} SHARED ${UTILS_SOURCES})
else()
	add_library(${PROJECT_NAME} STATIC ${UTILS_SOURCES})
endif()
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.4)
		message(FATAL_ERROR "You are on an extremely old version of GCC. Please update your compiler to at least GCC 5.4, preferably latest")
    elseif (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.0)
		message(WARNING "Old Verison of GCC detected. Using Legacy C++ support")
		target_compile_definitions(${PROJECT_NAME} PUBLIC LEGACY_CXX)
		target_link_libraries(${PROJECT_NAME} stdc++fs)
	endif()
	target_link_libraries(${PROJECT_NAME} stdc++fs)
endif()
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PUBLIC CS_PLATFORM_WINDOWS)
	#target_compile_definitions(${PROJECT_NAME} PRIVATE CS_BUILD_DLL)
endif()
if(UNIX AND NOT APPLE)
    target_compile_definitions(${PROJECT_NAME} PUBLIC CS_PLATFORM_LINUX)
endif()
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../vendor/minizip ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} minizip)
if(CS_SHARED_LINK)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_BINARY_DIR}/../cli/$<CONFIGURATION>/$<TARGET_FILE_NAME:${PROJECT_NAME}>
	)
endif()
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
