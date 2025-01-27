#pragma once
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <string>
#include <thread>
#include <boost/beast/ssl.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "../include/json.hpp"
#include "NotificationHandler.hpp"
#include "Logger.hpp"


namespace beast = boost::beast;
namespace net = boost::asio;
namespace websocket = beast::websocket;
using tcp = net::ip::tcp;

class WebSocketClient
{
public:
    WebSocketClient(const std::string &host, const std::string &port, const std::string &endpoint,
                    NotificationHandler &notificationHandler);
    ~WebSocketClient();

    void connect();
    void sendMessage(const std::string &message);
    void close();

private:
    void readLoop();

    std::string host_;
    std::string port_;
    std::string endpoint_;
    net::io_context ioc_;
    net::ssl::context sslCtx_;
    websocket::stream<beast::ssl_stream<beast::tcp_stream>> ws_;
    std::thread readThread_;
    NotificationHandler &notificationHandler_;
};