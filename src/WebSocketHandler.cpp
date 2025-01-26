#include "WebSocketHandler.hpp"

WebSocketClient::WebSocketClient(
    const std::string &host,
    const std::string &port,
    const std::string &endpoint,
    std::queue<nlohmann::json> &subscriptionQueue,
    std::mutex &queueMutex
)
    : host_(host),
      port_(port),
      endpoint_(endpoint),
      ssl_ctx_(net::ssl::context::tlsv12_client),
      ws_(ioc_, ssl_ctx_),
      subscriptionQueue_(subscriptionQueue),
      queueMutex_(queueMutex) {}


WebSocketClient::~WebSocketClient()
{
    close();
    if (read_thread_.joinable())
    {
        read_thread_.join();
    }
}

void WebSocketClient::connect()
{
    try
    {
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

        startReading();
    }
    catch (const beast::system_error &se)
    {
        std::cerr << "WebSocket connection error: " << se.what() << std::endl;
        throw;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        throw;
    }
}

void WebSocketClient::sendMessage(const std::string &message)
{
    try
    {
        ws_.write(net::buffer(message));
    }
    catch (const std::exception &e)
    {
        std::cerr << "Send error: " << e.what() << std::endl;
    }
}

void WebSocketClient::close()
{
    try
    {
        ws_.close(websocket::close_code::normal);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Close error: " << e.what() << std::endl;
    }
}

void WebSocketClient::startReading()
{
    read_thread_ = std::thread(&WebSocketClient::readLoop, this);
}

void WebSocketClient::readLoop()
{
    try
    {
        while (true)
        {
            beast::flat_buffer buffer;
            ws_.read(buffer);

            std::string response = beast::buffers_to_string(buffer.data());
            nlohmann::json jsonResponse;

            try
            {
                jsonResponse = nlohmann::json::parse(response);
                if (jsonResponse.contains("method") && jsonResponse["method"] == "subscription")
                {
                    std::lock_guard<std::mutex> lock(queueMutex_);
                    subscriptionQueue_.push(jsonResponse);
                    continue;
                }
                std::cout << "Received: " << jsonResponse.dump(4) << std::endl;
            }
            catch (const nlohmann::json::exception &e)
            {
                std::cerr << "JSON Parse Error: " << e.what() << std::endl;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Read error: " << e.what() << std::endl;
    }
}
