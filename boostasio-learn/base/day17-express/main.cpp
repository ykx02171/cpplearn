#include <iostream>
#include "express.h"

int main() {
    system("chcp 65001");
    print99();
    int array[] = {6,1,0,5,2,9};
    bubbleSort(array, 6);
    printArray(array,6);

    // 生成斐波那契数列
    std::vector<unsigned long long> fibonacci = generateFibonacci(7);

    // 打印斐波那契数列
    std::cout << "斐波那契数列:" << std::endl;
    printFibonacci(fibonacci);

    std::vector<unsigned long long> fibonacci2 = generateFibonacciRecursive(7);
    // 打印斐波那契数列
    std::cout << "斐波那契数列:" << std::endl;
    printFibonacci(fibonacci);

    auto fibonacci3 = fibonacci_dynamic(7);
    // 打印斐波那契数列
    std::cout << "斐波那契数列:" << std::endl;
    printFibonacci(fibonacci);
    return 0;
}
