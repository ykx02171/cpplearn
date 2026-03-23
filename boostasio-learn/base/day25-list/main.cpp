#include <iostream>
#include <list>
#include "List.h"
int main() {
    std::list<int> numbers;
    numbers.push_back(100);
    numbers.push_back(200);
    numbers.push_back(300);
    numbers.push_front(50);

    for(auto it = numbers.begin(); it != numbers.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    auto it = numbers.begin();
    ++it ;
    numbers.insert(it, 150);
    numbers.insert(it, 200);
    for(auto it = numbers.begin(); it != numbers.end(); ++it){
        std::cout << *it << " ";
    }

    std::cout << std::endl;

    numbers.remove(200);
    for(auto it = numbers.begin(); it != numbers.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    auto end_it = numbers.end();
    --end_it;
    --end_it;
    numbers.erase(end_it);

    for(auto it = numbers.begin(); it != numbers.end(); ++it){
        std::cout << *it << " ";
    }

    return 0;
}
