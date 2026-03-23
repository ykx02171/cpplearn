cmake_minimum_required(VERSION 3.28)
project(day19_class)

set(CMAKE_CXX_STANDARD 17)

add_executable(day19_class main.cpp
        Student.cpp
        Student.h
        JoiningThread.cpp
        JoiningThread.h
        MyString.cpp
        MyString.h
        WrapperC.cpp
        WrapperC.h
)
