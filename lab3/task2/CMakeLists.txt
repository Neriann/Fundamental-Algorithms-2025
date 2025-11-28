cmake_minimum_required(VERSION 3.30)
project(FA_LAB3_TASK2 C)

set(CMAKE_C_STANDARD 11)
set(DEBUG ../../debug)

include_directories(include)

add_executable(tests_int tests/test_vector_int.c
        include/vector.h
        ${DEBUG}/assert_base.h
)

add_executable(tests_struct tests/test_vector_struct.c
        include/vector.h
        ${DEBUG}/assert_base.h
)

target_include_directories(tests_int PUBLIC ${DEBUG})
target_include_directories(tests_struct PUBLIC ${DEBUG})
