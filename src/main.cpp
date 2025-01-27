#include "WebSocketHandler.hpp"
#include "MarketAPI.hpp"
#include "Logger.hpp"
#include "NotificationHandler.hpp"
#include <thread>
/*

*/
int main() {
    Logger::logInfo("Starting EurekaExchange");

    try {
        NotificationHandler notificationHandler(10);

        WebSocketClient client("test.deribit.com", "443", "/ws/api/v2", notificationHandler);
        client.connect();
        marketAPI::help();

        std::string userInput;
        while (true) {
            Logger::logIO("Waiting for user input...");
            sleep(1);
            std::cout << "Enter a message: ";
            std::getline(std::cin, userInput);

            int cleanInput = marketAPI::inputValidator(userInput);
            if (cleanInput == -1) {
                Logger::logWarn("Invalid input received");
                std::cout << "Invalid Input, Please Try Again!" << std::endl;
                continue;
            } else if (cleanInput == 0) {
                Logger::logInfo("Terminating session");
                std::cout << "Thank you for using EurekaExchange" << std::endl;
                break;
            } else if (cleanInput == 1) {
                marketAPI::help();
                continue;
            } else if (cleanInput == 9) {
                notificationHandler.displayNotifications();
                continue;
            }

            std::string message = marketAPI::parse(cleanInput);
            client.sendMessage(message);
        }
    } catch (const std::exception &e) {
        Logger::logError(std::string("Main error: ") + e.what());
        return 1;
    }

    Logger::logInfo("EurekaExchange terminated gracefully");
    return 0;
}


/*
----- printing
CMAKE
auth??
DOCS
VIDEO
*/