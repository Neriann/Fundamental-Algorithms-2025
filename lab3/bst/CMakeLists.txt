cmake_minimum_required(VERSION 3.30)
project(bst C)

set(CMAKE_C_STANDARD 11)
set(DEBUG ../../debug)

include_directories(include)

add_executable(bst
        include/bst.h
        src/bst.c
        main.c
)

add_executable(tests
        include/bst.h
        src/bst.c
        tests/unit.c
        ${DEBUG}/assert_base.h
)
target_include_directories(tests PUBLIC ${DEBUG})
