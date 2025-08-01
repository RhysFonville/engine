cmake_minimum_required(VERSION 3.5)

project(editor DESCRIPTION "Editor for engine" VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ENGINE_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/engine/build")

find_library(ENGINE_LIB_DEBUG
	NAMES engine
	PATHS "${ENGINE_BUILD_DIR}/Debug"
)

find_library(ENGINE_LIB_RELEASE
	NAMES engine
	PATHS "${ENGINE_BUILD_DIR}/Release"
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

# Create executable
if(WIN32)
	add_executable(editor WIN32 engine/main.cpp)
else()
	add_executable(editor engine/main.cpp)

    find_package(glfw3 3.4 REQUIRED)
    target_link_libraries(editor PRIVATE glfw)
endif()

# Include headers from child project
target_include_directories(editor PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/engine/include
)

# Link the correct library depending on build type
target_link_libraries(editor PRIVATE
	$<$<CONFIG:Debug>:${ENGINE_LIB_DEBUG}>
	$<$<CONFIG:Release>:${ENGINE_LIB_RELEASE}>
)
