cmake_minimum_required(VERSION 3.28)
project(28_map)

set(CMAKE_CXX_STANDARD 17)

add_executable(28_map main.cpp
        MyMap.cpp
        MyMap.h
        AVLMap.cpp
        AVLMap.h)
