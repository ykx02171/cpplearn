#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <regex>
#include <map>



void base(){
    //    默认构造函数
    std::string str1;

//    使用字符串字面值初始化
    std::string str2 = "Hello";

//    使用拷贝构造函数
    std::string str3(str2);

//    使用部分初始化
    std::string str4(str2,0,3);
//   使用重复字符初始化
    std::string str5(5,'A');
/*
//    std::cout << "str1: " << str1 << std::endl;
//    std::cout << "str2: " << str2 << std::endl;
//    std::cout << "str3: " << str3 << std::endl;
//    std::cout << "str4: " << str4 << std::endl;
//    std::cout << "str5: " << str5 << std::endl;
//    str2: Hello
//    str3: Hello
//    str4: Hel
//    str5: AAAAA
 */

//常见字符串操作
//    拼接用+ 和 append
//    查找用find()
    std::string text = "The quick brown fox jumps over the lazy dog.";
    std::string word = "fox";

    size_t pos = text.find(word);
//    查找
    if (pos != std::string::npos) {
        std::cout << "found '" << word << "' position: " << pos << std::endl;
    } else {
        std::cout << "'" << word << "' not found。" << std::endl;
    }
//    替换
    std::string text1 = "I like cats.";
    std::string from = "cats";
    std::string to = "dogs";

    size_t pos1 = text1.find(from);
    if (pos1 != std::string::npos) {
        text1.replace(pos1, from.length(), to);
        std::cout << "替换后: " << text1 << std::endl; // 输出: I like dogs.
    } else {
        std::cout << "'" << from << "' 未找到。" << std::endl;
    }

//    substr()获取子字符串
    std::string subStr = "Hello, world!";
    std::string sub = subStr.substr(7,5);  //从7开始长度5
    std::cout << subStr << std::endl;

//    长度 str.length 与str.size都可以

//    at函数
    std::string strAt = "ABCDE";
    try {
        char c1 = strAt.at(2);
        std::cout<<c1<<std::endl;
        char c = strAt.at(10); // 超出范围，会抛出异常
    } catch (const std::out_of_range& e) {
        std::cout << "异常捕获: " << e.what() << std::endl;
    }

//    结合transform来转换字符大小写
    std::string strTrans = "Hello, World!";
    std::transform(strTrans.begin(),strTrans.end(),strTrans.begin(),
                   [](unsigned  char c){
                       return std::toupper(c);
                   });
    std::cout << strTrans << std::endl;
    std::transform(strTrans.begin(),strTrans.end(),strTrans.begin(),
                   [](unsigned  char c){
                       return std::tolower(c);
                   });
    std::cout << strTrans << std::endl;

//    其他函数
//    empty() 检查字符串是否为空
//    clear() 清空字符串内容
//    erase() 删除字符串部分内容
//    insert() 在指定位置插入字符串或字符
//    replace() 替换字符串的部分内容
//    find_first_of(), find_last_of()：查找字符集合中的任何一个字符。


//    stringstream
//    std::stringstream ss;
    std::string data = "123 45.67 Hello";
    std::stringstream ss(data);
    int a;
    double b;
    std::string c;

    ss >> a >> b >> c;

    std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;
    // 输出: a: 123, b: 45.67, c: Hello


//    将其他类型转换为 std::string：
//    使用 std::to_string()

//    将 std::string 转换为其他类型：
//    使用字符串流
//    使用 std::stoi(), std::stod() 等函数（C++11 及以上）

    std::string numStr = "256";
    std::string piStr = "3.14";

    int num = std::stoi(numStr);
    double pi = std::stod(piStr);

    std::cout << "num: " << num << ", pi: " << pi << std::endl;
    // 输出: num: 256, pi: 3.14

    std::string textReg = "The quick brown fox jumps over the lazy dog.";
    std::regex pattern(R"(\b\w{5}\b)"); // 匹配所有5个字母的单词

    std::sregex_iterator it(textReg.begin(), textReg.end(), pattern);
    std::sregex_iterator end;

    std::cout << "5个字母的单词有:" << std::endl;
    while (it != end) {
        std::cout << (*it).str() << std::endl;
        ++it;
    }
}


void textAnalyse(){
    std::string text;
    std::cout << "请输入一段文本（结束请输入Ctrl+D/Ctrl+Z）：\n";

    // 读取整段文本
    std::ostringstream oss;
    std::string line;
    while (std::getline(std::cin, line)) {
        if(line=="ci"){ break;}

        oss << line << " ";
    }
    text = oss.str();

    // 使用字符串流分割单词
    std::stringstream ss(text);
    std::string word;
    std::map<std::string, int> wordCount;
    size_t totalWords = 0;
    std::string longestWord;

    while (ss >> word) {
        // 去除标点符号（简单处理）
        word.erase(std::remove_if(word.begin(), word.end(),
                                  [](char c) { return ispunct(c); }), word.end());

        // 转为小写
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (!word.empty()) {
            wordCount[word]++;
            totalWords++;
            if (word.length() > longestWord.length()) {
                longestWord = word;
            }
        }
    }

    std::cout << "\n统计结果:\n";
    std::cout << "总单词数: " << totalWords << std::endl;
    std::cout << "每个单词出现的次数:\n";
    for (const auto& pair : wordCount) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    std::cout << "最长的单词: " << longestWord << std::endl;

    // 查找指定单词的出现次数
    std::string searchWord;
    std::cout << "\n请输入要查找的单词: ";
    std::cin >> searchWord;
    // 转为小写
    std::transform(searchWord.begin(), searchWord.end(), searchWord.begin(), ::tolower);
    auto it = wordCount.find(searchWord);
    if (it != wordCount.end()) {
        std::cout << "'" << searchWord << "' 出现了 " << it->second << " 次。" << std::endl;
    } else {
        std::cout << "'" << searchWord << "' 未在文本中找到。" << std::endl;
    }


}

int main() {
//    base();
    textAnalyse();
    return 0;
}