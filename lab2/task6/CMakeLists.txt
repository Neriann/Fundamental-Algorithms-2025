cmake_minimum_required(VERSION 3.30)
project(task6 C)

set(CMAKE_C_STANDARD 11)
set(DEBUG ../../debug)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -g")

include_directories(include)
include_directories(${DEBUG})

add_executable(task6
        include/functions.h
        src/functions.c
        main.c)

add_executable(tests
        include/functions.h
        src/functions.c
        tests/unit.c
        ${DEBUG}
)
