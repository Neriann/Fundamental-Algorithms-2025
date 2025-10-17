cmake_minimum_required(VERSION 3.30)
project(task3 C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(task3
    include/functions.h
    src/functions.c
    main.c)
