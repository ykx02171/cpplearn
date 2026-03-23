// ProtobufDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "msg.pb.h"
int main()
{
    Book book;
    book.set_name("CPP programing");
    book.set_pages(100);
    book.set_price(200);
    std::string bookstr;
	//序列化写入字符串
    book.SerializeToString(&bookstr);       
    std::cout << "serialize str is " << bookstr << std::endl;
    
	//服务器操作类似于这样
    Book book2;
	//反序列化到对象
    book2.ParseFromString(bookstr);
    std::cout << "book2 name is " << book2.name() << " price is "
        << book2.price() << " pages is " << book2.pages() << std::endl;
    getchar();
}
