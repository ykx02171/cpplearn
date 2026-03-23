set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -save-temps=obj")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -save-temps=obj")

cmake_minimum_required(VERSION 3.28)
project(day03_scope)

set(CMAKE_CXX_STANDARD 17)

add_executable(day03_scope main.cpp)
