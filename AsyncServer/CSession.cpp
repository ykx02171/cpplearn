#include "CSession.h"
#include "CServer.h"
#include <iostream>
CSession::CSession(boost::asio::io_context& io_context, CServer* server) :
	_socket(io_context), _server(server), _b_close(false), _b_head_parse(false) {
	boost::uuids::uuid  a_uuid = boost::uuids::random_generator()();
	_uuid = boost::uuids::to_string(a_uuid);
	_recv_head_node = make_shared<MsgNode>(HEAD_LENGTH);
}

tcp::socket& CSession::GetSocket() {
	return _socket;
}

std::string& CSession::GetUuid() {
	return _uuid;
}

void CSession::Start() {
	memset(_data, 0, MAX_LENGTH);
	_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH), std::bind(&CSession::HandleRead, this,
		std::placeholders::_1, std::placeholders::_2, shared_from_this()));
}

void CSession::Send(char* msg, int max_length) {
	bool pending = false;
	std::lock_guard<std::mutex> lock(_send_lock);
	if (_send_que.size() > 0) {
		pending = true;
	}
	_send_que.push(make_shared<MsgNode>(msg, max_length));
	if (pending) {
		return;
	}

	boost::asio::async_write(_socket, boost::asio::buffer(msg, max_length),
		std::bind(&CSession::HandleWrite, this, std::placeholders::_1, shared_from_this()));
}

void CSession::HandleWrite(const boost::system::error_code& error, shared_ptr<CSession> _self_shared) {
	if (!error) {
		std::lock_guard<std::mutex> lock(_send_lock);
		_send_que.pop();
		if (!_send_que.empty()) {
			auto& msgnode = _send_que.front();
			boost::asio::async_write(_socket, boost::asio::buffer(msgnode->_data, msgnode->_max_len),
				std::bind(&CSession::HandleWrite, this, std::placeholders::_1, _self_shared));
		}
	}
	else {
		std::cout << "handle write failed, error is " << error.what() << endl;
		_server->ClearSession(_uuid);
	}
}

void CSession::HandleRead(const boost::system::error_code& error, size_t  bytes_transferred, shared_ptr<CSession> _self_shared) {
	if (!error) {
		// 计算已经移动的字符数
		if (!error) {
			PrintRecvData(_data, bytes_transferred);
			std::chrono::milliseconds dura(2000);
			std::this_thread::sleep_for(dura);
		}
		int copy_len = 0;
		while (bytes_transferred > 0) {
			if (!_b_head_parse) {
				//收到的数据不足头部大小
				//说明头部数据没收完，先把收到的存进去，然后继续读
				if (bytes_transferred + _recv_head_node->_cur_len < HEAD_LENGTH) {
					memcpy(_recv_head_node->_data + _recv_head_node->_cur_len,
						_data + copy_len, bytes_transferred);
					_recv_head_node->_cur_len += bytes_transferred;
					::memset(_data, 0, MAX_LENGTH);
					_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
						[this, _self_shared](const boost::system::error_code& ec, std::size_t bytes_transferred) {
							this->HandleRead(ec, bytes_transferred, _self_shared);
						});
					return;
				}
				// 收到数据比头部多
				// 头部剩余未复制的长度
				int head_remain = HEAD_LENGTH - _recv_head_node->_cur_len;
				memcpy(_recv_head_node->_data + _recv_head_node->_cur_len,
					_data + copy_len, head_remain);
				// 到这头部节点的长度已经接收完成
				// 
				// 更新已处理的data长度于剩余未处理的长度
				copy_len += head_remain;
				bytes_transferred -= head_remain;
				// 获取头部节点的数据
				short data_len = 0;
				memcpy(&data_len, _recv_head_node->_data, HEAD_LENGTH);
				// 网络字节序转换为主机字节序
				data_len = boost::asio::detail::socket_ops::network_to_host_short(data_len);
				std::cout << "data len is " << data_len << std::endl;
				// 头部长度非法
				if (data_len > MAX_LENGTH) {
					std::cout << "invalid data length is " << data_len << std::endl;
					_server->ClearSession(_uuid);
					return;
				}
				// 接着比对，头部所存消息的长度，与实际接收的消息长度
				_recv_msg_node = make_shared<MsgNode>(data_len);
				// 如果消息的长度小于头部规定的长度，则说明数据没收完，所以先存收到的部分
				if (bytes_transferred < data_len) {
					memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, bytes_transferred);
					::memset(_data, 0, MAX_LENGTH);
					_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
						[this, _self_shared](const boost::system::error_code& ec, std::size_t bytes_transferred) {
							this->HandleRead(ec, bytes_transferred, _self_shared);
						});
					// 不管msg节点有没有处理完成，反正头部处理完成
					_b_head_parse = true;
					return;
				}
				// 接下来是已经处理了头部节点的情况
				// 首先处理消息，这种情况是消息可以收全，但是可能不止收了一次消息
				// 所以先把这次消息全部收掉，然后开始下一轮消息的处理
				memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, data_len);
				_recv_msg_node->_cur_len += data_len;
				copy_len += data_len;
				bytes_transferred -= data_len;
				_recv_msg_node->_data[_recv_msg_node->_total_len] = '\0';

				std::cout << "receive data is " << _recv_msg_node->_data << std::endl;
				//调用send发送测试
				Send(_recv_msg_node->_data, _recv_msg_node->_total_len);

				// 因为上一步已经把上次的消息处理了，
				// 所以这次我们需要把_b_head_parse重新设为false
				// 继续轮询剩余未处理数据
				_b_head_parse = false;
				_recv_head_node->Clear();
				//这种情况是没有粘包，所以先把read服务挂上，然后直接return掉
				if (bytes_transferred <= 0) {
					::memset(_data, 0, MAX_LENGTH);
					_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
						[this, _self_shared](const boost::system::error_code& ec, std::size_t bytes_transferred) {
							this->HandleRead(ec, bytes_transferred, _self_shared);
						});
					return;
				}
				continue;
			}
			// 处理接收的数据仍不足剩余未处理的
			int remain_msg = _recv_msg_node->_total_len - _recv_msg_node->_cur_len;
			if (bytes_transferred < remain_msg) {
				memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, bytes_transferred);
				_recv_msg_node->_cur_len += bytes_transferred;
				::memset(_data, 0, MAX_LENGTH);
				_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
					[this, _self_shared](const boost::system::error_code& ec, std::size_t bytes_transferred) {
						this->HandleRead(ec, bytes_transferred, _self_shared);
					});
				return;
			}
			// 经过上面的判断，现在的消息节点的数据已经比剩余未处理的要小了
			memcpy(_recv_msg_node->_data + _recv_msg_node->_cur_len, _data + copy_len, bytes_transferred);
			_recv_msg_node->_cur_len += remain_msg;
			bytes_transferred -= remain_msg;
			copy_len += remain_msg;
			_recv_msg_node->_data[_recv_msg_node->_total_len] = '\0';
			std::cout << "receive data is " << _recv_msg_node->_data << std::endl;

			Send(_recv_msg_node->_data, _recv_msg_node->_total_len);

			//继续轮询剩余未处理数据
			_b_head_parse = false;
			_recv_head_node->Clear();
			if (bytes_transferred <= 0) {
				::memset(_data, 0, MAX_LENGTH);
				_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH),
					[this, _self_shared](const boost::system::error_code& ec, std::size_t bytes_transferred) {
						this->HandleRead(ec, bytes_transferred, _self_shared);
					});
				return;
			}
			continue;

		}	
	}
	else {
		std::cout << "handle read failed, error is " << error.what() << endl;

		Close();
		_server->ClearSession(_uuid);
	}
}
void CSession::Close() {
	_socket.close();
	_b_close = true;
}

void CSession::PrintRecvData(char* data, int length) {
	stringstream ss;
	string result = "0x";
	for (int i = 0; i < length; i++) {
		string hexstr;
		ss << hex << std::setw(2) << std::setfill('0') << int(data[i]) << endl;
		ss >> hexstr;
		result += hexstr;
	}
	std::cout << "receive raw data is : " << result << endl;
}