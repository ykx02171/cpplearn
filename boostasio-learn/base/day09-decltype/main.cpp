#include <iostream>

//wages 是double的同义词
typedef double wages;
//base是double的同义词,p是double*的同义词
typedef wages base, *p;
//64位整型
using int64_t = long long;
// pstring是char*的同义词
typedef char *pstring;
// cstr 是 const char* 类型的变量
const pstring cstr = 0;
const pstring *ps;


int main() {
    //定义变量a为64位整型
    int64_t a = 10;
    //计算求和
    int age1 = 20;
    int age2 = 35;
    auto age_add = age1 + age2;
    //正确, i是整数，p是整型指针
    auto i = 0, *p = &i;
    //错误, sz是整型，pi是double
    //auto sz = 0, pi = 3.14;
    {
        int i = 0, &r = i;
        // a是一个整数，类型是r所引用的类型
        auto a = r;
        // cr是一个常量引用，ci是int类型的常量
        const int ci = i, &cr = ci;
        // b是一个整数，ci顶层const被忽略了
        auto b = ci;
        // c是一个整数，cr是ci的别名，ci本身是一个顶层const
        auto c = cr;
        // d 是一个整型指针，i是整型
        auto d = &i;
        // e是一个指向整数常量的指针，对常量对象取地址是一种底层const
        auto e = &ci;
        //顶层const可显示指定,f是一个const int类型
        const auto f = ci;
        // g是一个整型常量引用，绑定到ci
        auto &g = ci;
        //错误，非常量引用不能绑定字面量
        //auto &h = 42;
        //正确,常量引用可以绑定字面量
        const auto &j = 42;

        //i为int类型， ci为const int类型， 但是k是int类型，l是int&类型
        auto k = ci, &l = i;
        //m是对常量的引用，p是指向整数常量的指针
        // p为const int*类型
        auto &m = ci, *p = &ci;
        //错误, i为int类型，&ci的类型为const int*
        //auto &n = i, *p2 = &ci;

    }

    {
        const int ci = 0, &cj = ci;
        //x是const int类型
        decltype(ci) x = 0;
        //y是一个const int&类型，y绑定到x
        decltype(cj) y = x;
        //错误，z是一个引用,引用必须初始化
        //decltype(cj) z;
    }

    {
        //decltype的结果可以是引用各类型
        int i = 42, *p = &i, &r = i;
        //正确，假发的结果是int，因此b是一个未初始化的int
        decltype(r + 0) b;
        //错误，c是int&，必须初始化
        //decltype(*p) c;

        //decltype的表达式如果加上了括号的变量，结果就是引用
        //错误，d是int&，必须初始化
        //decltype((i)) d;
        //正确,e是一个未被初始化的int类型值
        decltype(r) e = i;
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
