#include <iostream>
#include "InterView.h"

void thread_safe_print(){
    std::mutex mtx;
    MyLocker locker(mtx);
    std::cout << "hello world" << std::endl;
    throw std::runtime_error("打开文件失败");
}

int main() {
    //测试默认合成
//    JoiningThread jt;
//    std::cout << "member _i is " << jt.GetIndex() << std::endl;
//    JoiningThread jt(1);
//    JoiningThread jt2(jt);
//    std::cout << "member _i is " << jt.GetIndex() << std::endl;
//    WrapperC wc;
//    DerivedA a;
//
//    MyClass mc;
//    mc.setValue(10).setValue(200);

//    DefaultClass b;
//    std::cout << b << std::endl;

//    JoiningThread jt;
//    BaseA* ba = new DerivedA("zack","1001");
//    delete ba;
//
//    //FileHandler fh("test.txt");
//    try{
//        thread_safe_print();
//    }catch (std::exception& e){
//
//    }
//
//    std::cout <<"return 0 before join" << std::endl;
//    MyClass mc;
//    MyClass mc2 = mc;
//    std::cout << mc2.getValue() << std::endl;
    useVirtualTable();
    deriveTable();

    Convertible c("ximisu7");

    return 0;
}
