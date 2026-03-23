//
// Created by secon on 2024/9/21.
//
#include "global.h"
#include <iostream>

const int bufSize2 = 10;
void PrintBufAddress(){
    std::cout << "global.cpp buf address: " << &bufSize << std::endl;
    std::cout << "global.cpp buf2 address: " << &bufSize2 << std::endl;
}

int GetSize(){
    return 20;
}


