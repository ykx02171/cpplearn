#pragma once
#include<boost/asio.hpp>
#include<iostream>
#include<memory>
#include<queue>
const int RECVSIZE = 1024;
class MsgNode;

// 服务器处理客户端连接的管理类
class CSession
{
public:
	CSession(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
	void Connect(const boost::asio::ip::tcp::endpoint& ep);
	void WriteCallBackErr(const boost::system::error_code& ec, std::size_t bytes_transferred,
		std::shared_ptr<MsgNode> msg_node);
	void WriteToSocketErr(const std::string& buf);

	void WriteCallBack(const boost::system::error_code& ec, std::size_t bytes_transferred);
	void WriteToSocket(const std::string& buf);

	std::queue<std::shared_ptr<MsgNode>> _send_queue;
	std::shared_ptr<boost::asio::ip::tcp::socket> _socket;
	std::shared_ptr<MsgNode> _send_node;
	bool _send_pending;

};

//MsgNode，用来管理发送和接受的数据
class MsgNode {
public:
	// 用于发送的构造方法
	MsgNode(const char* msg, int total_len) :_total_len(total_len), _cur_len(0) {
		_msg = new char[total_len];
		memcpy(_msg, msg, total_len);
	}
	//用于接收的构造方法
	MsgNode(int total_len) :_total_len(total_len), _cur_len(0) {
		_msg = new char[total_len];
	}
	~MsgNode() {
		delete[]_msg;
	}

	int _total_len;
	int _cur_len;
	char* _msg;
};

