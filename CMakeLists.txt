cmake_minimum_required(VERSION 3.3)

project(conversation)

enable_testing()

add_subdirectory(engine)

add_executable(total engine/main.cpp)
target_link_libraries(total engine)
