#include <iostream>
#include <string>
#include <memory>
#include <cctype>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <regex>

using std::cout;
using std::endl;
using std::string;
int main(){
    system("chcp 65001");
    std::cout << "Hello World!" << std::endl;
    cout << "Hello Zack!" << endl;
    //默认构造函数，定义一个空字符串
    std::string str1;
    //使用字面值初始化字符串
    string str2 = "Hello";
    //使用拷贝构造函数
    std::string str3(str2);
    //使用部分初始化 Hell
    std::string str4(str2,0,4);
    //使用重复字符进行初始化
    std::string str5(5,'a');
    cout << "str1: " << str1 << std::endl;
    cout << "str2: " << str2 << std::endl;
    cout << "str3: " << str3 << std::endl;
    cout << "str4: " << str4 << std::endl;
    cout << "str5: " << str5 << std::endl;

//    std::string input;
//    std::cout << "请输入字符串: ";
//    std::cin >> input;
//    std::cout << "你输入的字符串是: " << input << std::endl;

    //os 表示输出流对象，<< 表示插入运算符

    std::string  first = "Hello, ";
    std::string  second = "World!";
    std::string  combined = first + second;
    std::cout << combined << std::endl;

    std::string str = "Hello";
    str.append(",World");
    std::cout << str << std::endl;

    str = "Data";
    str += " Structures";
    std::cout << str << std::endl;

    string a = "apple";
    std::string b = "Apple";


    if(a < b){
        std::cout << "a is less than b" << std::endl;
    }else if (a == b){
        std::cout << "a is equal to b" << std::endl;
    }else{
        std::cout << "a is greater than b" << std::endl;
    }

    std::string text = "The quick brown fox jumps over the lazy dog.";
    std::string word = "foxs";
    auto pos = text.find(word);
    if(pos == std::string::npos){
        std::cout << "No match found" << std::endl;
        std::cout << pos << std::endl;
    }else{
        std::cout << "Found at position: " << pos << std::endl;
    }

    text = "I like cats.";
    std::string from = "cats";
    std::string to = "dogs";

    pos = text.find(from);
    if(pos != std::string::npos){
        text.replace(pos, from.length(), to);
        std::cout << "替换后：" << text << std::endl;
    }else{
        std::cout << "'"<< from << "'未找到"<<std::endl;
    }

    str = "Hello, World!";
    std::string sub = str.substr(7,5);
    std::cout << "子串: " << sub << std::endl;

    std::string new_sub = str.substr(7);
    std::cout << "子串: " << new_sub << std::endl;


    std::cout << "字符串长度: "<<str.size()<<std::endl;
    std::cout << "字符串长度: "<<str.length()<<std::endl;
    std::cout <<"字符串的容量："<< str.capacity() << std::endl;
    str += " zack";
    std::cout << "字符串长度: "<<str.length()<<std::endl;
    std::cout <<"字符串的容量："<< str.capacity() << std::endl;

    str = "ABCDE";
    std::cout << str[0] << std::endl;
    if(isupper(str[0]) ){
        std::cout << "大写" << std::endl;
    }else{
        std::cout << "小写" << std::endl;
    }

    //正向遍历
    for(size_t i = 0; i < str.length(); i ++){
        std::cout << "下标为 " << i << "的字符为" << str[i] << std::endl;
    }

    //反向遍历
    for(int i = str.length() - 1; i >= 0 ; i --){
        std::cout << "下标为 " << i << "的字符为" << str[i] << std::endl;
    }

    //越界访问
    //std::cout << str[100] << std::endl;

    //检测越界
    try{
        std::cout << str.at(100) << std::endl;
    }catch(std::out_of_range e){
        std::cout << "越界访问" << std::endl;
    }

    str = "hello world";
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned  char c){ return std::toupper(c);});
    std::cout << str << std::endl;

    for(auto iter = str.begin(); iter != str.end(); ++iter){
        *iter = std::tolower(*iter);
    }

    std::cout << str << std::endl;

    std::stringstream ss;
    ss << "Value: " << 42 << ", " << 3.14;

    std::string result = ss.str();
    std::cout << result << std::endl; // 输出: Value: 42, 3.14

    std::string data = "123 45.67 Hello";
    std::stringstream ss1(data);

    int a1;
    double b1;
    std::string c;

    ss1 >> a1 >> b1 >> c;

    std::cout << "a1: " << a1 << ", b1: " << b1 << ", c: " << c << std::endl;
    // 输出: a: 123, b: 45.67, c: Hello

    int num = 100;
    double pi = 3.14159;

    str1 = std::to_string(num);
    str2 = std::to_string(pi);

    std::cout << "str1: " << str1 << ", str2: " << str2 << std::endl;
    // 输出: str1: 100, str2: 3.141590

    std::string numStr = "256";
    std::string piStr = "3.14";

    ss1.clear();
    ss1.str("");
    ss1 << numStr;
    ss1 >> num;

    std::stringstream ss2(piStr);
    ss2 >> pi;

    std::cout << "num: " << num << ", pi: " << pi << std::endl;
    // 输出: num: 256, pi: 3.14

    text = "The quick brown fox jumps over the lazy dog.";
    std::regex pattern(R"(\b\w{5}\b)"); // 匹配所有5个字母的单词

    std::sregex_iterator it(text.begin(), text.end(), pattern);
    std::sregex_iterator end;

    std::cout << "5个字母的单词有:" << std::endl;
    while (it != end) {
        std::cout << (*it).str() << std::endl;
        ++it;
    }

    return 0;
}
