#pragma once
#include"Singleton.h"
#include<queue>
#include<thread>
#include<map>
#include<functional>
#include"const.h"
#include"CSession.h"
#include<json/json.h>
#include<json/value.h>
#include<json/reader.h>

typedef function<void(std::shared_ptr<CSession>, const short& msg_id, const std::string& msg_data)> FunCallBack;
class LogicSystem:public Singleton<LogicSystem>
{
	friend class Singleton<LogicSystem>;		//因为单例类是私有的
public:
	~LogicSystem();
	void PostMsgQue(std::shared_ptr<LogicNode>msg);
private:
	LogicSystem();
	void RegisterCallBacks();
	void HelloWordCallBacks(std::shared_ptr<CSession>, const short& msg_id, const std::string& msg_data);
	void DealMsg();


	std::queue<std::shared_ptr<LogicNode>> _msg_que;
	std::mutex _mutex;
	std::condition_variable _consume;
	std::thread _worker_thread;
	bool _b_stop;
	std::map<short, FunCallBack> _fun_callback;
};

