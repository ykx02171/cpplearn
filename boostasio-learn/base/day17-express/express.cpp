//
// Created by secon on 2024/11/3.
//
#include "express.h"
#include <iostream>
#include <vector>
// 9*9乘法表
void print99(){
    // 外层循环控制行数
    for (int i = 1; i <= 9; ++i) {
        // 内层循环控制列数
        for (int j = 1; j <= 9; ++j) {
            std::cout << i << "x" << j << "=" << i * j << "\t";
        }
        std::cout << std::endl; // 每行结束后换行
    }
}

// 冒泡排序函数
void bubbleSort(int arr[], int n) {
    bool swapped;
    // 外层循环控制总的遍历次数
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        // 内层循环进行相邻元素的比较和交换
        for (int j = 0; j < n - i - 1; ++j) {
            // 如果前一个元素大于后一个元素，则交换它们
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // 如果在一轮遍历中没有进行任何交换，数组已经有序
        if (!swapped) {
            break;
        }
    }
}

// 打印数组函数
void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// 生成斐波那契数列的函数（迭代法）
std::vector<unsigned long long> generateFibonacci(int n) {
    std::vector<unsigned long long> fib;

    if (n <= 0) {
        // 返回空向量
        return fib;
    }

    // 第一个斐波那契数
    fib.push_back(0);

    if (n == 1) {
        return fib;
    }

    // 第二个斐波那契数
    fib.push_back(1);

    // 生成后续的斐波那契数
    for (int i = 2; i < n; ++i) {
        unsigned long long next = fib[i - 1] + fib[i - 2];
        fib.push_back(next);
    }

    return fib;
}

// 递归函数，计算第 n 个斐波那契数
unsigned long long fibonacciRecursive(int n) {
    if (n < 0) {
        throw std::invalid_argument("n 不能为负数。");
    }
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

// 生成斐波那契数列的函数（递归实现）
std::vector<unsigned long long> generateFibonacciRecursive(int n) {
    std::vector<unsigned long long> fib;

    for (int i = 0; i < n; ++i) {
        fib.push_back(fibonacciRecursive(i));
    }

    return fib;
}

// 动态规划实现斐波那契数列
std::vector<unsigned long long> fibonacci_dynamic(int n) {
    std::vector<unsigned long long> fib(n);
    fib[0] = 0;
    if (n > 1) {
        fib[1] = 1;
    }
    for (int i = 2; i < n; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    return fib;
}


// 打印斐波那契数列的函数
void printFibonacci(const std::vector<unsigned long long> &fib) {
    for (size_t i = 0; i < fib.size(); ++i) {
        std::cout << fib[i] << " ";
    }
    std::cout << std::endl;
}
