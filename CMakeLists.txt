cmake_minimum_required(VERSION 3.17)
project(assignment_8 C)

set(CMAKE_C_STANDARD 90)

add_executable(assignment_8 main.c)

find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME} Threads::Threads)