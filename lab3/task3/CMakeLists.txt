cmake_minimum_required(VERSION 3.30)
project(FA_LAB3_TASK3 C)

set(CMAKE_C_STANDARD 11)
set(DEBUG ../../debug)


add_library(LIB src/liver.c)
target_include_directories(LIB PUBLIC include)

add_executable(task3
        main.c
)

target_link_libraries(task3 LIB)


add_executable(list_tests
        ${DEBUG}/assert_base.h
        tests/list_liver_test.c
)

target_include_directories(list_tests PUBLIC ${DEBUG})
target_link_libraries(list_tests LIB)
