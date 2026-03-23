//
// Created by secon on 2024/12/7.
//

#ifndef DAY22_MEMORY_STUDENT_H
#define DAY22_MEMORY_STUDENT_H
#include <string>

class Student {
public:
    Student():age(7),name("student"){}
    Student(std::string name, int age):name(name),age(age){}
    std::string name;
    int age ;
};


#endif //DAY22_MEMORY_STUDENT_H
