//
// Created by secon on 2024/11/3.
//

#ifndef DAY17_FUNCTION_GLOBAL_H
#define DAY17_FUNCTION_GLOBAL_H
#include <iostream>

extern int multiply(int a, int b);
extern void changeValue(int num);
extern void changeValueR(int & num);
extern void changeValueP(int * num);
inline void printHello(){
    std::cout << "Hello" << std::endl;
}
#endif //DAY17_FUNCTION_GLOBAL_H
