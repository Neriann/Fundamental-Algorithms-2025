cmake_minimum_required(VERSION 3.30)
project(task8 C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(task8
    include/functions.h
    src/functions.c
    main.c)
