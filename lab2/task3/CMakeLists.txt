cmake_minimum_required(VERSION 3.30)
project(task3 C)

set(CMAKE_C_STANDARD 11)
set(DEBUG ../../debug)

include_directories(include)
include_directories(${DEBUG})

add_executable(task3
        src/functions.c
        main.c
)

add_executable(tests
        src/functions.c
        tests/unit.c
)

target_link_libraries(tests m)
target_link_libraries(task3 m)
