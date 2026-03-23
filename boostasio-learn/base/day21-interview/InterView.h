//
// Created by secon on 2024/11/30.
//

#ifndef DAY21_INTERVIEW_INTERVIEW_H
#define DAY21_INTERVIEW_INTERVIEW_H

#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

class JoiningThread {
public:
    JoiningThread(const JoiningThread & src):_stop(false) { _i = src._i;
        _address = new int();
        _t = std::thread([this](){
            while(!_stop){
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        });

    }
    JoiningThread():_i(0){}
    JoiningThread(int i) : _i{i} {}
    int GetIndex() const { return _i; }
    ~JoiningThread() {
        _i = 0;
        std::cout << "~JoiningThread()" << std::endl;
        _stop = true;
        if(_t.joinable()){
            _t.join();
        }
        delete _address;
        _address = nullptr;
    }
private:
    std::thread _t;
    int _i;
    std::atomic<bool> _stop;
    int * _address = nullptr;
};



class InnerB {
public:
    InnerB() {
        std::cout << "InnerB()" << std::endl;
    }

    ~InnerB(){
        std::cout << "~InnerB()" << std::endl;
    }
};

class WrapperC {
public:
    WrapperC(){
        std::cout << "WrapperC()" << std::endl;
    }
    ~WrapperC(){
        std::cout << "~WrapperC()" << std::endl;
    }
    InnerB _inner;
};

class InnerA{
public:
    InnerA(){
        std::cout << "InnerA()" << std::endl;
    }
    ~InnerA(){
        std::cout << "~InnerA()" << std::endl;
    }
};

class InnerC{
public:
    InnerC(){
        std::cout << "InnerC()" << std::endl;
    }
    ~InnerC(){
        std::cout << "~InnerC()" << std::endl;
    }
};

class BaseA{
public:
    BaseA():BaseA(""){}
    BaseA(std::string name):_name(name){
        std::cout << "BaseA()" << std::endl;
    }

   virtual ~BaseA(){
        std::cout << "~BaseA()" << std::endl;
    }

private:
    InnerC _innerC;
    std::string _name;
};

class DerivedA: public BaseA {
public:
    DerivedA():DerivedA("",""){}
    DerivedA(std::string name,std::string num) :
            BaseA(name), _num(num) {
        std::cout << "DerivedA()" << std::endl;
    }

    ~DerivedA(){
        std::cout << "~DerivedA()" << std::endl;
    }
private:
    InnerA _innterA;
    InnerB _innerB;
    std::string _num;
};

class MyClass {
private:
    int value;
public:
    MyClass() : value(0) {}
    MyClass(int value) : value(value) {}
    MyClass(const MyClass& other) : value(other.value) {
        std::cout << "MyClass(const MyClass& other)" << std::endl;
    }
    MyClass& operator = (const MyClass& other){
        if(this == &other){
            return *this;
        }
        value = other.value;
        std::cout << "MyClass& operator = (const MyClass& other)" << std::endl;
        return * this;
    }
    MyClass& setValue(int value) {
        this->value = value;
        return *this; // 返回当前对象的引用
    }

    int getValue() const{
        return value;
    }

    void static print(){
        std::cout << "static print" << std::endl;
    }
};

class DefaultClass {
public:
    DefaultClass() = default;
    ~DefaultClass() = default;
    DefaultClass(const DefaultClass &) = delete;
    DefaultClass &operator=(const DefaultClass &) = delete;
    friend std::ostream& operator << (std::ostream &out, const DefaultClass &defaultClass);
private:
    int _num ;
};

class FileHandler {
    FILE* file;
public:
    FileHandler(const char* filename) {
        file = fopen(filename, "r");
        if (!file) throw std::runtime_error("打开文件失败");
    }
    ~FileHandler() {
        if (file) fclose(file);
    }
    // 禁止拷贝和移动
    FileHandler(const FileHandler&) = delete;
    FileHandler& operator=(const FileHandler&) = delete;
};

class MyLocker{
public:
    MyLocker(std::mutex & mtx):_mutex(mtx){
        std::cout << "MyLocker()" << std::endl;
        _mutex.lock();
    }

    ~MyLocker(){
        _mutex.unlock();
        std::cout << "~MyLocker()" << std::endl;
    }
private:
    std::mutex &_mutex;
};


class Baseclass
{

public:
    Baseclass() : a(1024) {}
    virtual void f() { std::cout << "Base::f" << std::endl; }
    virtual void g() { std::cout << "Base::g" << std::endl; }
    virtual void h() { std::cout << "Base::h" << std::endl; }
    int a;
};

// 0 1 2 3   4 5 6 7(虚函数表空间)    8 9 10 11 12 13 14 15(存储的是a)

class DeriveClass : public Baseclass
{
public:
    //override
    virtual void f() { std::cout << "Derive::f" << std::endl; }
    virtual void g2() { std::cout << "Derive::g2" << std::endl; }
    virtual void h3() { std::cout << "Derive::h3" << std::endl; }
};

typedef void (*Func)(void*);
extern void useVirtualTable();
extern void deriveTable();

// 基类 Device
class Device {
public:
    std::string brand;

    Device(const std::string& brand_) : brand(brand_) {}

    void showBrand() const {
        std::cout << "Brand: " << brand << std::endl;
    }
};

// 派生类 Laptop，虚继承 Device
class Laptop :  virtual public Device {
public:
    Laptop(const std::string& brand_) : Device(brand_) {}
};

// 派生类 Tablet，虚继承 Device
class Tablet :  virtual public Device {
public:
    Tablet(const std::string& brand_) : Device(brand_) {}
};

// 派生类 Convertible
class Convertible : public Laptop, public Tablet {
public:
    Convertible(const std::string& brand_) : Device(brand_), Laptop(brand_), Tablet(brand_) {}
};

#endif //DAY21_INTERVIEW_INTERVIEW_H
