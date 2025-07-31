cmake_minimum_required(VERSION 3.5)

project(engine_total DESCRIPTION "Engine with test project" VERSION 1.0 LANGUAGES CXX)

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
	add_executable(engine_total WIN32 engine/main.cpp)
else()
	add_executable(engine_total WIN32 engine/main.cpp)
endif()

# Include headers from child project
target_include_directories(engine_total PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/engine/include
)

# Link the correct library depending on build type
target_link_libraries(engine_total PRIVATE
	$<$<CONFIG:Debug>:${ENGINE_LIB_DEBUG}>
	$<$<CONFIG:Release>:${ENGINE_LIB_RELEASE}>
)