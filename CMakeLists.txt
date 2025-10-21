cmake_minimum_required(VERSION 3.5)
project(waffine)

set(CMAKE_CXX_STANDARD 20)
# Placing lib in build path for cereal imports
include_directories(lib)

add_subdirectory("lib")
add_subdirectory("src")
add_subdirectory("test")
