cmake_minimum_required(VERSION 3.13)

project(cli)
set(CLI_SOURCES
    Main.cpp   
)
add_executable(${PROJECT_NAME} ${CLI_SOURCES})
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PUBLIC CS_PLATFORM_WINDOWS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE CS_BUILD_DLL)
	set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_COMMAND_ARGUMENTS "test1.zip ../../.git/")
endif()
if(UNIX AND NOT APPLE)
    target_compile_definitions(${PROJECT_NAME} PUBLIC CS_PLATFORM_LINUX)
endif()
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../CompressStudio)
target_link_libraries(${PROJECT_NAME} CompressStudio)
