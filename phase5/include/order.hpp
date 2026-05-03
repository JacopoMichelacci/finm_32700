#pragma once

#include <string>


struct Order {
    std::string id;
    double price;
    int qty;
    bool isBuy;
};