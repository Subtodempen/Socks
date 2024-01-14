cmake_minimum_required(VERSION 3.10)

project(Socks)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra -pedantic -g)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(bin ${SOURCES})
