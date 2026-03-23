#include"boost/asio.hpp"
#include <iostream>
#include<set>
using boost::asio::ip::tcp;
const int max_length = 1024;
typedef std::shared_ptr<tcp::socket> socket_ptr;
std::set<std::shared_ptr<std::thread>> thread_set;

void session(socket_ptr sock) {
	try {
		for (;;) {
			char data[max_length];
			memset(data, '\0', max_length);
			boost::system::error_code error;
			std::size_t length = sock->read_some(boost::asio::buffer(data, max_length), error);
			if (error == boost::asio::error::eof) {
				std::cout << "Connection closed by peer" << std::endl;
				break;
			}
			else if (error) {
				throw boost::system::system_error(error);
			}

			std::cout << "receive from " << sock->remote_endpoint().address().to_string() << std::endl;
			std::cout << "received message is " << data << std::endl;

			//回传给对方
			boost::asio::write(*sock, boost::asio::buffer(data, length));

		}
	}
	catch (std::exception& e) {
		std::cout << "Connect failed, code is " << e.what()
			<< std::endl;
	}
}

void server(boost::asio::io_context& io_context, unsigned short port) {
	tcp::acceptor a(io_context, tcp::endpoint(tcp::v4(), port));
	for (;;) {
		socket_ptr socket(new tcp::socket(io_context));
		a.accept(*socket);
		auto t = std::make_shared<std::thread>(session, socket);
		thread_set.insert(t);
	}
}
int main()
{
	try {
		boost::asio::io_context ioc;
		server(ioc, 10086);
		for (auto& t : thread_set)
		{
			t->join();
		}
	}
	catch (std::exception& e) {
		std::cout << "Connect failed, code is " << e.what()
			<< std::endl;
	}
}
