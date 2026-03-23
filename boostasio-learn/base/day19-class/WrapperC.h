//
// Created by secon on 2024/11/21.
//

#ifndef DAY19_CLASS_WRAPPERC_H
#define DAY19_CLASS_WRAPPERC_H
#include <iostream>
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


class BaseA{
public:
    BaseA(std::string name):_name(name){
        std::cout << "BaseA()" << std::endl;
    }

    virtual ~BaseA(){
        std::cout << "~BaseA()" << std::endl;
    }

private:
    std::string _name;
};

class DerivedA: public BaseA {
public:
    DerivedA(std::string name,std::string num) :
    BaseA(name), _num(num) {
        std::cout << "DerivedA()" << std::endl;
    }

    ~DerivedA(){
        std::cout << "~DerivedA()" << std::endl;
    }
private:
   std::string _num;
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


#endif //DAY19_CLASS_WRAPPERC_H
