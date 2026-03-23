// HelloWorld.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>

void hello() {
    std::cout << "Hello Concurrent World\n";
}

int main()
{
    std::thread t(hello);
    t.join();                   // 新的线程启动之后③，初始线程继续执行。如果它不等待新线程结束，它就将自顾自地继续运
                                // 行到main()的结束，从而结束程序——有可能发生在新线程运行之前。这就是为什么在④这里
                                // 调用 join() 的原因
}

