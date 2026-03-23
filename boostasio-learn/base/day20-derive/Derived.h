//
// Created by secon on 2024/11/23.
//

#ifndef DAY20_DERIVE_DERIVED_H
#define DAY20_DERIVE_DERIVED_H
#include <iostream>

class Base{
public:
    Base():privateNum(0), protectedNum(0){
        std::cout << "Base Constructor" << std::endl;
    }
    Base(int num1, int num2) : privateNum(num1), protectedNum(num2){
        std::cout << "Base Constructor" << std::endl;
    }
    virtual ~Base(){
        std::cout << "Base Destructor" << std::endl;
    }
    void baseFunc(){
        std::cout << "Base Func" << std::endl;
        std::cout << "Private Num: " << privateNum << std::endl;
        std::cout << "Protected Num: " << protectedNum << std::endl;
    }

    int baseFunc(int num1, int num2){
        return num1 + num2;
    }
     virtual void display();

private:
    int privateNum;
protected:
    int protectedNum;
};

class Vehicle{
public:
    virtual void startEngine() = 0;
};

class Car: public Vehicle{
public:
    Car(){
        std::cout << "Car Constructor" << std::endl;
    }
    void startEngine() override{
        std::cout << "Car Start Engine" << std::endl;
    }

};

class Motorcycle : public Vehicle {
public:
    Motorcycle() {
        std::cout << "Motorcycle Constructor" << std::endl;
    }
    void startEngine() override {
        std::cout << "Motorcycle engine started." << std::endl;
    }
};

class Derived: public Base {
public:
    Derived():Base(1,2){
        std::cout << "Derived Constructor" << std::endl;
    }
    Derived(int num1, int num2):Base(num1, num2){}
    ~Derived(){
          std::cout << "Derived Destructor" << std::endl;
    }
    void derivedFunc(){
        std::cout << "Derived Func" << std::endl;
        //std::cout << "Private Num: " << privateNum << std::endl;
        std::cout << "Protected Num: " << protectedNum << std::endl;
    }

    void display() override{
        std::cout << "Drived Virtual Func" << std::endl;
        std::cout << "Protected Num: " << protectedNum << std::endl;
    }

    void callBaseDisplay(){
        Base::display();
    }
private:
    Car _car;
    Motorcycle _motorcycle;
};

#endif //DAY20_DERIVE_DERIVED_H
