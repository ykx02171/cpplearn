#include <boost/asio.hpp>
#include <iostream>
#include <thread>

using boost::asio::ip::udp;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "用法: client <服务器IP> <客户端ID>\n";
        return 1;
    }

    std::string server_ip = argv[1];
    std::string client_id = argv[2];

    try {
        boost::asio::io_context io_context;
        udp::socket socket(io_context, udp::endpoint(udp::v4(), 0)); // 随机本地端口

        udp::resolver resolver(io_context);
        udp::endpoint server_endpoint = *resolver.resolve(udp::v4(), server_ip, "12345").begin();

        // 向服务器发送客户端ID
        socket.send_to(boost::asio::buffer(client_id), server_endpoint);
        std::cout << "已向服务器注册: " << client_id << std::endl;

        // 等待服务器发送对方的地址
        char data[1024];
        udp::endpoint remote_endpoint;
        size_t length = socket.receive_from(boost::asio::buffer(data, 1024), remote_endpoint);
        std::string remote_info(data, length);

        std::cout << "收到对方的地址信息: " << remote_info << std::endl;
        // 解析对方的IP和端口
        size_t colon = remote_info.find(':');
        if (colon == std::string::npos) {
            std::cerr << "地址信息格式错误\n";
            return 1;
        }

        std::string remote_ip = remote_info.substr(0, colon);
        int remote_port = std::stoi(remote_info.substr(colon + 1));

        udp::endpoint peer_endpoint(boost::asio::ip::make_address(remote_ip), remote_port);

        // 开启一个线程监听来自对方的消息
        std::thread listener([&socket]() {
            char recv_buf[1024];
            udp::endpoint sender_ep;
            while (true) {
                size_t len = socket.receive_from(boost::asio::buffer(recv_buf, 1024), sender_ep);
                std::string msg(recv_buf, len);
                std::cout << "收到来自 " << sender_ep.address().to_string() << ":" << sender_ep.port() << " 的消息: " << msg << std::endl;
            }
            });

        // 尝试向对方发送消息
        while (true) {
            std::string message;
            std::cout << "输入要发送的消息: ";
            std::getline(std::cin, message);
            socket.send_to(boost::asio::buffer(message), peer_endpoint);
        }

        listener.join();
    }
    catch (std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
    }

    return 0;
}


