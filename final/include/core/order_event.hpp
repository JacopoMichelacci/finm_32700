#pragma once
#include <iostream>
#include <string>


enum class ORDER_STATUS {
    PENDING,
    FILLED,
    PFILLED,
    REJECTED,
    CANCELED,
};
std::ostream& operator<<(std::ostream& os, ORDER_STATUS status);

enum class ORDER_SIDE {
    BUY,
    SELL,
};
std::ostream& operator<<(std::ostream& os, ORDER_SIDE side);


class OrderEvent {
public:
    long long ts;
    ORDER_SIDE side;
    std::string symbol;
    double qty;
    double price;
    // strategy_id. --- a unique identifier pointing to an instance of a class
    ORDER_STATUS status;

    OrderEvent(long long ts_, ORDER_SIDE side_, double qty_, ORDER_STATUS status_);
};