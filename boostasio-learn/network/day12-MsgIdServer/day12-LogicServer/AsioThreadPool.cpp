#include "AsioThreadPool.h"
AsioThreadPool::AsioThreadPool(int threadNum) {
	_work = std::make_unique<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>>(						// 通过deepseek修改的
		boost::asio::make_work_guard(_service.get_executor()));
	for (int i = 0; i < threadNum; ++i) {
		_threads.emplace_back([this]() {
			_service.run();
			});

	}
}

boost::asio::io_context& AsioThreadPool::GetIOService() {
	return _service;
}

void AsioThreadPool::Stop() {
	_work.reset();
	for (auto& t : _threads) {
		t.join();
	}
}