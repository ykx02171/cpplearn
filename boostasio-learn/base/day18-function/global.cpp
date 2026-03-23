//
// Created by secon on 2024/11/3.
//
#include "global.h"
#include <iostream>

int multiply(int a, int b)
{
return a*b;
}

void changeValue(int num){
    num = 100;
    std::cout << "Inside function changeValue num: "<<num<<std::endl;
}

void changeValueR(int & num){
    num = 100;
    std::cout << "Inside function changeValueR num: "<<num<<std::endl;
}

void changeValueP(int * num){
    *num = 100;
    std::cout << "Inside function changeValueP num: "<<*num<<std::endl;
}