#include <iostream>
#include <iostream>
#include <cstring>

void calculate(){
    //整形变量支持计算，所谓计算就是我们熟悉的  `+` ,`-`,`*`,`/`,`%`等
    int a = 10;
    int b = 20;
    std::cout << "a + b = " << a+b << std::endl;
    std::cout << "a - b = " << a-b << std::endl;
    std::cout << "a * b = " << a*b << std::endl;
    std::cout << "a / b = " << a/b << std::endl;
    std::cout << "a % b = " << a%b << std::endl;
    //浮点型变量支持计算，所谓计算就是我们熟悉的  `+` ,`-`,`*`,`/`等
    float c = 10.5;
    float d = 20.3;
    std::cout << "c + d = " << c+d << std::endl;
    std::cout << "c - d = " << c-d << std::endl;
    std::cout << "c * d = " << c*d << std::endl;
    std::cout << "c / d = " << c/d << std::endl;
    //浮点型变量支持计算，所谓计算就是我们熟悉的  `+` ,`-`,`*`,`/`等
    double e = 10.5;
    double f = 20.3;
    std::cout << "e + f = " << e+f << std::endl;
    std::cout << "e - f = " << e-f << std::endl;
    std::cout << "e * f = " << e*f << std::endl;
    std::cout << "e / f = " << e/f << std::endl;
    //字符变量支持计算，所谓计算就是我们熟悉的  `+` ,`-`,`*`,`/`等
    char g = 'a';
    char h = 'b';
    std::cout << "g + h = " << (int)(g+h) << std::endl;
    std::cout << "g - h = " << (int)(g-h) << std::endl;
    std::cout << "g * h = " << (int)(g*h) << std::endl;
    std::cout << "g / h = " << (int)(g/h) << std::endl;

}

void sizeofnum(){
    std::cout << "Size of char: " << sizeof(char) << " bytes\n";
    std::cout << "Size of int: " << sizeof(int) << " bytes\n";
    std::cout << "Size of float: " << sizeof(float) << " bytes\n";
    std::cout << "Size of double: " << sizeof(double) << " bytes\n";
    std::cout << "Size of long long: " << sizeof(long long) << " bytes\n";
}

// 全局变量，具有全局作用域
int globalVar = 42;

void func1() {
    std::cout << "Inside func: globalVar = " << globalVar << std::endl;
}

void func2() {
    // 局部变量，具有局部作用域
    int localVar = 10;
    std::cout << "Inside func: localVar = " << localVar << std::endl;
    // localVar 在这里之后就不再可见
}

// 定义一个命名空间
namespace MyNamespace {
    // 命名空间内的变量，具有命名空间作用域
    int namespaceVar = 20;

    void printVar() {
        std::cout << "Inside MyNamespace: namespaceVar = " << namespaceVar << std::endl;
    }
}

class MyClass {
public:
    // 成员变量，具有类作用域
    int classVar;

    // 成员函数，也可以访问类作用域内的成员变量
    void printVar() {
        std::cout << "Inside MyClass: classVar = " << classVar << std::endl;
    }
};

void func3() {
    {
        // 块内局部变量，具有块作用域
        int blockVar = 5;
        std::cout << "Inside block: blockVar = " << blockVar << std::endl;
        // blockVar 在这个代码块之后就不再可见
    }
    // 尝试访问 blockVar 会导致编译错误
    // std::cout << "blockVar = " << blockVar << std::endl; // 错误
}

// 全局变量，存储在全局/静态存储区
int globalVar2 = 10;

// 静态变量，也存储在全局/静态存储区，但仅在其声明的文件或函数内部可见
static int staticVar = 20;

void func4() {
    // 局部变量，存储在栈区
    int localVar = 30;

    // 静态局部变量，虽然声明在函数内部，但存储在全局/静态存储区，且只在第一次调用时初始化
    static int staticLocalVar = 40;

    std::cout << "Inside func:" << std::endl;
    std::cout << "localVar = " << localVar << std::endl;
    std::cout << "staticLocalVar = " << staticLocalVar << std::endl;

    // 尝试通过动态内存分配在堆区分配内存
    int* heapVar = new int(50);

    std::cout << "heapVar = " << *heapVar << std::endl;

    // 释放堆区内存（重要：实际使用中不要忘记释放不再使用的堆内存）
    delete heapVar;
}

int main() {
    calculate();
    sizeofnum();
    std::cout << "Inside main: globalVar = " << globalVar << std::endl;
    func1(); // 访问全局变量
    // 尝试访问 localVar 会导致编译错误
    // std::cout << "localVar = " << localVar << std::endl; // 错误
    func2(); // 局部变量仅在func函数内部可见
    // 使用命名空间前缀访问变量
    std::cout << "Outside MyNamespace: namespaceVar = " << MyNamespace::namespaceVar << std::endl;
    MyNamespace::printVar(); // 访问命名空间内的函数

    MyClass obj;
    obj.classVar = 30; // 通过对象访问成员变量
    obj.printVar(); // 访问成员函数
    // 尝试直接访问 classVar 会导致编译错误
    // std::cout << "classVar = " << classVar << std::endl; // 错误
    func3();


    // 访问全局变量
    std::cout << "Inside main:" << std::endl;
    std::cout << "globalVar = " << globalVar << std::endl;
    std::cout << "staticVar = " << staticVar << std::endl; // 注意：staticVar在外部不可见（除非在同一个文件中或通过特殊方式）

    // 调用函数，展示栈区和堆区的使用
    func4();

    // 字符串常量通常存储在常量区，但直接访问其内存地址并不是标准C++的做法
    // 这里我们仅通过指针来展示其存在
    const char* strConst = "Hello, World!";
    // 注意：不要尝试修改strConst指向的内容，因为它是只读的
    std::cout << "strConst = " << strConst << std::endl;
    // 尝试获取字符串常量的长度（这不会修改常量区的内容）
    std::cout << "Length of strConst = " << strlen(strConst) << std::endl;

    return 0;
}
