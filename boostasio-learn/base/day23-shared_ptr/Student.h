//
// Created by secon on 2024/12/7.
//

#ifndef DAY22_MEMORY_STUDENT_H
#define DAY22_MEMORY_STUDENT_H
#include <string>
#include <iostream>
#include <memory>

class Student {
public:
    Student():age(7),name("student"){}
    Student(std::string name, int age):name(name),age(age){}
    ~Student() {
        std::cout << "Student::~Student()" << std::endl;
        std::cout << "name:" << name << std::endl;
    }
    void print() {
        std::cout << "name:" << name << std::endl;
    }
    std::string name;
    int age ;
};

class B;
class A{
public:
    std::shared_ptr<B> ptrB;
    A() {
        std::cout << "A()" << std::endl;
    }

    ~A() {
        std::cout << "~A()" << std::endl;
    }
};

class B{
public:
    std::weak_ptr<A> ptrA;
    B() {
        std::cout << "B()" << std::endl;
    }

    ~B() {
        std::cout << "~B()" << std::endl;
    }
};


#endif //DAY22_MEMORY_STUDENT_H
