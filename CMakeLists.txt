cmake_minimum_required(VERSION 3.30)
project(steganography_config C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -pedantic -pedantic-errors -Wall -Wextra -Werror")

add_subdirectory(lib)
