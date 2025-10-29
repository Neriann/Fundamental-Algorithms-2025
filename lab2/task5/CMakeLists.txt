cmake_minimum_required(VERSION 3.30)
project(task5 C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(task5
    include/functions.h
    src/funstions.c
    main.c)

target_link_libraries(task5 m)
