//
// Created by secon on 2024/11/10.
//

#include "Student.h"

int Student::_money = 100;

void Student::ChangeAge(int age){
    _age = age;
}

std::string Student::GetName() const{
   return _name;
}

void Student::ChangeNum(const std::string& num){
    _num = num;
}

int Student:: GetAge() const{
    return _age;
}

std::string Student::GetNum() const{
    return _num;
}

Student::Student():_age(0),_name("路人甲"),_num("0"){
    _data = new int();
}

Student::Student(const std::string& name, int age, const std::string& num)
               :_name(name),_age(age),_num(num)
{
    _data = new int();
}

Student::Student(const Student &student):
    _name(student._name), _age(student._age),_num(student._num){
    _data = new int();
    *_data = *(student._data);
}

void Student::ChangeMoney(int cost){
    _money -= cost;
}
int Student::GetMoney(){
    std::cout << "this value is " << this << std::endl;
    return _money;
}

Student::Student(Student && student):
_name(std::move(student._name)),_age(student._age),_num(std::move(student._num)),_thread(std::move(student._thread))
{
    _data = new int();
    *_data = std::move(*(student._data));
}

Student::~Student(){
    std::cout << "Student::~Student()" << std::endl;
    if(_thread.joinable()){
        _thread.join();
    }
    delete _data;
    std::cout << "Student::~Student() success" << std::endl;
}

Student &Student::operator=(const Student &student) {
    if(this == &student){
        return *this;
    }

    this->_name = student._name;
    this->_age = student._age;
    this->_num = student._num;
    (*_data) = *(student._data);
    return * this;
}

void Student::TestStatic() {
  std::cout << "money is " << _money << std::endl;
}

Student &Student::operator=(Student &&student) {
    if(this == &student){
        return *this;
    }
    this->_name = std::move(student._name);
    this->_age = student._age;
    this->_num = student._num;
    *(this->_data) = std::move(*(student._data));

    return *this;
}

Student &Student::operator+(const Student &student) {

    this->_age += student._age;
    return *this;
}

void ChangeAge(Student & student, int age){
    student._age = age;
}

std::ostream& operator << (std::ostream & os,const Student & student){
    os << "student name is " << student._name << std::endl <<
    "age is " << student._age << std::endl
    << "num is " << student._num << std::endl;
    return os;
}
