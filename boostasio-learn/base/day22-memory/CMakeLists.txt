cmake_minimum_required(VERSION 3.28)
project(day22_memory)

set(CMAKE_CXX_STANDARD 17)

add_executable(day22_memory main.cpp
        Student.cpp
        Student.h
        DynamicArray.cpp
        DynamicArray.h
        MemoryPool.cpp
        MemoryPool.h)
