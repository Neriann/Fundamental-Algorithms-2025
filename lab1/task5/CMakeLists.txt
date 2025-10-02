cmake_minimum_required(VERSION 3.30)
project(task5 C)

set(CMAKE_C_STANDARD 11)
set(DEBUG ../../debug)

include_directories(include)
include_directories(${DEBUG})

add_executable(solution
        include/functions.h
        src/functions.c
        main.c)

add_executable(tests
        include/functions.h
        ${DEBUG}/assert_base.h
        src/functions.c
        tests/unit.c
)
