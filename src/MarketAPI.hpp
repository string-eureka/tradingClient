#pragma once
#include <string.h>
#include <iostream>
#include <algorithm>
#include "json.hpp"

namespace marketAPI{
    /*
        1. Place order 
        2. Cancel order 
        3. Modify order 
        4. Get orderbook
        View current positions
         Real-time market data streaming via WebSocket          
    */
    int inputValidator(const std::string& s);
    std::string parse(int x);
    std::string authenticate();
    void help();
    std::string buy();
    std::string cancel();
    std::string modifyOrder();
    std::string getOrderbook();
    std::string getCurrentPositions();
}