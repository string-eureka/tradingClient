#include "WebSocketHandler.hpp"
#include "MarketAPI.hpp"


int main() {
    std::cout << "Welcome to EurekaExchange!" << std::endl;

    try {
        WebSocketClient client("test.deribit.com", "443", "/ws/api/v2");
        client.connect();
        marketAPI::help();

        std::string user_input;
        while (true) {

            std::cout << "Enter a message ";
            std::getline(std::cin, user_input);

            int clean_input = marketAPI::inputValidator(user_input);
            if (clean_input == -1) {
                std::cout << "Invalid Input, Please Try Again!" << std::endl;
                continue;
            }
            else if (clean_input == 0){
                std::cout << "Terminating Sesssion\n"
                          << "Thank you for using EurekaExchange\n";
                break;
            }
            else if (clean_input == 1){
                marketAPI::help();
                continue;
            }
            else if (clean_input == 9){

            }

            std::string message = marketAPI::parse(clean_input);
            // client.sendMessage(message);
        }

        // client.close();
    } catch (const std::exception& e) {
        std::cerr << "Main Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

/*

Implement Notifications
Store access_token in password class.
Fix exit bug
Latency benchmarking and Optimization

*/
