cmake_minimum_required(VERSION 3.30)
project(task4 C)

set(CMAKE_C_STANDARD 11)
set(DEBUG_DIR ../../debug)
set(PRIMES_PATH ../task2)


add_library(primes_lib ${PRIMES_PATH}/src/functions.c)
target_include_directories(primes_lib PUBLIC ${PRIMES_PATH}/include)

add_library(lib src/functions.c src/constants.c)
target_include_directories(lib PUBLIC
        include
        ${PRIMES_PATH}/include
)

add_executable(main main.c)
target_link_libraries(main lib primes_lib m)

add_executable(tests tests/unit.c)
target_link_libraries(tests lib primes_lib m)

target_include_directories(tests PUBLIC
        ${DEBUG_DIR}
)
