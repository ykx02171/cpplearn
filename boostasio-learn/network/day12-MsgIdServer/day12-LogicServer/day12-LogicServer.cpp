#include <iostream>
#include "CServer.h"
#include<csignal>
#include<thread>
#include<mutex>
#include "AsioThreadPool.h"
using namespace std;
/////////////////////////////////////////////////
//bool bstop = false;
//std::condition_variable cond_quit;
//std::mutex mutex_quit;*/
/////////////////////////////////////////////////////////
// 一般方式
//void SigHandler(int sig) {
//	if (sig == SIGINT || sig == SIGTERM) {		// ctrl c 和q
//		std::unique_lock<std::mutex> lock_quit(mutex_quit);
//		bstop = true;					//bstop是全局的，为了保证bstop的安全需要加锁
//		cond_quit.notify_one();
//	}
//}
////////////////////////////////////////////////////////

bool bstop = false;
std::condition_variable cond_quit;
std::mutex mutex_quit;


int main()
{
	try {
		auto pool = AsioThreadPool::GetInstance();


		// 这个是asio封装的方法，asio异步监听信号
		boost::asio::io_context io_context;
		boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
		signals.async_wait([pool, &io_context](auto, auto) {
			io_context.stop();
			pool->Stop();
			std::unique_lock<std::mutex> lock(mutex_quit);
			bstop = true;
			cond_quit.notify_one();
			});

		CServer s(pool->GetIOService(), 10086);
		{
			std::unique_lock<std::mutex> lock(mutex_quit);
			while (!bstop) {
				cond_quit.wait(lock);
			}

		}
		/////////////////////////////////////////
		// 一般方式 利用多线程通信的方法，C风格退出
		//boost::asio::io_context  io_context;
		//std::thread net_work_thread([&io_context] {			//io_context是单例模式，不能拷贝和赋值
		//	CServer s(io_context, 10086);
		//	io_context.run();

		//	});
		//signal(SIGINT, SigHandler);
		//signal(SIGTERM, SigHandler);

		//while (!bstop) {
		//	std::unique_lock<std::mutex> lock_quit(mutex_quit);
		//	cond_quit.wait(lock_quit);
		//}

		//io_context.stop();
		//net_work_thread.join();
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << endl;
	}
}