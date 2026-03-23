#pragma once
#include<iostream>
#include<boost/asio.hpp>
#include<map>
#include<boost/uuid/uuid_io.hpp>
#include<boost/uuid/uuid_generators.hpp>
using boost::asio::ip::tcp;
class Server;
class MsgNode
{
	friend class Session;
public:
	MsgNode(char* msg, int max_len) {
		_data = new char[max_len];
		memcpy(_data, msg, max_len);
	}
	~MsgNode() {
		delete[] _data;
	}
private:
	int _cur_len;
	int _max_len;
	char* _data;
};

class Session:public std::enable_shared_from_this<Session>
{
public:
	Session(boost::asio::io_context& ioc,Server* server)
		:_socket(ioc),_server(server) {
		boost::uuids::uuid a_uuid = boost::uuids::random_generator()();
		_uuid = boost::uuids::to_string(a_uuid);
	}
	~Session() {
		std::cout << "session destruct delete this " << this << std::endl;
	}
	tcp::socket& Socket() {
		return _socket;
	}

	void Start();
	const std::string& GetUuid();

private:
	void handle_read(const boost::system::error_code& error,
		std::size_t bytes_transforred, std::shared_ptr<Session> _self_shared);
	void handle_write(const boost::system::error_code& error, std::shared_ptr<Session> _self_shared);
	tcp::socket _socket;
	enum {max_length = 1024};
	char _data[max_length];
	Server* _server;
	std::string _uuid;
};


class Server {
public:
	Server(boost::asio::io_context& ioc, short port);
	void ClearSession(std::string uuid);
private:
	void start_accept();
	void handle_accept(std::shared_ptr<Session> new_session, const boost::system::error_code& error);
	boost::asio::io_context& _ioc;
	tcp::acceptor _acceptor;
	std::map<std::string, std::shared_ptr<Session>> _session;
};
