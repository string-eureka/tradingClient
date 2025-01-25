// #include <boost/beast/core.hpp>
// #include <boost/beast/websocket.hpp>
// #include <boost/beast/ssl.hpp>
// #include <boost/asio/ssl/stream.hpp>
// #include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <string>
#include "WebSocketHandler.hpp"
// #include <thread>

namespace beast = boost::beast;         
namespace net = boost::asio;           
namespace websocket = beast::websocket; 
using tcp = net::ip::tcp;

/*
    Welcome!

        establish a connection!

        (Websocket connection object)Quit after one failed attempt
        - If connected, print instructions
        Event Loop
            Interface APIS
            Notifications
            quiz to end session.
        
*/
int main() {

        std::cout << "Welcome to EurekaExchange!" << std::endl;
        
        std::string host = "test.deribit.com";
        std::string port = "443";
        std::string endpoint = "/ws/api/v2";

        try {
            std::cout << "Establishing a connection with the Deribit Exchange..." << std::endl;
            WebSocketConnection ws_connection =  WebSocketConnection(host, port, endpoint);
            websocket::stream<beast::ssl_stream<beast::tcp_stream>> ws = ws_connection.getStream();
        }
        catch (const std::exception& e){
            std::cerr << "Error" << e.what();
            return 1;
        }

        // while(ws.)

    }
