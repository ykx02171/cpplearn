#include <iostream>
#include <deque>
#include "Deque.h"
int main() {
    Deque<std::string> dq;
    dq.push_back("Hello");
    dq.push_back("World");
    for(auto it = dq.begin(); it != dq.end(); ++it){
        std::cout << *it << std::endl;
    }
    std::cout <<"=========================\n";
    dq.push_front("C++");
    dq.push_front("Programming");
    for(auto it = dq.begin(); it != dq.end(); ++it){
        std::cout << *it << std::endl;
    }

    std::cout <<"=========================\n";
    dq.pop_front();
    for(auto it = dq.begin(); it != dq.end(); ++it){
        std::cout << *it << std::endl;
    }
    std::cout <<"=========================\n";
    dq.pop_back();
    for(auto it = dq.begin(); it != dq.end(); ++it){
        std::cout << *it << std::endl;
    }

    return 0;
}
