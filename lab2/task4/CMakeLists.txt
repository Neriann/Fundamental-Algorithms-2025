cmake_minimum_required(VERSION 3.30)
project(task4 C)

set(CMAKE_C_STANDARD 11)
set(DEBUG ../../debug)

include_directories(include)
include_directories(${DEBUG})

add_executable(task4
        include/functions.h
        src/functions.c
        main.c
)

add_executable(tests
        include/functions.h
        src/functions.c
        ${DEBUG}/assert_base.h
        tests/unit.c

)
