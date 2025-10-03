cmake_minimum_required(VERSION 3.30)
project(task7 C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(solution
    include/functions.h
    src/functions.c
    tests/main.c)
