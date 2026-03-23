//
// Created by secon on 2024/11/23.
//

#include "Derived.h"

void Base::display()
{
std::cout << "Base Virtual Func" << std::endl;
std::cout << "Private Num: " << privateNum << std::endl;
std::cout << "Protected Num: " << protectedNum << std::endl;
}