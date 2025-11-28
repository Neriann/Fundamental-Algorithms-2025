cmake_minimum_required(VERSION 3.30)
project(FA_LAB3_TASK7 C)

set(CMAKE_C_STANDARD 11)

add_executable(task7
        main.c
        src/interpreter.c
        include/interpreter.h
        src/operations.c
        include/operations.h
)

target_include_directories(task7 PUBLIC include)
