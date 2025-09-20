cmake_minimum_required(VERSION 3.25)

set(CMAKE_C_STANDARD 11)

set(HEADERS include/main.h)

project(task1)

add_executable(solution src/main.c ${HEADERS})
add_executable(run_tests tests/unit.c ${HEADERS})

#target_include_directories(solution PUBLIC include)
#target_include_directories(run_tests PUBLIC include)
