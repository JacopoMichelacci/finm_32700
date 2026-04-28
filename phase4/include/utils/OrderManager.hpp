#pragma once 
#include "Order.hpp"
#include "OrderBook.hpp"
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <memory> 
#include <type_traits> 

template<typename PriceType, typename OrderIdType>
class OrderManager { 
    static_assert(std::is_integral<OrderIdType>::value, "OrderIdType must be an integral type");
    public: 
        using OrderType = Order<PriceType, OrderIdType>;
        using OrderPtr = std::shared_ptr<OrderType>;
    private:
        std::unordered_map<OrderIdType, OrderPtr> orders;
        OrderBook<PriceType, OrderIdType>& orderBook;
    public:
        OrderManager(OrderBook<PriceType, OrderIdType>& b) : orderBook(b) {}

        void newOrder(OrderIdType id, std::string symbol, PriceType price, int quantity, bool is_buy) {
            auto order = std::make_shared<OrderType>(id, symbol, price, quantity, is_buy);
            orders[id] = order;
            orderBook.addOrder(*order);
        }

        void cancelOrder(OrderIdType id) {
            if (orders.find(id) == orders.end()) return;
            orders[id]->status = OrderStatus::CANCELLED;
            orders.erase(id);
        }

        void markPartialFill(OrderIdType id, int qty) {
            auto& o = orders[id];
            o->quantity -= qty;
            if (o->quantity == 0){
                o->status = OrderStatus::FILLED;
            } else {
                o->status = OrderStatus::PARTIALLY_FILLED;
            }
        }
};