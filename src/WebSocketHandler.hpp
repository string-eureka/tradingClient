#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>
#include <thread>
#include <iostream>

namespace beast = boost::beast;
namespace net = boost::asio;
namespace websocket = beast::websocket;
using tcp = net::ip::tcp;

class WebSocketClient {
public:
    WebSocketClient(const std::string& host, const std::string& port, const std::string& endpoint);
    ~WebSocketClient();

    void connect();
    void sendMessage(const std::string& message);
    void close();
    void startReading();

private:
    std::string host_;
    std::string port_;
    std::string endpoint_;
    net::io_context ioc_;
    net::ssl::context ssl_ctx_;
    websocket::stream<beast::ssl_stream<beast::tcp_stream>> ws_;
    std::thread read_thread_;

    void readLoop();
};