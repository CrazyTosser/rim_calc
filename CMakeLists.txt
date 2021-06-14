cmake_minimum_required(VERSION 3.19)
project(cvk)

set(CMAKE_CXX_STANDARD 17)

add_executable(cvk main.cpp)
add_compile_options(cvk public -Werror -Wall -Wextra -Wpedantic)