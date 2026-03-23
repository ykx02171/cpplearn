#include <iostream>
#include <thread>
#include "Student.h"
#include "SimpleSharedPtr.h"
#include <memory>
#include <cstdio>
void test_p_int(Student *p_student){

    p_student->name = "Ray";
}

struct FileDeleter{
    void  operator()(FILE * fp){
        if(fp){
            std::cout  << "Close file success!" << std::endl;
            fclose(fp);
        }
    }
};

int main() {
    //std::cout << "Hello, World!" << std::endl;
//    Student* p_student = new Student("zack",36);
//    std::cout << p_student->name << std::endl;
//
//    std::thread t1([p_student](){
//        std::this_thread::sleep_for(std::chrono::seconds(1));
//        p_student->name = "Ray";
//    });
//    t1.join();
//    std::cout << "Creating default constructed shared_ptr..." << std::endl;
//    SimpleSharedPtr<Student> ptr1;
//    std::cout << "ptr1 use_count: " << ptr1.use_count() << std::endl;
//
//    std::cout << "Creating shared_ptr from raw pointer..." << std::endl;
//    SimpleSharedPtr<Student> ptr2(new Student("zack", 36));
//    std::cout << "ptr2 use_count: " << ptr2.use_count() << std::endl;
//
//    std::cout << "Creating shared_ptr from another shared_ptr..." << std::endl;
//    SimpleSharedPtr<Student> ptr3 = ptr2;
//    std::cout << "ptr3 use_count: " << ptr3.use_count() << std::endl;
//    std::cout << "ptr2 use_count: " << ptr2.use_count() << std::endl;
//
//    ptr1 = ptr3;
//    std::cout << "ptr1 use_count: " << ptr1.use_count() << std::endl;
//    std::cout << "ptr3 use_count: " << ptr3.use_count() << std::endl;
//
//    ptr2.reset(new Student("Ray", 23));
//    std::cout << "ptr2 use_count: " << ptr2.use_count() << std::endl;
//    std::cout << "ptr3 use_count: " << ptr3.use_count() << std::endl;
//    std::cout << "ptr1 use_count: " << ptr1.use_count() << std::endl;
//
//    std::thread t1([ptr2](){
//        ptr2->name = "Ray in thread";
//    });
//
//    t1.join();

    //auto * student = new Student();
    //std::shared_ptr<Student> shared_student (student);
    //std::shared_ptr<Student> shared_student = std::shared_ptr<Student>(student);
   // std::shared_ptr<Student> shared_student(new Student());
//    auto shared_student = std::make_shared<Student>("zack",25);
//    std::shared_ptr<Student> shared_student2 = shared_student;
//    std::cout <<"After shared_student2 = shared_student, the use count is " << std::endl;
//    std::cout << shared_student2.use_count()<< std::endl;
//    std::cout << shared_student.use_count()<< std::endl;
//
//    std::shared_ptr<Student> sp3;
//    sp3 = shared_student;
//    std::cout <<"After sp3 = shared_student, the use count is "<< std::endl;
//    std::cout << sp3.use_count()<< std::endl;
//    std::cout << shared_student.use_count()<< std::endl;
//
//    shared_student2.reset(new Student("Ray",23));
//    std::cout << "After shared_student2.reset(new Student), the use count is "<< std::endl;
//    std::cout << shared_student.use_count()<< std::endl;
//    std::cout << shared_student2.use_count()<< std::endl;
//    std::cout << sp3.use_count()<< std::endl;

     std::unique_ptr<Student> ptr1(new Student("zack",25));
     ptr1->print();

     std::unique_ptr<Student> ptr2 = std::move(ptr1);
     ptr1 = std::unique_ptr<Student>(new Student("Ray",23));
     ptr1->print();

     "hello world";
     std::unique_ptr<Student> ptr3 = std::make_unique<Student>("Vivo", 25);
     std::unique_ptr<Student> ptr4 = std::move(ptr3);

    {
        std::shared_ptr<A> a = std::make_shared<A>();
        std::shared_ptr<B> b = std::make_shared<B>();
        a->ptrB = b;
        b->ptrA = a;
        std::cout << "a use count: "<< a.use_count() << std::endl;
        std::cout <<"b->ptrA use count: "<< b->ptrA.use_count() << std::endl;
        bool b_expired = b->ptrA.expired();
    }

    {
//       std::shared_ptr<FILE> filePtr(fopen("test.txt","w"), FileDeleter());
//       if(filePtr){
//           std::cout << "File opened successfully." << std::endl;
//           // 使用 filePtr 进行文件操作
//           fprintf(filePtr.get(), "Hello, World!\n");
//       }
        {
           auto fileDeletor = [](FILE* fp){
               if(fp){
                   std::cout << "Close file success!" << std::endl;
                   fclose(fp);
               }
           };

           std::unique_ptr<FILE,decltype(fileDeletor)> filePtr(fopen("test.txt","w"),
                                                               fileDeletor);
           if(filePtr){
               std::cout << "File opened successfully." << std::endl;
               fprintf(filePtr.get(), "Hello, Lambda!\n");
           }
        }
    }

    return 0;
}
