//
// Created by secon on 2024/11/16.
//

#ifndef DAY19_CLASS_MYSTRING_H
#define DAY19_CLASS_MYSTRING_H
#include <iostream>
#include <cstring>
class MyString {
public:
    MyString():_data(nullptr){}
    MyString(const char* str);
    MyString(const MyString& other);
    MyString& operator =(const MyString& other);

    MyString(MyString&& other);
    MyString& operator =(MyString&& other);

    MyString& operator + (const MyString& other);
    bool operator == (const MyString& other);
    friend std::ostream & operator << (std::ostream & out , const MyString & other);
    ~MyString();
private:
    char* _data;
};


#endif //DAY19_CLASS_MYSTRING_H
