#include "Session.h"
#include<iostream>

void Session::Start() {
	memset(_data, 0, max_length);
	_socket.async_read_some(boost::asio::buffer(_data, max_length),
		std::bind(&Session::handle_read, this, std::placeholders::_1, std::placeholders::_2,shared_from_this())
	);

}
const std::string& Session::GetUuid() {
	return _uuid;
}

void Session::handle_read(const boost::system::error_code& error,
	std::size_t bytes_transforred, std::shared_ptr<Session> _self_shared) {
	if (!error) {
		std::cout << "Server receive data is " << _data << std::endl;

		boost::asio::async_write(_socket, boost::asio::buffer("hello client", bytes_transforred),
			std::bind(&Session::handle_write, this, std::placeholders::_1,_self_shared)
		);


	}
	else {
		std::cout << "Read error " << std::endl;
		_server->ClearSession(_uuid);
	}
}

void Session::handle_write(const boost::system::error_code& error,
	std::shared_ptr<Session> _self_shared) {
	if (!error) {
		memset(_data, 0, max_length);
		_socket.async_read_some(boost::asio::buffer(_data, max_length),
			std::bind(&Session::handle_read, this, std::placeholders::_1, std::placeholders::_2,_self_shared)
		);
	}
	else {
		std::cout << "Write error " << std::endl;
		_server->ClearSession(_uuid);
	}
}

Server::Server(boost::asio::io_context& ioc, short port) 
	:_ioc(ioc), _acceptor(ioc, tcp::endpoint(tcp::v4(), port)) {
	std::cout << "Server start successfully on port " << port << std::endl;
	start_accept();
}

void Server::ClearSession(std::string uuid) {
	_session.erase(uuid);
}

void Server::start_accept() {
	std::shared_ptr<Session> new_session = std::make_shared<Session>(_ioc, this);
	_acceptor.async_accept(new_session->Socket(), 
		std::bind(&Server::handle_accept, this, new_session, std::placeholders::_1)
	);
}

void Server::handle_accept(std::shared_ptr<Session> new_session, const boost::system::error_code& error) {
	if(!error){
		new_session->Start();
		_session.insert(std::make_pair(new_session->GetUuid(), new_session));
	}
	else {
		
	}
	start_accept();
}