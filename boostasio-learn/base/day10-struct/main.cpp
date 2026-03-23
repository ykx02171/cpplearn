#include <iostream>
#include <string>
//学生结构体
struct Student{
    //学号
    int id;
    //姓名
    std::string name;
    //学分权重
    float grade;
    //构造函数,构造函数就是用来创建对象时调用的，并且传入参数赋值给各个成员变量
    Student(int studentId, std::string studentName, float studentGrade)
    :id(studentId),name(studentName){
        grade = studentGrade;
    }

    Student():id(0),name(""),grade(0.0f){

    }
};

struct Point {
    int x;
    int y;
};

//通过值传递
void printPoint(Point p){
    std::cout << "Point(" << p.x << ", " << p.y << ")" << std::endl;
}

//通过引用方式传递
void movePoint(Point &p, int dx, int dy){
    p.x += dx;
    p.y += dy;
}

//通过指针传递
// movePoint2(&p1,5,-5)
void movePoint2(Point *p, int dx, int dy){
    p->x += dx;
    p->y += dy;
}

//返回结构体数据
Point movePoint3(Point *p, int dx, int dy){
    Point p2 = *p;
    p2.x += dx;
    p2.y += dy;
    return p2;
}

Point movePoint4(Point *p, int dx, int dy){
    (*p).x += dx;
    (*p).y += dy;

    return *p;
}

class Rectangle {
private:
    int width;
    int height;

public:
    void setDimensions(int w, int h) {
        width = w;
        height = h;
    }

    int area() const {
        return width * height;
    }

    int get_width(){
        return width;
    }
};


struct Car{
    std::string brand;
    std::string model;
    int year;
};

typedef Car Car2;

typedef struct {
    int id;
    std::string name;
    float grade;
} StudentType;

using StudentType2 = struct {
    int id;
    std::string name;
    float grade;
};

struct Book {
    std::string title;
    std::string author;
    int pages;

    //成员函数
    void printInfo() const {
        std::cout << "书名：" << title
        << " 作者：" << author
        << " 页数：" << pages << std::endl;
    }
};

int main() {
    system("chcp 65001");
    //定义结构体变量
    Student student1;
    Student student2;

    //修改结构体内成员变量
    //修改学号
    student1.id = 95200;
    //修改名字
    student1.name = "zack";
    //评分权重
    student1.grade = 100.0f;

    //结构体成员的访问
    std::cout << "学生ID: " << student1.id << std::endl;
    std::cout << "学生姓名: " << student1.name << std::endl;
    std::cout << "学生成绩: " << student1.grade << std::endl;

    //快速初始化结构体变量
    Student student3 = {95201,"Bob",70.5f};

    std::cout << "学生ID: " << student3.id << std::endl;
    std::cout << "学生姓名: " << student3.name << std::endl;
    std::cout << "学生成绩: " << student3.grade << std::endl;
    //运算符重载后才能输出，需要重载<<运算符
    //std::cout << student3 << std::endl;

    Student student5(1004,"Daisy",98.5);
    std::cout << "学生ID: " << student5.id << std::endl;
    std::cout << "学生姓名: " << student5.name << std::endl;
    std::cout << "学生成绩: " << student5.grade << std::endl;

    Rectangle rt;
    //错误，不能直接访问私有成员
    //rt.width;
    //正确，可以通过公有成员函数访问
    rt.get_width();

    Point pt;
    pt.x = 100;

    struct Address {
        std::string city;
        std::string street;
        int houseNumber;
    };

    struct Person {
        std::string name;
        int age;
        Address address; // 嵌套结构体
    };

    Person person1;
    person1.name = "zack";
    person1.age = 35;
    person1.address.city = "Beijing";
    person1.address.street = "Chaoyang Road";
    person1.address.houseNumber = 10025;

    std::cout << person1.name << " lives at "
              << person1.address.houseNumber << " "
              << person1.address.street << ", "
              << person1.address.city << std::endl;

    int array[3] = {1,2,3};
    float array2[] = {1.0f,2.0f,3.0f};
    Student array3[2] = {
            {95201,"Bob",70.5f},
            {95200,"zack",100.0f}
    };

    for(int i = 0; i < 2; ++i){
        std::cout << "学生ID: " << array3[i].id
        << " 姓名: " << array3[i].name
        << " 成绩: " << array3[i].grade << std::endl;
    }



    Car car1 = {"BMW","M5",2019};
    int a = 100;
    int * p = &a;
    Car* pcar = &car1;
    std::cout << "品牌: "<< pcar->brand << std::endl;
    std::cout << "型号: "<< pcar->model << std::endl;
    std::cout << "年份: "<< pcar->year << std::endl;


    Car2 car2 = {"Tesla","Model 3",2019};

    std::cout << "品牌: "<< car2.brand << std::endl;
    std::cout << "型号: "<< car2.model << std::endl;
    std::cout << "年份: "<< car2.year << std::endl;

    Book myBook = {"C++ Primer Plus","StanleyB.Lippman",976};
    myBook.printInfo();

    Point p1 = {10,20};
    printPoint(p1);
    movePoint(p1,5,-5);
    printPoint(p1);
    movePoint2(&p1,5,-5);
    printPoint(p1);
    auto p2 = movePoint3(&p1,5,-5);
    printPoint(p1);
    printPoint(p2);
    auto p3 = movePoint4(&p1,5,-5);
    printPoint(p1);
    printPoint(p3);
    return 0;
}
