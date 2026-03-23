#include "AsioIOServicePool.h"
#include<iostream>

AsioIOServicePool::AsioIOServicePool(std::size_t size)
	:_ioServices(size),_works(size),_nextIOService(0) {
	for (std::size_t i = 0; i < size; ++i) {
		_works[i] = std::make_unique<Work>(
			boost::asio::make_work_guard(_ioServices[i].get_executor()));
	}

	//遍历多个IOService创建多个线程，每个线程内部启动IOService
	for (std::size_t i = 0; i < _ioServices.size(); i++) {
		_threads.emplace_back([this, i]() {
			_ioServices[i].run();
			});
	}
}

AsioIOServicePool::~AsioIOServicePool() {
	std::cout << "AsioIOServicePool destruct" << std::endl;
}

boost::asio::io_context& AsioIOServicePool::GetIOService() {
	auto& service = _ioServices[_nextIOService++];
	if (_nextIOService == _ioServices.size()) {
		_nextIOService = 0;
	}
	return service;
}

void AsioIOServicePool::Stop() {
	for (auto& work : _works) {
		work.reset();
	}

	for (auto& t : _threads) {
		t.join();
	}
}

AsioIOServicePool& AsioIOServicePool::GetInstance() {
	static AsioIOServicePool instance(1);
	return instance;
}