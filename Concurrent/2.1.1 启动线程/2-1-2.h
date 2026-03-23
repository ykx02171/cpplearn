#pragma once
#include<iostream>
#include<thread>
#include <chrono>

struct func
{
	int& i;
	int val;
	func(int& i_) : i(i_) {}
	void operator() ()
	{
		for (unsigned j = 0; j < 1000000; ++j)
		{
			std::cout << "子线程访问 i: " << i << std::endl; // 访问悬垂引用！
			std::this_thread::sleep_for(std::chrono::seconds(1)); // 缩短休眠时间
		}
	}
};
void fun212()
{
	int some_local_state = 42;
	func my_func(some_local_state);
	std::thread my_thread(my_func);
	my_thread.detach(); // 2 不等待线程结束
	std::cout << "fun212 函数结束，some_local_state 即将被销毁！" << std::endl;
} // 3 新线程可能还在运行