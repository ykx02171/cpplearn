cmake_minimum_required(VERSION 3.28)
project(29_unordermap)

set(CMAKE_CXX_STANDARD 17)

add_executable(29_unordermap main.cpp
        MyHashMap.cpp
        MyHashMap.h)
