cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG a33701196adfad74917046096bf5a2aa0ab0bb50 # 9.1.0
    FIND_PACKAGE_ARGS NAMES fmt
)
FetchContent_MakeAvailable(fmt)
find_package(fmt REQUIRED)

project(cursed-timers CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -Wno-unused-parameter -Werror)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/utf-8 /W3 /WX /sdl)
endif()

add_executable(fastsleep fastsleep.cpp)
target_link_libraries(fastsleep PRIVATE winmm.lib fmt::fmt)

add_executable(change_interval change_interval.cpp)
target_link_libraries(change_interval PRIVATE winmm.lib)
add_executable(measure_interval measure_interval.cpp)
target_link_libraries(measure_interval PRIVATE winmm.lib)
