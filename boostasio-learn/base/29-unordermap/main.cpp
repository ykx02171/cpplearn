#include <iostream>
#include <unordered_map>
#include "MyHashMap.h"
struct Point{
    int x;
    int y;
    bool operator==(const Point& other) const{
        return x == other.x && y == other.y;
    }

};

struct PointHash{
    std::size_t operator()(const Point& p) const{
        std::size_t h1 = std::hash<int>()(p.x);
        std::size_t h2 = std::hash<int>()(p.y);
        return h1 ^ (h2 << 1);
    }
};

struct PointEqual{
    bool operator()(const Point& p1, const Point& p2) const{
        return p1.x == p2.y && p1.y == p2.x;
    }
};


int main() {
//    std::unordered_map<std::string, int> umap;
//    std::unordered_map<std::string, int> umap_init = {
//            {"apple",3},
//            {"banana",2},
//            {"cherry",5}
//    };
//
//    std::unordered_map<std::string,int> umpa_from_map(umap_init.begin(), umap_init.end());
//    auto apple_count = umap["apple"];
//    std::cout << "apple count: " << apple_count << std::endl;
//    std::cout << umap.count("apple") << std::endl;
//    umap.insert({"melon",100});
//    umap.emplace("kiwi",20);
//    try{
//       int bana_count =  umap.at("banana");
//    }catch(const std::exception& e){
//        std::cout << e.what() << std::endl;
//    }
//
//    auto it = umap.find("orange");
//    if(it == umap.end()){
//        std::cout << "orange not found" << std::endl;
//    }else{
//        std::cout << "orange found" << std::endl;
//    }
//
//    umap.erase("banana");
//    auto it2 = umap.find("banana");
//    if(it2 != umap.end()){
//        auto it3 = umap.erase(it2);
//    }
//
//    umap.clear();
//
//    for(auto it = umap.begin(); it != umap.end(); it++){
//        std::cout << it->first << " " << it->second << std::endl;
//    }
//
//    for(const auto & pair : umap_init){
//        std::cout << pair.first << " " << pair.second << std::endl;
//    }
//
//    std::cout << "size: " << umap.size() << std::endl;
//    std::cout << "empty: " << umap.empty() << std::endl;
//    auto bk_count = umap.bucket_count();
//    umap.rehash(bk_count*2);
//    std::cout << "bucket count: " << bk_count << std::endl;
//    std::cout << "Hello, World!" << std::endl;
//    auto umap2 = std::move(umap);
//
//    std::unordered_map<Point, std::string, PointHash> point_map;
//    point_map[{1,2}] = "A";
//    point_map[{3,4}] = "B";
//
//    std::unordered_map<Point, std::string, PointHash, PointEqual> point_map3;
    MyHashMap<std::string, int> my_hashmap;
    my_hashmap.insert("apple", 3);
    my_hashmap.insert("banana", 2);
    for(auto it = my_hashmap.begin(); it != my_hashmap.end(); ++it){
        std::cout << it->first << " " << it->second << std::endl;
    }
    my_hashmap.erase("banana");
    for(auto it = my_hashmap.begin(); it != my_hashmap.end(); ++it){
        std::cout << it->first << " " << it->second << std::endl;
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
