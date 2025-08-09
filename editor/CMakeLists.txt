cmake_minimum_required(VERSION 3.5)

project(editor DESCRIPTION "Editor for engine" VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
execute_process(
    COMMAND {$CMAKE_CMOMAND} -E create_symlink
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_CURRENT_SOURCE_FIR}/compile_commands.json
)

set(ENGINE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../engine")

find_library(ENGINE_LIB_DEBUG
	NAMES engine
	PATHS "${ENGINE_DIR}/Debug"
)

find_library(ENGINE_LIB_RELEASE
	NAMES engine
	PATHS "${ENGINE_DIR}/Release"
)

if(NOT ENGINE_LIB_DEBUG)
	message(WARNING "Debug version of engine.lib not found")
else()
	message(STATUS "Debug version of engine.lib found")
endif()

if(NOT ENGINE_LIB_RELEASE)
	message(WARNING "Release version of engine.lib not found")
else()
	message(STATUS "Release version of engine.lib found")
endif()

set(EXE_FILES main.cpp Editor/Editor.cpp)

# Create executable
if(WIN32)
	add_executable(editor WIN32 ${EXE_FILES})
else()
	add_executable(editor ${EXE_FILES})

	find_package(glfw3 3.4 REQUIRED)
	target_link_libraries(editor PRIVATE glfw)
endif()

set_target_properties(editor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Release"
)

# Include headers from child project
target_include_directories(editor PRIVATE
	${ENGINE_DIR}/include
)

# Create symlink to compile_commands.json for IDE to pick it up
if(UNIX)
	execute_process(
		COMMAND ${CMAKE_COMMAND} -E create_symlink
		${CMAKE_BINARY_DIR}/compile_commands.json
		${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
	)
endif()

# Link the correct library depending on build type
target_link_libraries(editor PRIVATE
	$<$<CONFIG:Debug>:${ENGINE_LIB_DEBUG}>
	$<$<CONFIG:Release>:${ENGINE_LIB_RELEASE}>
)
