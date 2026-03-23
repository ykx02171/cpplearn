#include <iostream>

int main() {
    system("chcp 65001");
    //声明一个指向整数的指针，可以不赋初值
    int *ptr;
    //ip1和ip2都是指向int类型对象的指针
    int *ip1, *ip2;
    //dp2是指向double类型对象的指针,dp是double型对象
    double dp, *dp2;
    //定义ptr2并且赋值，指向var地址
    int var = 10;
    int *ptr2 = &var;
    //ptr_address 存储ptr2的地址
    int** ptr_address = &ptr2;
    std::cout << "var 的地址为: " << &var << std::endl;
    std::cout << "ptr2 存储的值为: " << ptr2 << std::endl;
    std::cout << "ptr2 地址为: " << &ptr2 << std::endl;
    std::cout << "ptr_address 的值为: " << ptr_address << std::endl;
    //因为在声明语句中指针的类型实际上被用于指定它所指向的对象的类型，所以二者必须匹配。
    //如果指针指向了一个其他类型的对象，那么会产生错误。
    double dval = 3.14;
    //正确，初始值是double类型的对象的地址
    double *pd = &dval;
    //正确，初始值是指向double对象的指针
    double *pd2 = pd;
    //错误,pi的类型和pd类型不匹配
    //int * pi = pd;
    //错误，视图把double型对象的地址赋值给int型指针
    //int * pi = &dval;

    //访问对象
    int ival = 42;
    //p_int存放着ival的地址，或者说p_int是指向变量ival的指针
    int * p_int = &ival;
    //由符号*得到指针p所指向的对象，输出42
    std::cout << *p_int << std::endl;
    //由符号*得到指针p所指向的对象，即可经由p_int为变量ival赋值
    *p_int = 0;
    std::cout << * p_int << std::endl;
    //打印ival的值
    std::cout << "ival 的值为" << ival << std::endl;
    //初始化一个空指针
    int* empty_pointer = nullptr;
    //打印空指针数据,非法
    //std::cout << "空指针指向数据是 " << *empty_pointer << std::endl;

    //符号的多重含义
    int ival2 = 42;
    //& 紧跟着类型名出现，因此是声明的一部分，r是一个引用
    int &r = ival2;
    //* 紧跟着类型名出现，因此是声明的一部分，p是一个指针
    int *p;
    // &出现在表达式中，是一个取地址符号
    p = &ival2;
    // * 出现在表达式中，是一个解引用符号
    *p = ival2;
    //& 是声明的一部分，*是一个解引用符号
    int &r2 = *p;

    //空指针定义方式
    //C++11 最推荐方式
    int *p1 = nullptr;
    //直接将p2初始化为字面量0
    int *p2 = 0;
    //需要使用#include<cstdlib>
    //等价于int * p3 = 0;
    int *p3 = NULL;
    std::cout << "p1: " << p1 << std::endl;
    std::cout << "p2: " << p2 << std::endl;
    std::cout << "p3: " << p3 << std::endl;

    //把int变量直接赋给指针是错误的操作，即使int变量的值恰好等于0也不行
    //int zero = 0;
    //int* pi2 = zero;

    int ival3 = 42;
    //pval3 被初始化，但没有指向任何对象
    int *pval3 = 0;
    //pval4被初始化，指向ival3的地址
    int* pval4 = &ival3;
    //将pval3的指向改为pval4的指向，二者同时指向ival3
    pval3 = pval4;
    std::cout <<"ival3 的地址为：" << &ival3 << std::endl;
    std::cout <<"pval3 指向的地址为 " << pval3 << std::endl;
    std::cout <<"pval4 指向的地址为 " << pval4 << std::endl;

    //空指针判断
    int * empty_pointer2 = nullptr;
    if(!empty_pointer){
        std::cout << "empty_pointer is empty" << std::endl;
    }

    int test = 100;
    int * normal_pointer2 = &test;
    if(normal_pointer2){
        std::cout << "normal pointer is not empty" << std::endl;
    }

    //判断指针是否相等
    if(normal_pointer2 != empty_pointer){
        std::cout << "normal_pointer 和 empty_pointer 不相等"<< std::endl;
    }

    //万能指针
    double obj = 3.14, *obj_pd = &obj;
    //void 可以存放任何类型的对象的地址
    void * pv = &obj;
    //pv 可以存储任意类型的地址
    pv = obj_pd;

    //以指针为例，指针是内存中的对象，像其他对象一样也有自己的地址，
    // 因此允许把指针的地址再存放到另一个指针当中。通过＊的个数可以区分指针的级别。
    // 也就是说，＊＊表示指向指针的指针，＊＊＊表示指向指针的指针的指针，以此类推：
    int ival4= 1024;
    // pival4指向了int型的数
    int *pival4 = &ival4;
    //ppi指向了一个int型的指针
    int ** ppi = &pival4;

    std::cout << "The value of ival\n"
        << "direct value: " << ival4 << "\n"
        << "indirect value: " << *pival4 << "\n"
        << "doubly indirect value : " << **ppi
        << std::endl;

    //引用本身不是一个对象，因此不能定义指向引用的指针。
    // 但指针是对象，所以存在对指针的引用
    int init = 42;
    // pinit是一个int型的指针
    int *pinit;
    // rpinit是一个对指针pinit的引用
    int *& rpinit = pinit;
    // rpinit引用了一个指针，因此给rpinit赋值&init就是令pinit指向init
    rpinit = &init;
    //解引用rpinit得到i,也就是p指向的对象，将init改为0
    *rpinit = 0;

    //指针可以进行算术运算，如递增（++）和递减（--），
    // 这些操作会改变指针所指向的内存地址。但是，这种操作仅限于指向数组元素的指针。
    int arr[5] = {1, 2, 3, 4, 5};
    int *ptr_arr = arr;
    std::cout << "ptr_arr is : " << ptr_arr << std::endl;
    int firstElement = *ptr_arr;
    std::cout << "firstElement is " << firstElement << std::endl;
    // 递增指针
    ++ptr_arr; // ptr 现在指向 arr[1]
    std::cout << "ptr_arr is : " << ptr_arr << std::endl;
    // 访问新位置的值
    int secondElement = *ptr_arr; // secondElement 等于 2
    std::cout << "secondElement is " << secondElement;
    return 0;

}
