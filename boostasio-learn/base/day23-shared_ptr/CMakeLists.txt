cmake_minimum_required(VERSION 3.28)
project(day23_shared_ptr)

set(CMAKE_CXX_STANDARD 17)

add_executable(day23_shared_ptr main.cpp
        Student.cpp
        Student.h
        SimpleSharedPtr.cpp
        SimpleSharedPtr.h
)
