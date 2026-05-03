#pragma once

#include <map>
#include <unordered_map>

#include "order.hpp"


class OrderBook {
public:
    bool addOrder(const Order& order) {
        auto [it, inserted] = orderContainer.emplace(order.id, std::move(order));
        
        if (!inserted) { return false; }

        orderLevels[order.price][order.id] = &(it->second);
        return true;
    }

    bool modifyOrder(const std::string& id, double new_price = -1, int new_qty = -1) {
        auto it = orderContainer.find(id);
        if (it == orderContainer.end()) { return false; }

        Order& order = it->second;
            
        if (new_price > 0 && new_price != order.price) {
            auto it_level = orderLevels.find(order.price);
            

            // fixing the book level
            it_level->second.erase(order.id);

            if ((it_level->second).empty()) {
                orderLevels.erase(it_level);
            }

            // changing the price
            order.price = new_price;
            orderLevels[order.price][order.id] = &order;
        }

        if (new_qty > 0) { 
            order.qty = new_qty;
        }

        return true;
    }

    bool deleteOrder(const std::string& id) {
        auto it = orderContainer.find(id);
        if (it == orderContainer.end()) { return false; }

        Order& order = it->second;

        auto it_level = orderLevels.find(order.price);

        // del order from order book level
        (it_level->second).erase(order.id);
        if ((it_level->second).empty()) { orderLevels.erase(it_level); }
        
        //del order from general container
        orderContainer.erase(order.id);

        return true;
    }

    // getter

    bool get_order(const std::string& id) const {
        auto it = orderContainer.find(id);
        if (it != orderContainer.end()) { return true; }
        return false;
    }


private:
    std::unordered_map<std::string, Order> orderContainer;
    std::map<double, std::unordered_map<std::string, Order*>> orderLevels;

};