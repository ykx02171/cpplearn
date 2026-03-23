#include <iostream>
#include <cstdlib>
#include "Student.h"
#include "DynamicArray.h"
#include "MemoryPool.h"

int main() {
   //分配一个整数的内存
   int *p = (int *)malloc(sizeof(int));
   if(p == nullptr){
       std::cerr << "Memory allocation failed!" << std::endl;
       return -1;
   }

   *p = 42;
   std::cout << "Value: " << *p << std::endl;
   //释放内存
   free(p);

//   Student* st_p = (Student*)malloc(sizeof(Student));
//   if(st_p == nullptr){
//       std::cerr << "Memory allocation failed!" << std::endl;
//       return -1;
//   }
//   std::cout << "student age is " << st_p->age << " , name is " << st_p->name << std::endl;
//   free(st_p);

    int * array_p = (int*)(malloc(5* sizeof(int)));
    if(array_p == nullptr){
        std::cerr << "Memory allocation failed!" << std::endl;
        return -1;
    }

    for(int i = 0; i < 5; i++){
       // array_p[i] = i*2;
       *(array_p + i) = i*2;
    }


   for(int i = 0; i < 5; i++){
       std::cout << "array_p["<< i << "] = " << array_p[i] << std::endl;
    }

   free(array_p);

   Student* p_st = new Student("Tom", 20);
   std::cout << "student age is " << p_st->age << " , name is " << p_st->name << std::endl;
   delete p_st;

   auto pst_array = new Student[2]{
           {"Tom", 20},
           {"Jack", 19}
   };

   for(int i = 0; i < 2; i++){
       std::cout << "student age is " << pst_array[i].age << " , name is " << pst_array[i].name << std::endl;

   }

   delete[] pst_array;

   int * arr = (int*) malloc(3*sizeof(int));
   if(arr == nullptr){
       std::cerr << "Memory allocation failed!" << std::endl;
       return -1;
   }

   for(int i = 0; i < 3; i++){
       arr[i] = i*2;
   }

  for(int i = 0; i < 3; i++){
       std::cout << "arr["<< i << "] = " << arr[i] << std::endl;
   }

  int *temp = (int*)realloc(arr, 5*sizeof(int));
  if(temp == nullptr){
      std::cerr << "Memory reallocation failed!" << std::endl;
      free(arr);
      return -1;
  }

  arr = temp;
  for(int i = 3; i < 5; i++){
      arr[i] = (i+1)*10;
  }

  for(int i = 0; i < 5; i++){
      std::cout << "arr["<< i << "] = " << arr[i] << std::endl;
  }

  free(arr);

  try{
    DynamicArray arr;
    arr.add(10);
    arr.add(20);
    arr.add(30);
    std::cout << "DynamicArray: " << std::endl;
    for(size_t i = 0; i < arr.getSize(); ++i){
        std::cout << "["<< i << "] = " << arr.get(i) << std::endl;
    }
    std::cout << std::endl;
  }catch(const std::bad_alloc& e){
      std::cerr << "Memory allocation error: " << e.what() << std::endl;
      return 1;
  }catch(const std::out_of_range& e){
      std::cerr << "Array access error: " << e.what() << std::endl;
      return 1;
  }catch(const std::exception& e){
      std::cerr << "Error: " << e.what() << std::endl;
      return 1;
  }

  try{
      MemoryPool pool(sizeof(Student), 3);
      void * mem1 = pool.allocate();
      void * mem2 = pool.allocate();
      void * mem3 = pool.allocate();


      Student* obj1 = new(mem1) Student("Tom", 20);
      Student* obj2 = new(mem2) Student("Zack", 35);
      Student* obj3 = new(mem3) Student("Ray", 26);
      std::cout << "obj1 name: " << obj1->name << " obj1 age: " << obj1->age << std::endl;
      std::cout << "obj2 name: " << obj2->name << " obj2 age: " << obj2->age << std::endl;
      std::cout << "obj3 name: " << obj3->name << " obj3 age: " << obj3->age << std::endl;
      void * mem4 = pool.allocate();
      Student* obj4 = new(mem4) Student("Alan", 26);

      //显示调用析构
      obj1->~Student();
      obj2->~Student();
      obj3->~Student();
      pool.deallocate(mem1);
      pool.deallocate(mem2);
      pool.deallocate(mem3);
      obj4->~Student();
      pool.deallocate(mem4);
  }catch (const std::bad_alloc& e){
      std::cout << "Memory allocation error: " << e.what() << std::endl;
      return 1;
  }

  return 0;
}
