#include <iostream>
#include "global.h"
int global_i = 0;
int main() {
    //const 关键字放在变量类型之前
    const int i = 5;
    //也可以放在类型之后
    int const j = 10;
    //可以用一个变量初始化常量
    int i1 = 10;
    const int i2 = i1;
    //也可以将一个常量赋值给一个变量
    int i3 = i2;
    //错误用法，const变量必须初始化
    //const int i4;
    PrintBufAddress();
    //输出bufSize地址
    std::cout << "main.cpp buf address is " << &bufSize << std::endl;
    //输出bufSize2地址
    std::cout << "main.cpp buf2 address is " << &bufSize2 << std::endl;
    //定义常量
    const int ci = 1024;
    //用常量引用绑定常量
    const int &r1 = ci;

    //不能修改常量引用的值
    //r1 = 2048;

    //也不能用非常量引用指向一个常量对象
    //int& r2 = ci;

    int i5 = 1024;
    //允许将const int& 绑定到一个普通的int对象上
    const int &r5 = i5;

    //常量引用绑定字面量
    const int &r6 = 1024;

    //常量引用绑定表达式计算的值
    const int &r7 = r6 * 2;
    const int &r8 = i5 * 2 + 10;

    //错误用法，类型不匹配
//    double dval = 3.14;
//    int & rd = dval;


    //编译通过
    double dval = 3.14;
    const int & ri = dval;

    //上面代码会做隐士转换,相当于下面代码
    const int temp  = dval;
    const int &rt = temp;

    int i9 = 1024;
    //非常量引用绑定i9
    int &r9 = i9;
    //常量引用绑定一个变量
    const int &r10 = i9;
    //可以同过非常量引用修改i9的值
    r9 = 2048;

    //PI 是一个常量,它的值不能改变
    const double PI = 3.14;
    //错误，ptr是一个普通指针
    //double * ptr = &PI;
    //正确,cptr可以指向一个双精度常量
    const double *cptr = &PI;
    //错误，不能给*ptr赋值
    //*cptr = 3.14;

    //可以用指向常量的指针指向一个非常量
    int i10 = 2048;
    //ptr指向i10
    int *cptr2 = &i10;

    int errNumb = 0;
    //curErr是一个常量指针，指向errNumb
    int * const curErr = &errNumb;
    const double pi2 = 3.14;
    //pip 是一个指向常量对象的常量指针
    const double *const pip = &pi2;

    //错误，pip是一个指向常量的指针
    //*pip = 2.72;
    //可以修改常量指针指向的内容
    *curErr = 1024;
    //可以修改常量指针指向的地址
    //curErr = &i10;

    {
        int i = 0;
        //不能改变p1的值，这是一个顶层const
        int * const pi = &i;
        //不能改变ci的值，这是一个顶层const
        const int ci  = 42;
        //允许改变p2的值，这是一个底层const
        const int * const p2 = &ci;
        //靠右边的const是顶层const，靠左边的const是底层const
        const int * const p3 = p2;
        //用于声明引用的const都是底层const
        const int &r = ci;

        //指针赋值要注意关注底层const
        //p2拥有底层const,p4无底层const，所以无法赋值
        //int * p4 = p2;

        //一个对象（或表达式）是不是常量表达式由它的数据类型和初始值共同决定
        {
            //max_files是一个常量表达式
            const int max_files = 20;
            //limit是一个常量表达式
            const int limit = max_files + 10;
            //staff_size不是常量表达式,无const声明
            int staff_size = 20;
            //sz不是常量表达式,运行时计算才得知
            const int sz = GetSize();
        }

        //c++ 11新特性 constexpr 关键字
        {
            //20是一个常量表达式
            constexpr int mf = 20;
            //mf+1是一个常量表达式
            constexpr int limit = mf + 10;
            //错误，GetSize()不是一个常量表达式，需要运行才能返回
            //constexpr int sz = GetSize();

            constexpr int sz = GetSizeConst();

            int mvalue = 100;

        }

        {
            //p是一个指向整形常量的指针
            const int * p = nullptr;
            //q是一个指向整数的常量指针
            constexpr int *q = nullptr;
        }

        {
            //constexpr指针只能绑定固定地址
            //constexpr int *p = &mvalue;
            constexpr int *p = nullptr;
            //可以绑定全局变量，全局变量地址固定
            constexpr  int *cp = &global_i;
        }

        {
            constexpr int *p = &global_i;
            //修改p指向的内容数据
            *p = 1024;
            //cp是一个常量指针，指向整数常量global_i
            constexpr const int * cp = &global_i;
        }
    }
    return 0;
}
