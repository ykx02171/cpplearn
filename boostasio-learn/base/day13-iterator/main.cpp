#include <iostream>
#include <vector>
#include <string>

int main() {
    std::string s("some string");
    //确保s非空
    if(s.begin() != s.end()){
        //第一个字母改为大写
        auto it = s.begin();
        *it = toupper(*it);
    }
    std::cout << s << std::endl;

    std::string s2 = "another string";
    //将s2中第一个非空格字符改为大写
    for(auto it = s2.begin(); it != s2.end() &&
        !isspace(*it); ++it) {
        //如果当前字符不是空格，则将其改为大写
        *it = toupper(*it);
    }
    std::cout << s2 << std::endl;

    // 迭代器it, it能读写vector<int>的元素
    std::vector<int>::iterator it;
    // it2能读写string对象的字符
    std::string::iterator it2;
    // it3只能读元素，不能写元素
    std::vector<int>::const_iterator it3;
    // it4只能读字符,不能写字符
    std::string::const_iterator it4;

    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 使用 const_iterator 遍历
    std::vector<int>::const_iterator cit;
    for (cit = numbers.cbegin(); cit != numbers.cend(); ++cit) {
        std::cout << *cit << " ";  // 读取元素值
    }

    std::cout << std::endl;

    {
        std::vector<int> v;
        const std::vector<int> cv;
        //it1是 vector<int>的迭代器，
        auto it1 = v.begin();
        //it2是const vector<int>的迭代器
        auto it2 = cv.begin();
        //it3的类型是vector<int>::const_iterator
        auto it3 = v.cbegin();
    }

    {
        std::vector<std::string> vs = {"hello", "world"};
        for(auto it = vs.begin(); it != vs.end(); ++it){
            //(*it)解引用获取string对象，再次调用empty()方法判断为空
            if((*it).empty()){
                std::cout << "empty string" << std::endl;
            }
        }

        //依次输出text的每一行直到遇到第一个空行为止
        std::vector<std::string> text = {
            "hello",
            "",
            "world",
        };
        for(auto it = text.cbegin(); it != text.cend() && !(*it).empty(); ++it) {
            std::cout << *it << std::endl;
        }
    }

    //迭代器失效
    {
        //注意下面逻辑错误，在for循环中push元素导致死循环
        std::vector<int> numbers = {1, 2, 3, 4, 5};
//        for(auto i = 0; i < numbers.size(); ++i) {
//            numbers.push_back(i);
//        }

        //注意下面逻辑错误，在for循环中push元素导致迭代器失效，也会导致死循环
//        for(auto it = numbers.begin(); it != numbers.end(); ++it) {
//            numbers.push_back(1);
//        }

        //删除第一个元素
        numbers.erase(numbers.begin() );
    }

    {
        std::vector<int> numbers = {1, 2, 3, 4, 5};
        //循环遍历,并删除其中奇数
        for(auto it = numbers.begin(); it != numbers.end(); ) {
            // 删除奇数
            if(*it % 2 != 0){
                it = numbers.erase(it);
                continue;
            }
            ++it;
        }

        for(auto num : numbers) {
            std::cout << num << " ";
        }

        std::cout << std::endl;
    }

    {
        std::vector<int> numbers = {1, 2, 3, 4, 5};
        //中间位置的迭代器
        auto mid = numbers.begin() + numbers.size()/2;
        //判断迭代器是否有效
        if(mid != numbers.end()){
            std::cout << *mid << std::endl;
        }else{
            std::cout << "mid is end" << std::endl;
        }
    }

    {
        std::vector<int> numbers = {1, 2, 3, 4, 5};
        //二分查找4所在的迭代器为止
        auto beg = numbers.begin(), end = numbers.end();
        auto mid = beg + (end - beg) / 2;
        //二分查找
        while(mid != end && *mid != 4){
            //4在mid的右边
            if(*mid < 4){
                beg = mid + 1;
            }else{ //4在mid的左边
                end = mid;
            }
            mid = beg + (end - beg) / 2;

        }
        if(mid != end){
            std::cout << "4 is found" << std::endl;
        }else{
            std::cout << "4 is not found" << std::endl;
        }

    }

    return 0;
}
