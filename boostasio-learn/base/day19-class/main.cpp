#include <iostream>
#include "student.h"
#include "JoiningThread.h"
#include "MyString.h"
#include "WrapperC.h"

int main() {
    system("chcp 65001");
    Student student1;
    student1.ChangeName("zack");
    student1.ChangeNum("10001");
    student1.ChangeAge(36);
    student1.ChangeMoney(5);
    std::cout << "Money: " << student1.GetMoney() << std::endl;

    std::cout << "Name: " << student1.GetName() << std::endl;
    std::cout << "Num: " << student1.GetNum() << std::endl;
    std::cout << "Age: " << student1.GetAge() << std::endl;

    std::cout << std::endl;
    Student student2;
    std::cout << "Name: " << student2.GetName() << std::endl;
    std::cout << "Num: " << student2.GetNum() << std::endl;
    std::cout << "Age: " << student2.GetAge() << std::endl;
    std::cout << "Money: " << student2.GetMoney() << std::endl;
    student2.ChangeMoney(10);

    Student student3("Alex", 33,"10002");
    std::cout << "Name: " << student3.GetName() << std::endl;
    std::cout << "Num: " << student3.GetNum() << std::endl;
    std::cout << "Age: " << student3.GetAge() << std::endl;
    std::cout << "Money: " << student3.GetMoney() << std::endl;

    Student student4(student1);
    std::cout << "Name: " << student4.GetName() << std::endl;
    std::cout << "Num: " << student4.GetNum() << std::endl;
    std::cout << "Age: " << student4.GetAge() << std::endl;
    std::cout << "Money: " << student4.GetMoney() << std::endl;

    Student student5(std::move(student1));
    std::cout << "Name: " << student5.GetName() << std::endl;
    std::cout << "Num: " << student5.GetNum() << std::endl;
    std::cout << "Age: " << student5.GetAge() << std::endl;
    std::cout << "Money: " << student5.GetMoney() << std::endl;


    std::cout << "Money: " << student1.GetMoney() << std::endl;

    std::cout << "Name: " << student1.GetName() << std::endl;
    std::cout << "Num: " << student1.GetNum() << std::endl;
    std::cout << "Age: " << student1.GetAge() << std::endl;

    //测试默认合成
    JoiningThread jt(1);
    JoiningThread jt2(jt);
    std::cout << "member _i is " << jt.GetIndex() << std::endl;

    Student student6;
    student6.GetMoney();
    std::cout << "student6 address is " << &student6 << std::endl;
    std::cout << "Name: " << student6.GetName() << std::endl;
    std::cout << "Num: " << student6.GetNum() << std::endl;
    std::cout << "Age: " << student6.GetAge() << std::endl;
    std::cout << "Money: " << student6.GetMoney() << std::endl;
    student6 = student5;
    std::cout << "Name: " << student6.GetName() << std::endl;
    std::cout << "Num: " << student6.GetNum() << std::endl;
    std::cout << "Age: " << student6.GetAge() << std::endl;
    std::cout << "Money: " << student6.GetMoney() << std::endl;

    Student student7 = std::move(student6);
    std::cout << "Name: " << student7.GetName() << std::endl;
    std::cout << "Num: " << student7.GetNum() << std::endl;
    std::cout << "Age: " << student7.GetAge() << std::endl;
    std::cout << "Money: " << student7.GetMoney() << std::endl;

    ChangeAge(student7, 20);
    std::cout << "Age: " << student7.GetAge() << std::endl;

    Student student8 = student7;
    student8 = student8+ student7;
    std::cout << "Age: " << student8.GetAge() << std::endl;
    std::cout << "......................" << std::endl;
    std::cout << "student8 operator <<  is " << student8;

    std::cout << "......................" << std::endl;

    MyString s1("hello");
    std::cout << "s1 is " << s1 << std::endl;

    MyString s2(s1);
    std::cout << "s2 is " << s2 << std::endl;

    auto s3 = s1;
    std::cout << "s3 is " << s3 << std::endl;

    auto s4 = std::move(s1);
    std::cout << "s4 is " << s4 << std::endl;

    auto s5 = s1 + s2;
    std::cout << "s5 is " << s5 << std::endl;

    WrapperC  rc;

    DerivedA a("zack","1001");
    DefaultClass b;
    std::cout << b << std::endl;

    BaseA* base = new DerivedA("zack","1002");
    delete base;

    return 0;
}
