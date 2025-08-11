cmake_minimum_required(VERSION 3.5)
project(engine DESCRIPTION "C++ Cross-Platform Rendering Engine" VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(INCLUDE_DIR include/engine)

# Create the library
add_library(engine STATIC
	# Header files not needed, just good for IDEs (like visual studio)
	${INCLUDE_DIR}/util/defines.h
	${INCLUDE_DIR}/util/debug.h
	${INCLUDE_DIR}/Window.h
	${INCLUDE_DIR}/util/vector.h
	${INCLUDE_DIR}/Window_win32.h
	${INCLUDE_DIR}/Window_apple.h
	${INCLUDE_DIR}/AssetManager/AssetManager.h
	${INCLUDE_DIR}/AssetManager/AssetLoader.h
	${INCLUDE_DIR}/AssetManager/TextLoader.h
    ${INCLUDE_DIR}/Input/InputSet.h
    ${INCLUDE_DIR}/Input/Key.h
    ${INCLUDE_DIR}/Input/Keybind.h
	${INCLUDE_DIR}/Engine.h
	${INCLUDE_DIR}/VisualInterface.h
	${INCLUDE_DIR}/Scene/Object.h
	${INCLUDE_DIR}/Scene/Scene.h
	${INCLUDE_DIR}/Scene/World.h

	src/Window.cpp
	src/AssetManager/AssetManager.cpp
	src/AssetManager/AssetLoader.cpp
	src/AssetManager/TextLoader.cpp
    src/Input/InputSet.cpp
	src/Engine.cpp
	src/VisualInterface.cpp
	src/Scene/Object.cpp
	src/Scene/Scene.cpp
	src/Scene/World.cpp
)

if(WIN32)
	target_sources(engine PRIVATE src/Window_win32.cpp)
elseif(APPLE)
	target_sources(engine PRIVATE src/Window_apple.cpp)

	find_package(Vulkan REQUIRED)
	target_link_libraries(engine PRIVATE ${Vulkan_INCLUDE_DIRS})

	find_package(glfw3 3.4 REQUIRED)
	target_link_libraries(engine PRIVATE glfw)
endif()

# Set the include directory (public API)
target_include_directories(engine PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

set_target_properties(engine PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(engine PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

set(DEBUG_DIR ${CMAKE_SOURCE_DIR}/Debug)
set(RELEASE_DIR ${CMAKE_SOURCE_DIR}/Release)

set_target_properties(engine PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${DEBUG_DIR}"
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${RELEASE_DIR}"
	LIBRARY_OUTPUT_DIRECTORY_DEBUG   "${DEBUG_DIR}"
	LIBRARY_OUTPUT_DIRECTORY_RELEASE "${RELEASE_DIR}"
	RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${DEBUG_DIR}"
	RUNTIME_OUTPUT_DIRECTORY_RELEASE "${RELEASE_DIR}"
)

# Create symlink to compile_commands.json for IDE to pick it up
if(UNIX)
	execute_process(
		COMMAND ${CMAKE_COMMAND} -E create_symlink
		${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/compile_commands.json
		${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
	)
endif()

# Define export symbol macro when building the library
target_compile_definitions(engine PRIVATE ENGINE_EXPORTS)

# Make the library installable
include(GNUInstallDirs)

install(TARGETS engine
	EXPORT engine_targets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/engine
)

install(EXPORT engine_targets
	NAMESPACE Engine::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/engine
)

# Testing setup
enable_testing()

macro(add_engine_test test_name)
	add_executable(${test_name} tests/${test_name}.cpp)
	target_link_libraries(${test_name} PRIVATE engine)
	add_test(NAME ${test_name} COMMAND ${test_name})
	set_target_properties(${test_name} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${DEBUG_DIR}/tests"
		RUNTIME_OUTPUT_DIRECTORY_RELEASE "${RELEASE_DIR}/tests"
	)
endmacro()

add_engine_test(log_test)
add_engine_test(window_test)
add_engine_test(asset_manager_test)
add_engine_test(scene_test)

