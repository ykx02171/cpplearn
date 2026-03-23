#include "CServer.h"
#include <iostream>
#include "AsioIOServicePool.h"


CServer::CServer(boost::asio::io_context& io_context, short port)
	:_io_context(io_context), _port(port),
	_acceptor(io_context,
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),port)) {
	std::cout << "Server start port is " << port << std::endl;
	StartAccept();
}

CServer::~CServer() {
	std::cout << "CServer destruct" << std::endl;
}

void CServer::HandleAccept(std::shared_ptr<CSession> new_session, const boost::system::error_code& error) {
	if (!error) {
		new_session->Start();
		std::lock_guard<std::mutex> lock(_mutex);
		_sessions.insert(std::make_pair(new_session->GetUuid(), new_session));
	}
	else {
		std::cout << "session accept failed, error is " << error.what() << std::endl;
	}
	StartAccept();
}

void CServer::StartAccept() {
	auto& io_context = AsioIOServicePool::GetInstance().GetIOService();
	std::shared_ptr<CSession> new_session = std::make_shared<CSession>(io_context, this);
	_acceptor.async_accept(new_session->GetSocket(),
		[this, new_session](const boost::system::error_code& ec) {
			this->HandleAccept(new_session,ec);
		});
}

void CServer::ClearSession(std::string uuid) {
	std::lock_guard<std::mutex> lock(_mutex);
	_sessions.erase(uuid);
}