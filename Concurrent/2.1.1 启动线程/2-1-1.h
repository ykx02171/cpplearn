#pragma once
#include <iostream>
#include <thread>

class background_task
{
public:

	background_task(int i) :_val(i) {}
	void operator()()const {
		std::cout << _val << "Thread\n" << "#######\n";
	}
	int _val;
};

void fun211() {
	std::cout << "Hello World!\n";

	background_task f(1);
	std::thread my_thread1(f);
	std::thread my_thread2(background_task(2));		//如果你传递了一个临时变量，而不是一个命名的变
	//量；C++编译器会将其解析为函数声明，而不是类型对象的定义。
	//这里相当与声明了一个名为my_thread的函数，这个函数带有一个参数(函数指针指向没有参
	//数并返回background_task对象的函数)，返回一个 std::thread 对象的函数，而非启动了一个
	//线程。
	// 解决方法有三个
	std::thread my_thread3((background_task(3)));
	std::thread my_thread4{ background_task(4) };
	std::thread my_thread5([] {background_task(5)(); });//因为重载的是()所以如果没有后面的（），就只是声明，有了才会运行

	std::thread my_thread6([] {std::cout << 6 << "Thread\n" << "#######\n"; });
	my_thread2;
	std::cin.get();
}