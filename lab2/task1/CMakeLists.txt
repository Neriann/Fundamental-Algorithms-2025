cmake_minimum_required(VERSION 3.30)
project(task1 C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(task1
    include/functions.h
    src/functions.c
    main.c)
