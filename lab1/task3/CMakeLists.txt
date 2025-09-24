cmake_minimum_required(VERSION 3.25)

project(task3 C)

set(CMAKE_C_STANDARD 11)
set(DEBUG_DIR ../../debug)

add_library(lib src/functions.c)
target_include_directories(lib PUBLIC include)

add_executable(main main.c)
target_link_libraries(main lib m)

add_executable(tests tests/unit.c)
target_link_libraries(tests lib m)

target_include_directories(tests PRIVATE ${DEBUG_DIR})
