#include <iostream>
#include "derived.h"

int main() {
    //std::cout << "Hello, World!" << std::endl;
//    Derived d(10,20);
//    d.derivedFunc();
//    d.baseFunc();

//    Derived d2;
//    d2.derivedFunc();
//    d2.baseFunc();
//    d2.display();
//    d2.callBaseDisplay();
//
//    Base* bp = new Derived();
//    bp->display();

//    Vehicle * pcar = new Car();
//    pcar->startEngine();
//
//    Vehicle * pmt = new Motorcycle();
//    pmt -> startEngine();

//    Derived d2;
//    Base b;
//    b.baseFunc();
//    std::cout << b.baseFunc(1,2) << std::endl;
    Base *bp =  new Derived();
    delete bp;
    return 0;
}
