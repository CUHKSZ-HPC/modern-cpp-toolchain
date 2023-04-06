cmake_minimum_required(VERSION 3.13.4)

add_executable(main main.cpp add.cpp)

if (MSVC)
    # warning level 4
    target_compile_options(main PRIVATE /W4)
else()
    # lots of warnings
    target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic)
endif()
