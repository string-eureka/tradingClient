#include "WebSocketHandler.hpp"

WebSocketClient::WebSocketClient(const std::string& host, const std::string& port, const std::string& endpoint)
    : host_(host), port_(port), endpoint_(endpoint), ssl_ctx_(net::ssl::context::tlsv12_client), ws_(ioc_, ssl_ctx_) {}


void WebSocketClient::connect() {
    try {
        // DNS Resolver
        tcp::resolver resolver(ioc_);
        auto const results = resolver.resolve(host_, port_);

        // Connect to the server
        beast::get_lowest_layer(ws_).connect(results);

        // Perform SSL handshake
        ws_.next_layer().handshake(net::ssl::stream_base::client);

        // Perform WebSocket handshake
        ws_.handshake(host_, endpoint_);
        std::cout << "WebSocket connection established to " << host_ << endpoint_ << std::endl;

    } catch (const beast::system_error& se) {
        std::cerr << "WebSocket connection error: " << se.what() << std::endl;
        throw;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    }
}

