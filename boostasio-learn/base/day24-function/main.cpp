#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <thread>
#include <functional>

//定义函数指针类型的变量
int (*funcPtr)(int , int);

//定义一个普通函数
int add(int a, int b){
    return a + b;
}

struct Multiply{
    int operator()(int a, int b){
        return a * b;
    }
};

struct Adder{
    int to_add;
    Adder(int value): to_add(value){}
    int operator()(int x){
        return x + to_add;
    }

    void add(int x){
        to_add += x;
    }

    ~Adder(){
        std::cout << "Adder destructed" << std::endl;
    }
};

struct IsGreaterThan{
    int threshold;
    IsGreaterThan(int value): threshold(value){}
    bool operator()(int x){
        return x > threshold;
    }

};

template<typename T>
struct Compare{
    bool operator()(const T& a, const T& b){
        return a  < b;
    }
};

class Processor{
public:
    Processor(int threshold): _threshold(threshold){}

    void process(std::vector<int> & data){
        std::cout << "before process data :" << std::endl;
        for(auto num :data) std::cout << num << " ";
        std::cout << std::endl;
        auto new_end = std::remove_if(data.begin(), data.end(),
                                      [this](int n) -> bool{
            return n < _threshold;
           });
        data.erase(new_end, data.end());
        std::cout << "after process data :" << std::endl;
        for(auto num :data) std::cout << num << " ";
        std::cout << std::endl;
    }
private:
    int _threshold;
};

//定义回调类型
using Callback = std::function<void(int)>;

//触发事件的函数
void triggerEvent(Callback cb, int value){
    //事件发生，调用回调
    cb(value);
}

void print(int a, int b, int c){
    std::cout << "print: " << a << ", " << b << ", " << c << std::endl;
}

class Calculator{
public:
    Calculator(): result(0){}
    int result;
    int multiply(int a, int b){
        result = a * b;
        return result;
    }
};

int main() {
    system("chcp 65001");
    //函数指针指向函数
    //funcPtr = &add;
    funcPtr = add;
    int result = funcPtr(1,2);
   // int result = (*funcPtr)(1,2);
    std::cout << "result: " << result << std::endl;

//    Adder adder(5);
//    std::cout << "5+10 : " << adder(10) << std::endl;

    std::vector<int> numbers = {1,2,15,4,5};
    IsGreaterThan greaterThan(10);
    auto it = std::find_if(numbers.begin(), numbers.end(), greaterThan);
    if(it != numbers.end()){
        std::cout << "found: " << *it << std::endl;
    }else{
        std::cout << "not found" << std::endl;
    }

    std::vector<double> numbers2 = {9.2,0,7, 3.4,1.5, 3.4, 6.7};
    std::sort(numbers2.begin(), numbers2.end(), Compare<double>());
    for(auto& n : numbers2){
        std::cout << n << " ";
    }
    std::cout << std::endl;

    int threshold = 5;
    std::vector<int> numbers3 = {1, 6, 3, 8, 2, 7};
    auto new_end = std::remove_if(numbers3.begin(), numbers3.end(), [threshold](int x){
        return x < threshold;
    });

    for(int n : numbers3) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    numbers3.erase(new_end, numbers3.end());
    // 打印结果
    for (int n : numbers3) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    int temp = 2;
    int * ptemp = &temp;
    auto lambda1 = [ptemp](int x){
        *ptemp *= x;

    };

    lambda1(3);
    std::cout << "temp: " << temp << std::endl;
//    std::thread t1;
//    {
//        auto add_ptr = std::make_shared<Adder>(10);
//        auto lambda2 = [add_ptr](int x){
//            std::cout << "begin lambda2 use count : " << add_ptr.use_count() << std::endl;
//            std::this_thread::sleep_for(std::chrono::seconds(10));
//            add_ptr->add(x);
//            std::cout << add_ptr.use_count() << std::endl;
//        };
//
//        t1 = std::thread(lambda2, 5);
//
//        std::cout << "before }   use count : " << add_ptr.use_count() << std::endl;
//    }
//
//    t1.join();

//    Processor processor(5);
//    std::vector<int> data = {1,3,6,8,2,7};
//    processor.process(data);

    {
       //封装普通函数
       std::function<int(int, int)> func1 = add;
       std::cout << "Add : " << func1(3,4)  << std::endl;

       Multiply multiply;
       std::function<int(int, int)> func2 = multiply;
       std::cout << "Multiply : " << func2(3,4)  << std::endl;

       std::function<int(int, int )> func3 = [](int a, int b) -> int{
           return a - b;
       };

       std::cout << "Subtract : " << func3(10, 5)  << std::endl;
    }

    triggerEvent([](int x){
        std::cout << "事件触发， 值为: " << x << std::endl;
    }, 42);

    struct Printer{
        void operator()(int x) const{
            std::cout << "Printer 调用，值为: " << x << std::endl;
        }
    } printer;
    triggerEvent(printer, 42);

    std::vector<std::function<int(int, int)>> operations;
    operations.emplace_back(add);
    operations.emplace_back(Multiply());
    operations.emplace_back([](int a, int b) ->int{
        return a - b ;});


    for(auto & op : operations){
        std::cout << op(10,5) << std::endl;
    }

    auto new_add = std::bind(add, 10, std::placeholders::_1);
    //add(10,5)
    std::cout << new_add(5) << std::endl;

    std::function<void(int, int , int)> new_func = std::bind(print, std::placeholders::_3, std::placeholders::_2, std::placeholders::_1);
    new_func(1,2,3);

    auto new_f3 = [](int b) -> int {
        return add(10, b);
    };

    std::cout << " 10+ 5 = " << new_f3(5) << std::endl;

    Calculator calc;
    auto multiply_new = std::bind(&Calculator::multiply, &calc, 5,std::placeholders::_1);
    std::cout << "5 * 3 = " << multiply_new(3) << std::endl;

    auto new_multipy_lambda = [&calc](int a){
        return calc.multiply(5,a);
    };

    std::cout << "5*3 = " << new_multipy_lambda(3) << std::endl;
    return 0;
}
