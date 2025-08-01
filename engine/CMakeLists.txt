cmake_minimum_required(VERSION 3.5)
project(engine DESCRIPTION "C++ Cross-Platform Rendering Engine" VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create the library
add_library(engine STATIC
	include/engine/util/defines.h
	include/engine/util/debug.h
	include/engine/Window.h
	include/engine/util/vector.h
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

set_target_properties(engine PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}"
)

set_target_properties(engine PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(engine PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

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

add_executable(log_test tests/log_test.cpp)
target_link_libraries(log_test PRIVATE engine)
add_test(NAME log_test COMMAND log_test)

add_executable(window_test tests/window_test.cpp)
target_link_libraries(window_test PRIVATE engine)
add_test(NAME window_test COMMAND window_test)