cmake_minimum_required(VERSION 3.30)
project(task4 C)

set(CMAKE_C_STANDARD 11)


add_library(lib src/functions.c)

target_include_directories(lib PUBLIC include)

add_executable(main main.c)
target_link_libraries(main lib m)
