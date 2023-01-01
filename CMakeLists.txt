cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 20)

project(cursed-timers CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wno-unused-parameter -Werror)
add_executable(fastboi main.cpp)
target_link_libraries(fastboi PRIVATE winmm.lib)

add_executable(change_interval change_interval.cpp)
add_executable(measure_interval measure_interval.cpp)