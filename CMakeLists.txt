cmake_minimum_required(VERSION 3.5)

project(engine_total DESCRIPTION "Engine with test project" VERSION 1.0 LANGUAGES CXX)

add_subdirectory(engine)

add_executable(total engine/main.cpp)
target_link_libraries(total engine)
