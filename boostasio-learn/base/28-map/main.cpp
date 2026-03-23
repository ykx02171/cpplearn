#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <functional>
#include "MyMap.h"
#include "AVLMap.h"
class Person{
public:
    int age;
    std::string name;
    Person(int age, std::string name) : age(age), name(name){}
//    bool operator < (const Person & other) const {
//        return age < other.age ;
//    }
};

struct ComparePerson{
    bool operator()(const Person & a, const Person & b) const {
        return a.age < b.age;
    }
};


int main() {
    system("chcp 65001");
//    //std::cout << "Hello, World!" << std::endl;
//    std::map<int, std::string> mymap = {
//            {1, "apple"},
//            {100, "banana"},
//            {25, "orange"},
//    };
//
//    for (auto & x : mymap) {
//        std::cout << x.first << " => " << x.second << '\n';
//    }
//
//    mymap.insert(std::pair<int, std::string>(56,"peach"));
//    mymap.insert(std::make_pair(5,"pear"));
//    mymap.insert({104,"grape"});
//    mymap.insert({104,"watermelon"});
//    mymap[104] = "blackberry";
//    auto fruit = mymap[104];
//    std::cout << fruit << std::endl;
//    std::cout << "==============" << std::endl;
//
//    std::cout << "==================\n";
////    fruit = mymap[111];
////    std::cout << fruit << std::endl;
//
//    auto it = mymap.find(111);
//    if (it != mymap.end()) {
//        std::cout << "Found: " << it->second;
//    }else{
//        std::cout << "Not Found";
//    }
//
//    std::cout << std::endl;
//    std::cout << "==================" << std::endl;
//
//    //std::out_of_range
//    try{
//        fruit = mymap.at(111);
//    }catch (const std::out_of_range & e){
//        std::cout << "Key not found: " << e.what() << std::endl;
//    }
//
//    mymap.erase(104);
//    std::cout << "***********" << std::endl;
//
//    it = mymap.find(100);
//    if( it != mymap.end()){
//        mymap.erase(it);
//    }else{
//        std::cout << "Not Found" << std::endl;
//    }
//
//    auto endit = mymap.find(56);
//    mymap.erase(mymap.begin(), endit);
//
//    for (auto it = mymap.begin(); it != mymap.end(); ++it){
//        std::cout << it->first << " => " << it->second << '\n';
//    }
//
//    mymap.clear();
//    std::cout << "????????????????" << std::endl;
//    for (auto it = mymap.begin(); it != mymap.end(); ++it){
//        std::cout << it->first << " => " << it->second << '\n';
//    }
//
//    std::cout << "size: " << mymap.size() << std::endl;
//    if(mymap.empty()){
//        std::cout << "empty" << std::endl;
//    }
//
//    mymap.insert(std::make_pair(1,"grape"));
//    mymap.insert(std::pair(25,"orange"));
//    mymap.insert(std::pair(13,"blackberry"));
//    mymap.insert(std::make_pair(1024,"watermelon"));
//    mymap.insert({222,"apple"});
////    std::cout << mymap.count(1) << std::endl;
////    std::cout << mymap.count(1024) << std::endl;
//
//    auto itbegin = mymap.lower_bound(13);
//    auto itend = mymap.upper_bound(222);
//    //我想使用foreach 泛型算法
//    std::for_each(itbegin, itend, [](auto pair){
//       std::cout << pair.first << " => " << pair.second << '\n';
//    });
//
//    std::map<int, std::string> mymap2;
//    std::transform(itbegin, itend, std::inserter(mymap2, mymap2.end()),
//                   []( auto &pair){
//            auto new_str = pair.second;
//            std::transform(new_str.begin(),new_str.end(),new_str.begin(),::toupper);
//            return std::make_pair(pair.first, new_str);
//    });
//
//    std::for_each(mymap2.begin(), mymap2.end(), [](auto & pair){
//        std::cout << pair.first << " => " << pair.second << '\n';
//    });
//
//    std::function<bool(const Person&, const Person&)> comp = [](const Person& p1, const Person& p2) {
//        return p1.age > p2.age;
//    };
//
//    std::map<Person, int, std::function<bool(const Person&, const Person&)>> person_map(comp);
//    Person p1(25,"John");
//    Person p2(10,"Mike");
//    Person p3(100,"Tom");
//
//    person_map.insert(std::make_pair(p1, 100));
//    person_map.insert(std::make_pair(p2, 30));
//    person_map.insert(std::make_pair(p3, 10));
//
//    for (auto & x : person_map) {
//        std::cout << x.first.age << " => " << x.second << '\n';
//    }

//    MyMap<int,std::string> mymap;
//
//    mymap.insert(150,"apple");
//    mymap.insert(130,"banana");
//    mymap.insert(170,"orange");
//    mymap.insert(165,"peach");
//    for(auto it = mymap.begin(); it != mymap.end(); ++it){
//        std::cout << it->first << " => " << it->second << '\n';
//    }
//
//    mymap.erase(150);
//    std::cout << "**********" << std::endl;
//    for(auto it = mymap.begin(); it != mymap.end(); ++it){
//        std::cout << it->first << " => " << it->second << '\n';
//    }
//
//    mymap.insert(170,"apple");
//    std::cout << "?????" << std::endl;
//    for(auto it = mymap.begin(); it != mymap.end(); ++it){
//        std::cout << it->first << " => " << it->second << '\n';
//    }


   AVLMap<int, std::string> avlMap;
    avlMap.put(150,"apple");
    avlMap.put(200,"peach");
    avlMap.put(160,"grape");
    avlMap.put(180,"watermelon");
    avlMap.put(75,"pear");

    auto traversal = avlMap.inorderTraversal();
    for(auto & pair : traversal){
        std::cout << pair.first << " => " << pair.second << '\n';
    }

    auto * root = avlMap.GetRoot();
    std::cout << "root: " << root->key << std::endl;

    auto find_res = avlMap.get(20);
    if(find_res){
        std::cout << *find_res << '\n';
    }else{
        std::cout << "Not Found" << std::endl;
    }

    avlMap.remove(160);
    root = avlMap.GetRoot();
    std::cout << "root: " << root->key << std::endl;
    return 0;
}
