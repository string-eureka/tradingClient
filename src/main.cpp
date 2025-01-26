#include "WebSocketHandler.hpp"
#include "MarketAPI.hpp"
#include <queue>
#include <mutex>

std::mutex subscriptionQueueMutex;            // Mutex for thread-safe access
std::queue<nlohmann::json> subscriptionQueue; // Global queue for subscription responses

int main()
{
    std::cout << "Welcome to EurekaExchange!" << std::endl;

    try
    {
        WebSocketClient client("test.deribit.com", "443", "/ws/api/v2", subscriptionQueue, subscriptionQueueMutex);
        client.connect();
        marketAPI::help();

        std::string user_input;
        while (true)
        {
            sleep(1);
            std::cout << "Enter a message: ";
            std::getline(std::cin, user_input);

            int clean_input = marketAPI::inputValidator(user_input);
            if (clean_input == -1)
            {
                std::cout << "Invalid Input, Please Try Again!" << std::endl;
                continue;
            }
            else if (clean_input == 0)
            {
                std::cout << "Terminating Session\n"
                          << "Thank you for using EurekaExchange\n";
                break;
            }
            else if (clean_input == 1)
            {
                marketAPI::help();
                continue;
            }
            else if (clean_input == 9)
            {
                std::lock_guard<std::mutex> lock(subscriptionQueueMutex); // Lock the mutex for safe access
                int count = 0;
                while (!subscriptionQueue.empty() && count < 10)
                {
                    std::cout << "Notification: " << subscriptionQueue.front().dump(4) << std::endl;
                    subscriptionQueue.pop();
                    ++count;
                }
                if (count == 0)
                {
                    std::cout << "No notifications available.\n";
                }
                continue;
            }

            std::string message = marketAPI::parse(clean_input);
            client.sendMessage(message);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Main Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

/*

Fixing APIS
Fix exit bug
Latency benchmarking and Optimization
*/
