cmake_minimum_required(VERSION 3.5)

project(engine_total DESCRIPTION "Engine with test project" VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(engine)

add_executable(total engine/main.cpp)
target_link_libraries(total engine)
