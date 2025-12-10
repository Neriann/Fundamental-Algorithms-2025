cmake_minimum_required(VERSION 3.30)
project(binomial_heap C)

set(CMAKE_C_STANDARD 11)
set(DEBUG ../../debug)

include_directories(include)

add_executable(binomial_heap
        include/binomial_heap.h
        src/binomial_heap.c
        main.c
)

add_executable(tests
        include/binomial_heap.h
        src/binomial_heap.c
        tests/unit.c
        ${DEBUG}/assert_base.h
)
target_include_directories(tests PUBLIC ${DEBUG})
