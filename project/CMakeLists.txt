cmake_minimum_required(VERSION 3.5)
project(project DESCRIPTION "Test project for editor and engine" VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(INCLUDE_DIR include/project)

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
	message(WARNING "Debug version of engine library not found")
else()
	message(STATUS "Debug version of engine library found")
endif()

if(NOT ENGINE_LIB_RELEASE)
	message(WARNING "Release version of engine library not found")
else()
	message(STATUS "Release version of engine library found")
endif()

add_library(project SHARED
	${INCLUDE_DIR}/MyObject.h
	src/MyObject.cpp
)

target_include_directories(project PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${ENGINE_DIR}/include
	${ENGINE_DIR}/nlohmann_json/include
)

target_link_libraries(project PRIVATE
	$<$<CONFIG:Debug>:${ENGINE_LIB_DEBUG}>
	$<$<CONFIG:Release>:${ENGINE_LIB_RELEASE}>
)

set(DEBUG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Debug)
set(RELEASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Release)

set_target_properties(project PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${DEBUG_DIR}"
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${RELEASE_DIR}"
	LIBRARY_OUTPUT_DIRECTORY_DEBUG   "${DEBUG_DIR}"
	LIBRARY_OUTPUT_DIRECTORY_RELEASE "${RELEASE_DIR}"
	RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${DEBUG_DIR}"
	RUNTIME_OUTPUT_DIRECTORY_RELEASE "${RELEASE_DIR}"
)

