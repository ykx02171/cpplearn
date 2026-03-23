cmake_minimum_required(VERSION 3.28)
project(day05_extern)

set(CMAKE_CXX_STANDARD 17)

add_executable(day05_extern main.cpp
        global.h
        global.cpp)
