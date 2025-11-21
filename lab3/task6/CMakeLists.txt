cmake_minimum_required(VERSION 3.30)
project(task6 C)

set(CMAKE_C_STANDARD 11)
set(DEBUG ../../debug)

include_directories(include)

add_executable(task6
        include/functions.h
        src/functions.c
        main.c)

add_executable(tests
        include/functions.h
        src/functions.c
        ${DEBUG}/assert_base.h
        tests/unit.c
)

target_include_directories(tests PUBLIC ${DEBUG})
