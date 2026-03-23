#include "LogicSystem.h"
#include "const.h"
#include "base64.h"
#include <fstream>
#include <boost/filesystem.hpp>
#include "ConfigMgr.h"

using namespace std;

LogicSystem::LogicSystem():_b_stop(false){
	RegisterCallBacks();
	_worker_thread = std::thread (&LogicSystem::DealMsg, this);
}

LogicSystem::~LogicSystem(){
	_b_stop = true;
	_consume.notify_one();
	_worker_thread.join();
}

void LogicSystem::PostMsgToQue(shared_ptr < LogicNode> msg) {
	std::unique_lock<std::mutex> unique_lk(_mutex);
	_msg_que.push(msg);
	//由0变为1则发送通知信号
	if (_msg_que.size() == 1) {
		unique_lk.unlock();
		_consume.notify_one();
	}
}

void LogicSystem::DealMsg() {
	for (;;) {
		std::unique_lock<std::mutex> unique_lk(_mutex);
		//判断队列为空则用条件变量阻塞等待，并释放锁
		while (_msg_que.empty() && !_b_stop) {
			_consume.wait(unique_lk);
		}

		//判断是否为关闭状态，把所有逻辑执行完后则退出循环
		if (_b_stop ) {
			while (!_msg_que.empty()) {
				auto msg_node = _msg_que.front();
				cout << "recv_msg id  is " << msg_node->_recvnode->_msg_id << endl;
				auto call_back_iter = _fun_callbacks.find(msg_node->_recvnode->_msg_id);
				if (call_back_iter == _fun_callbacks.end()) {
					_msg_que.pop();
					continue;
				}
				call_back_iter->second(msg_node->_session, msg_node->_recvnode->_msg_id,
					std::string(msg_node->_recvnode->_data, msg_node->_recvnode->_cur_len));
				_msg_que.pop();
			}
			break;
		}

		//如果没有停服，且说明队列中有数据
		auto msg_node = _msg_que.front();
		cout << "recv_msg id  is " << msg_node->_recvnode->_msg_id << endl;
		auto call_back_iter = _fun_callbacks.find(msg_node->_recvnode->_msg_id);
		if (call_back_iter == _fun_callbacks.end()) {
			_msg_que.pop();
			std::cout << "msg id [" << msg_node->_recvnode->_msg_id << "] handler not found" << std::endl;
			continue;
		}
		call_back_iter->second(msg_node->_session, msg_node->_recvnode->_msg_id, 
			std::string(msg_node->_recvnode->_data, msg_node->_recvnode->_cur_len));
		_msg_que.pop();
	}
}

void LogicSystem::RegisterCallBacks() {
	_fun_callbacks[ID_TEST_MSG_REQ] = [this](shared_ptr<CSession> session, const short& msg_id,
		const string& msg_data) {
			Json::Reader reader;
			Json::Value root;
			reader.parse(msg_data, root);
			auto data = root["data"].asString();
			std::cout << "recv test data is  " << data << std::endl;

			Json::Value  rtvalue;
			Defer defer([this, &rtvalue, session]() {
				std::string return_str = rtvalue.toStyledString();
				session->Send(return_str, ID_TEST_MSG_RSP);
				});

			rtvalue["error"] = ErrorCodes::Success;
			rtvalue["data"] = data;
	};

	_fun_callbacks[ID_UPLOAD_FILE_REQ] = [this](shared_ptr<CSession> session, const short& msg_id,
		const string& msg_data) {
			Json::Reader reader;
			Json::Value root;
			reader.parse(msg_data, root);
			auto data = root["data"].asString();
			//std::cout << "recv file data is  " << data << std::endl;

			Json::Value  rtvalue;
			Defer defer([this, &rtvalue, session]() {
				std::string return_str = rtvalue.toStyledString();
				session->Send(return_str, ID_UPLOAD_FILE_RSP);
				});

			// 解码
			std::string decoded = base64_decode(data);

			auto seq = root["seq"].asInt();
			auto name = root["name"].asString();
			auto total_size = root["total_size"].asInt();
			auto trans_size = root["trans_size"].asInt();
			auto file_path = ConfigMgr::Inst().GetFileOutPath();
			auto file_path_str = (file_path / name).string();
			std::cout << "file_path_str is " << file_path_str << std::endl;
			std::ofstream outfile;
			//第一个包
			if (seq == 1) {
				// 打开文件，如果存在则清空，不存在则创建
				outfile.open(file_path_str, std::ios::binary | std::ios::trunc);
			}
			else {
				// 保存为文件
				outfile.open(file_path_str, std::ios::binary | std::ios::app);
			}

			
			if (!outfile) {
				std::cerr << "无法打开文件进行写入。" << std::endl;
				return 1;
			}

			outfile.write(decoded.data(), decoded.size());
			if (!outfile) {
				std::cerr << "写入文件失败。" << std::endl;
				return 1;
			}

			outfile.close();
			std::cout << "文件已成功保存为: " << name <<  std::endl;

			rtvalue["error"] = ErrorCodes::Success;
			rtvalue["total_size"] = total_size;
			rtvalue["seq"] = seq;
			rtvalue["name"] = name;
			rtvalue["trans_size"] = trans_size;
	};
}

