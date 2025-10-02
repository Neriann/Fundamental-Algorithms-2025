cmake_minimum_required(VERSION 3.30)
project(task6 C)

set(CMAKE_C_STANDARD 11)
set(DOUBLE_CALC_PATH ../task3)

include_directories(include ${DOUBLE_CALC_PATH}/include)


add_executable(solution
        include/functions.h
        src/functions.c
        ${DOUBLE_CALC_PATH}/include/double_calculations/functions.h
        ${DOUBLE_CALC_PATH}/src/functions.c
        main.c)

target_link_libraries(solution m)
