cmake_minimum_required(VERSION 3.25)
project(task1)

set(CMAKE_C_STANDARD 11)

# библиотека с функциями
add_library(lib src/functions.c)
target_include_directories(lib PUBLIC include)

# основной бинарник
add_executable(main main.c)
target_link_libraries(main lib)

# тесты
add_executable(tests tests/unit.c)
target_link_libraries(tests lib)
