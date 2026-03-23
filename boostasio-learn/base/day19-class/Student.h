//
// Created by secon on 2024/11/10.
//

#ifndef DAY19_CLASS_STUDENT_H
#define DAY19_CLASS_STUDENT_H
#include <string>
#include <iostream>
#include <thread>

struct StudentStruct{
    std::string name;
    int age;
    std::string num;
};

class Student {

    friend class Test;
public:
    Student();
    Student(const std::string& name, int age, const std::string& num);
    Student(const Student & student);
    Student(Student && student);
    ~Student();
    void ChangeName(const std::string& name){
        _name = name;
    }

    void ChangeAge(int age);

    void ChangeNum(const std::string& num);

    std::string GetName() const;

    int GetAge() const;

    std::string GetNum() const;

    void ChangeMoney(int money);
    int GetMoney();
    Student& operator=(const Student & student);
    Student& operator=(Student && student);
    static void TestStatic();
    Student& operator +(const Student & student);
    friend void ChangeAge(Student & student, int age);
    friend std::ostream& operator << (std::ostream & os,const Student & student);

private:
    std::string _name;
    int _age;
    std::string _num;
    //班费
    static int _money;
    std::thread _thread;
    int * _data;
};

class Test{
public:
    Test() = default;
    void ChangeAge(Student & student, int age){
        student._age = age;
    }
};

#endif //DAY19_CLASS_STUDENT_H
