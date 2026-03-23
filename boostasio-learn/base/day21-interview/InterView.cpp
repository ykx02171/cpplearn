//
// Created by secon on 2024/11/30.
//

#include "InterView.h"

std::ostream& operator << (std::ostream &out, const DefaultClass &defaultClass){
    std::cout << "DefaultClass num is " << defaultClass._num << std::endl;
}

void useVirtualTable(){
    Baseclass b;
    b.a = 1024;
    b.f();
    void** vtable = *(void ***)(&b);
    std::cout << "vtable address is" << vtable << std::endl;
    Func pf = (Func)vtable[0];
    //b.f()
    pf(&b);

    pf = (Func)vtable[1];
    pf(&b);

    pf = (Func)vtable[2];
    pf(&b);

    std::cout << "size of int is : " << sizeof(int) << std::endl;

    std::cout << "size of Baseclass is : " << sizeof(b) << std::endl;

    char* objBytes = (char*)&b;
    size_t vptrSize = sizeof(void*);
    int * aPtr = (int*)(objBytes+vptrSize);
    std::cout << "Value of a is : " << *aPtr << std::endl;

}

void deriveTable(){
    DeriveClass b;
    b.a = 1025;
    void** vtable = *(void ***)(&b);
    std::cout << "vtable address is" << vtable << std::endl;
    Func pf = (Func)vtable[0];
    //b.f()
    pf(&b);

    pf = (Func)vtable[1];
    pf(&b);

    pf = (Func)vtable[2];
    pf(&b);
}