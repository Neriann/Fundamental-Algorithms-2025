cmake_minimum_required(VERSION 3.30)
project(FA_LAB3_TASK1 C)

set(CMAKE_C_STANDARD 11)
set(DEBUG ../../debug)

include_directories(include)
include_directories(${DEBUG})

add_executable(task1
        src/functions.c
    main.c)

add_executable(tests
        src/functions.c
        tests/unit.c
        ${DEBUG}/assert_base.h
)
