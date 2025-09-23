cmake_minimum_required(VERSION 3.25)

project(task2)

set(CMAKE_C_STANDARD 11)

add_library(lib src/functions.c)
target_include_directories(lib PUBLIC include)

add_executable(main main.c)
target_link_libraries(main lib)

add_executable(tests tests/unit.c)

target_link_libraries(tests lib)

target_include_directories(tests PRIVATE ../../debug)
