cmake_minimum_required(VERSION 3.30)
project(FA_LAB3_TASK4 C)

set(CMAKE_C_STANDARD 11)
set(DEBUG ../../debug)

include_directories(include)

add_executable(task4
    include/heap.h
    src/heap.c
    main.c
)

add_executable(tests
    include/heap.h
        src/heap.c
        tests/unit.c
        ${DEBUG}/assert_base.h
)

target_include_directories(tests PUBLIC ${DEBUG})
