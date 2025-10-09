cmake_minimum_required(VERSION 3.30)
project(task2 C)

set(CMAKE_C_STANDARD 11)
set(DEBUG_DIR ../../debug)

include_directories(include)
include_directories(${DEBUG_DIR})

add_executable(task2
        include/functions.h
        include/errors.h
        src/functions.c
        main.c)

add_executable(tests
        include/functions.h
        src/functions.c
        tests/unit.c
        ${DEBUG_DIR}/assert_base.h
)
