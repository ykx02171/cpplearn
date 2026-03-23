// server.cpp
#include <boost/asio.hpp>
#include <iostream>
#include <unordered_map>

using boost::asio::ip::udp;

int main() {
    try {
        boost::asio::io_context io_context;
        udp::socket socket(io_context, udp::endpoint(udp::v4(), 12345));

        std::unordered_map<std::string, udp::endpoint> clients;
        char data[1024];

        std::cout << "服务器已启动，等待客户端连接..." << std::endl;

        while (true) {
            udp::endpoint sender_endpoint;
            size_t length = socket.receive_from(boost::asio::buffer(data, 1024), sender_endpoint);
            std::string message(data, length);

            std::string client_id = message; // 简化：客户端发送唯一标识符

            // 记录客户端的公共地址
            clients[client_id] = sender_endpoint;
            std::cout << "接收到客户端 " << client_id << " 的地址: " << sender_endpoint.address().to_string() << ":" << sender_endpoint.port() << std::endl;

            // 如果已有两个客户端，交换它们的信息
            if (clients.size() == 2) {
                auto it = clients.begin();
                std::string client1_id = it->first;
                udp::endpoint client1_ep = it->second;
                ++it;
                std::string client2_id = it->first;
                udp::endpoint client2_ep = it->second;

                // 发送对方的地址给每个客户端
                std::string msg_to_client1 = client2_ep.address().to_string() + ":" + std::to_string(client2_ep.port());
                socket.send_to(boost::asio::buffer(msg_to_client1), client1_ep);

                std::string msg_to_client2 = client1_ep.address().to_string() + ":" + std::to_string(client1_ep.port());
                socket.send_to(boost::asio::buffer(msg_to_client2), client2_ep);

                std::cout << "已交换客户端 " << client1_id << " 和 " << client2_id << " 的地址信息。" << std::endl;
            }
        }
    }
    catch (std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
    }

    return 0;
}