#pragma once
#include <string>
#include <memory>


enum class OrderStatus {
    NEW, 
    PARTIALLY_FILLED, 
    FILLED, 
    CANCELLED 
};
template <typename PriceType, typename OrderIdType>
struct Order {
    OrderIdType id;
    std::string symbol;
    PriceType price;
    int quantity;
    bool is_buy;
    OrderStatus status;
    Order(OrderIdType id, std::string sym, PriceType pr, int qty, bool buy)
        : id(id), symbol(std::move(sym)), price(pr), quantity(qty), is_buy(buy), status(OrderStatus::NEW) {}
};