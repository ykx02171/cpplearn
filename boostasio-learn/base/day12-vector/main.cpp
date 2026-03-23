#include <iostream>
#include <vector>
#include <algorithm>

struct Student{
    int id ;
    std::string name;
    float grade;
};

int main() {
    //默认初始化
    std::vector<int> vec1;
    //指定大小和默认值
    std::vector<int> vec2(5, 10);
    //C++11支持直接初始化，初始化列表
    std::vector<int> vec3 = {1, 2, 3};
    //拷贝构造
    std::vector<int> vec4(vec3);
    //移动构造
    std::vector<int> vec5(std::move(vec3));

    //输出vec2
    std::cout << "vec2: ";
    for (int temp: vec2) {
        std::cout << temp << " ";
    }
    std::cout << std::endl;

    std::cout << "size of vec2: " << vec2.size() << std::endl;
    std::cout << "capacity of vec2: " << vec2.capacity() << std::endl;
    vec2.push_back(100);
    std::cout << "size of vec2: " << vec2.size() << std::endl;
    std::cout << "capacity of vec2: " << vec2.capacity() << std::endl;

    std::cout << "size of vec4: " << vec4.size() << std::endl;
    std::cout << "capacity of vec4: " << vec4.capacity() << std::endl;

    std::vector<int> vec;
    //使用push_back添加元素
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    std::cout << "After push_back: " << std::endl;
    for (int temp: vec) {
        std::cout << temp << " ";
    }

    std::cout << std::endl;
    vec.pop_back();

    std::cout << "After pop_back: " << std::endl;
    for (int temp: vec) {
        std::cout << temp << " ";
    }

    std::cout << std::endl;

    //在第二个位置插入25
    vec.insert(vec.begin() + 1, 25);
    std::cout << "After insert: " << std::endl;
    for (int temp: vec) {
        std::cout << temp << " ";
    }

    std::cout << std::endl;

    //删除第二个位置的元素
    vec.erase(vec.begin() + 1);

    std::cout << "After erase: " << std::endl;
    for (int temp: vec) {
        std::cout << temp << " ";
    }

    std::cout << std::endl;

    vec.clear();
    std::cout << "After clear, size: " << vec.size() << std::endl; // 输出: 0
    std::cout << "After clear, capacity: " << vec.capacity() << std::endl; // 输出: 4

    //立即回收容量的机制
    {
        std::vector<int> empty_vec;
        empty_vec.swap(vec);

        std::cout << "After swap, vec capacity: " << vec.capacity() << std::endl;
        std::cout << "After swap, empty_vec capacity: " << empty_vec.capacity() << std::endl;
    }

    std::vector<std::string> fruits = {"apple", "banana", "orange"};
    std::cout << "first fruit : " << fruits[0] << std::endl;
    std::cout << "second fruit : " << fruits.at(1) << std::endl;

//    try {
//        std::cout << "invalid fruit : " << fruits.at(10086) << std::endl;
//    } catch (std::out_of_range &e) {
//        std::cerr << "Exception : " << e.what() << std::endl;
//    }

    std::cout << "++++++++++++++++++++++++++++++++++" << std::endl;
    //C++ 11
    for (auto temp: fruits) {
        std::cout << temp << " ";
    }

    std::cout << std::endl;
    std::cout << "++++++++++++++++++++++++++++++++++" << std::endl;

    std::cout << "???????????????????????????????????" << std::endl;
    //古老用法
    for (size_t i = 0; i < fruits.size(); ++i) {
        std::cout << "fruit: " << fruits[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "???????????????????????????????????" << std::endl;
    //迭代器
    for (auto it = fruits.begin(); it != fruits.end(); ++it) {
        std::cout << "fruit: " << *it << std::endl;
    }

    //通过索引(下标)访问元素
    fruits[0] = "pear";
    std::cout << "first fruit: " << fruits[0] << std::endl;

    //at()修改
    fruits.at(1) = "grape";
    std::cout << "second fruit: " << fruits.at(1) << std::endl;

    auto &temp = fruits[2];
    temp = "watermelon";
    std::cout << "third fruit: " << fruits[2] << std::endl;

    auto iter = fruits.end()-1;
    *iter = "lemon";
    std::cout << "third fruit: " << fruits[2] << std::endl;


    // 定义一个3x4的二维向量，初始化为0
    std::vector<std::vector<int>> matrix(3, std::vector<int>(4, 0));

    // 填充矩阵
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 4; ++j) {
            matrix[i][j] = i * 4 + j + 1;
        }
    }

    // 输出矩阵
    std::cout << "Matrix:" << std::endl;
    for(auto row : matrix) {
        for(auto elem : row) {
            std::cout << elem << "\t";
        }
        std::cout << std::endl;
    }

    std::vector<Student> students;
    students.push_back({1001,"Alice",89.5});
    students.push_back({1002,"Bob",95});
    students.push_back({1003,"Cindy",87});

    for(auto const  &student : students) {
        std::cout << "ID: " << student.id
                  << ", Name: " << student.name
                  << ", Score: " << student.grade << std::endl;
    }


    vec = {10, 20, 30, 40, 50};

    // 使用迭代器遍历并修改元素
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        *it += 5;
    }

    // 输出修改后的向量
    std::cout << "After modifying: ";
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl; // 输出: 15 25 35 45 55

    std::vector<int > numbers = {6,1,0,5,2,8};
    // 排序前
    std::cout << "Before sorting: ";
    for(auto num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::sort(numbers.begin(), numbers.end());

    // 排序后
    std::cout << "After sorting: ";
    for(auto num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::sort(numbers.begin(), numbers.end(),std::greater<int>());

    // 排序后
    std::cout << "After big sorting: ";
    for(auto num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    fruits = {"Apple", "Banana", "Cherry", "Lemon"};
    std::string target = "Watermelon";

    auto it = std::find(fruits.begin(), fruits.end(), target);
    if(it != fruits.end()) {
        std::cout << "Found: " << *it << std::endl;
    }else{
        std::cout << "Not found: " << target << std::endl;
    }

    {
        std::vector<int> vec;

        // 预留空间
        vec.reserve(1000);
        std::cout << "Capacity after reserve(1000): " << vec.capacity() << std::endl;

        // 添加元素
        for(int i = 0; i < 1000; ++i) {
            vec.push_back(i);
        }

        std::cout << "Size after adding elements: " << vec.size() << std::endl;
        std::cout << "Capacity after adding elements: " << vec.capacity() << std::endl;
    }

    {
        std::vector<int> vec;

        // 预留较大的空间
        vec.reserve(1000);
        std::cout << "Capacity before adding: " << vec.capacity() << std::endl;

        // 添加少量元素
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        std::cout << "Size after adding: " << vec.size() << std::endl;
        std::cout << "Capacity after adding: " << vec.capacity() << std::endl;

        // 收缩容量
        vec.shrink_to_fit();
        std::cout << "Capacity after shrink_to_fit: " << vec.capacity() << std::endl;
    }

    return 0;
}
