#include <iostream>
#include "global.h"
#include <vector>
#include <algorithm>

//函数声明
int add(int a, int b);

//返回引用, 注意不要引用局部变量
int & getValue(){
    int a = 100;
    return a;
}

//返回指针，注意不要返回局部变量的地址
int * getValueP(){
    int a = 10;
    return &a;
}

int* allocateArray(int size){
    int* arr = new int[size];
    for(int i = 0; i < size; ++i){
        arr[i] = i*2;
    }
    return arr;
}

int& getMax(int& a, int& b){
    if(a > b){
        return a;
    }else{
        return b;
    }
}

void printNum(int num){
    std::cout << "num = " << num << std::endl;
}

void execute(void (* pfunc)()){
    //解引用调用
    (*pfunc)();
    //也可以不解引用
    pfunc();
}

void sayHello() {
    std::cout << "Hello World!" << std::endl;
}

int main() {
    auto result = add(5,3);
    std::cout << "result = " << result << std::endl;

    auto result2 = multiply(5,3);
    std::cout << "result2 = " << result2 << std::endl;

    int value = 30;
    changeValue(value);
    std::cout << "Outside function: " << value << std::endl;

    changeValueR(value);
    std::cout << "Outside function: " << value << std::endl;

    value = 200;
    changeValueP(&value);
    std::cout << "Outside function: " << value << std::endl;

//    auto getvalue = getValue();
//    std::cout << "value = " << getvalue << std::endl;
    int x = 10;
    int y = 20;
    int &max = getMax(x,y);
    std::cout << "max = " << max << std::endl;

//    int * p = getValueP();
//    std::cout << "*p = " << *p << std::endl;

    int * myArray = allocateArray(5);
    for(int i = 0; i < 5; ++i){
        std::cout << "myArray["<<i<<"] = " << myArray[i] << std::endl;
    }
    std::cout << std::endl;

    delete [] myArray;
    printHello();

    std::vector<int> numbers = {1,2,3,4};
    std::for_each(numbers.begin(), numbers.end(), printNum);
    std::for_each(numbers.begin(), numbers.end(), [](int num){
        std::cout << "num = " << num << std::endl;
    });

    int sum = 0;

    std::for_each(numbers.begin(),numbers.end(),[&sum](int num){
        sum += num;
    });
    std::cout << "sum = " << sum << std::endl;

    sum = 0;
    int * sum_addr = &sum;
    std::for_each(numbers.begin(),numbers.end(),[sum_addr](int num){
        *sum_addr += num;
    });
    std::cout << "sum = " << sum << std::endl;
    //指向数组的指针
    int num_array[5] = {1,2,3,4,5};
    int (* parray)[5] = &num_array;

    //指向函数的指针
    int (* padd) (int a, int b) = &add;
    int add_result = (*padd)(100,100);
    std::cout << "add_result = " << add_result << std::endl;
    //也可以不解引用
    add_result = padd(100,200);
    std::cout << "add_result = " << add_result << std::endl;

    execute(sayHello);
    return 0;
}

int add(int a, int b){
    return a + b;
}

