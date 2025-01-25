#include "WebSocketHandler.hpp"
#include "MarketAPI.hpp"


int main() {
    std::cout << "Welcome to EurekaExchange!" << std::endl;

    try {
        WebSocketClient client("test.deribit.com", "443", "/ws/api/v2");        
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
    The following is my code for an cli  trading application that communicates via websockets. 
    What I want you to do is to start the websocket connection in a different thread. However I want that at a time either the input loop (post Enter a message)
    or the output (response from the websocket) takes place at a time. Implement a solution for this. Also implment the sendMessage function that directly
    sends the string input to the websocket. Implement the close function as well.
    Redo the Websocket functioning, a single lock/mutex exists for the read while loop in the main.cpp file and the output in the Market API file.
    Initially the lock is empty, the read loop then aquires the lock, when a request is to be sent via the websocket, the lock is acquired by the Websockethandler.
    Once it recieves and prints the response the lock is released and the main read loop aquires it.
    When the read loop ends/exits, the lock is given to the websockethandler, and then the program ends.
    
Rewrite entire websockets code
Store access_token in password class.

Latency benchmarking and Optimization
Implement Notifications

Fix autodisconnect bug - I think it happens when the program runs in the background - windows optimizing wsl or something.
Could be fixed by pinging the server every n minutes.

*/
