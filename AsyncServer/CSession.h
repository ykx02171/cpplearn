#pragma once
#include <boost/asio.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <queue>
#include <mutex>
#include <memory>
#include <iostream>
#include <iomanip>
using namespace std;
#define MAX_LENGTH  1024*2
#define HEAD_LENGTH 2
using boost::asio::ip::tcp;
class CServer;



class MsgNode
{
	friend class CSession;
public:
	MsgNode(char* msg, short max_len):_total_len(max_len+HEAD_LENGTH),_cur_len(0) {
		_data = new char[_total_len+1]();
		// 本地字节序转网络字节序 只有数值型数据才需要转换，字符串不需要
		int max_len = boost::asio::detail::socket_ops::host_to_network_short(max_len);
		memcpy(_data, &max_len, HEAD_LENGTH);		// 将max_len的数据传入_data的前HEAD_LENGTH里
		memcpy(_data + HEAD_LENGTH, msg, max_len);	// 将msg从HEAD_LENGTH之后开始传
		_data[_total_len] = '\0';					// 在最后补一个0
	
	}

	MsgNode(short max_len) :_total_len(max_len), _cur_len(0) {	//接收对端数据时构造接收节点用的
		_data = new char[_total_len + 1]();
	}

	~MsgNode() {
		delete[] _data;
	}

	void Clear() {
		::memset(_data, 0, _total_len);			//置0
		_cur_len = 0;
	}

private:
	int _total_len;
	int _cur_len;
	int _max_len;
	char* _data;
};
class CSession :public std::enable_shared_from_this<CSession>
{
public:
	CSession(boost::asio::io_context& io_context, CServer* server);
	~CSession() {
		std::cout << "Session destruct" << endl;
	}
	tcp::socket& GetSocket();
	std::string& GetUuid();
	void Start();
	void Send(char* msg, int max_length);
	void Close();
	void PrintRecvData(char* data, int length);

private:
	void HandleRead(const boost::system::error_code& error, size_t  bytes_transferred, shared_ptr<CSession> _self_shared);
	void HandleWrite(const boost::system::error_code& error, shared_ptr<CSession> _self_shared);
	tcp::socket _socket;
	std::string _uuid;
	char _data[MAX_LENGTH];
	CServer* _server;
	std::queue<shared_ptr<MsgNode> > _send_que;
	std::mutex _send_lock;

	bool _b_close;
	std::shared_ptr<MsgNode> _recv_msg_node;		// 接收的消息体
	bool _b_head_parse=false;								// 表示头部是否解析完成
	std::shared_ptr<MsgNode> _recv_head_node;		// 接收的头部信息
};
