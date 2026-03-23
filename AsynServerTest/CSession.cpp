#include "CSession.h"

CSession::CSession(std::shared_ptr<boost::asio::ip::tcp::socket> socket) {

}

void CSession::Connect(const boost::asio::ip::tcp::endpoint& ep) {
	_socket->connect(ep);
}

void CSession::WriteToSocketErr(const std::string& buf) {
	_send_node = std::make_shared<MsgNode>(buf.c_str(), buf.length());
	this->_socket->async_write_some(boost::asio::buffer(_send_node->_msg,
		_send_node->_total_len),
        [this](const boost::system::error_code& ec, std::size_t bytes_transferred) {
            this->WriteCallBackErr(ec, bytes_transferred, _send_node);
        }
		);
}

void CSession::WriteCallBackErr(const boost::system::error_code& ec,
    std::size_t bytes_transferred, std::shared_ptr<MsgNode> msg_node) {
    if (bytes_transferred + msg_node->_cur_len
        < msg_node->_total_len) {
        _send_node->_cur_len += bytes_transferred;
        this->_socket->async_write_some(boost::asio::buffer(_send_node->_msg + _send_node->_cur_len,
            _send_node->_total_len - _send_node->_cur_len),
            [this, msg_node](const boost::system::error_code& ec, std::size_t bytes_transferred) {
                this->WriteCallBackErr(ec, bytes_transferred, msg_node);
            }
            
            );
    }
}

void CSession::WriteCallBack(const boost::system::error_code& ec, std::size_t bytes_transferred) {
    if (ec.value() != 0) {
        std::cout << "Error , code is " << ec.value() << " . Message is " << ec.message();
        return;
    }
    auto& send_data = _send_queue.front();
    send_data->_cur_len += bytes_transferred;
    if (send_data->_cur_len < send_data->_total_len) {
        this->_socket->async_write_some(boost::asio::buffer(send_data->_msg + send_data->_cur_len, send_data->_total_len - send_data->_cur_len),
            [this](const boost::system::error_code& ec, std::size_t bytes_transferred) {
                this->WriteCallBack(ec, bytes_transferred);
            }
        
        );
        return;
    }
    //如果发送完，则pop出队首元素
    _send_queue.pop();
    //如果队列为空，则说明所有数据都发送完,将pending设置为false
    if (_send_queue.empty()) {
        _send_pending = false;
    }
    //如果队列不是空，则继续将队首元素发送
    if (!_send_queue.empty()) {
        auto& send_data = _send_queue.front();
        this->_socket->async_write_some(boost::asio::buffer(send_data->_msg + send_data->_cur_len, send_data->_total_len - send_data->_cur_len),
            [this](const boost::system::error_code& ec, std::size_t bytes_transferred) {
                this->WriteCallBack(ec, bytes_transferred);
            }
        );
        }
}

void CSession::WriteToSocket(const std::string& buf) {
    _send_queue.emplace(new MsgNode(buf.c_str(), buf.length()));
    if (_send_pending) {
        return;
    }
    this->_socket->async_write_some(boost::asio::buffer(buf),
        [this](const boost::system::error_code& ec, std::size_t bytes_transferred) {
            this->WriteCallBack(ec, bytes_transferred);
        });
    _send_pending = true;
}