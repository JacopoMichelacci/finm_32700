#pragma once 

#include <unordered_map>
#include <map>
#include <vector>
#include <iostream>
#include <optional>
#include <algorithm>

struct Order { 
    int id; 
    double price; 
    int quantity; 
    char side; 
};

class OrderBook {
    private:
        std::unordered_map<int, Order> orders_by_id; 

        std::map<double, std::vector<int>> bids_by_price; 
        std::map<double, std::vector<int>> asks_by_price;
    public: 
        void add_order(int id, double price, int quantity, char side){ 
            Order order{id, price, quantity, side};
            orders_by_id[id] = order;
            if (side == 'B'){
                bids_by_price[price].push_back(id);
            } else { 
                asks_by_price[price].push_back(id);
            }
        }

        void modify_order(int id, int new_quant){
            auto it = orders_by_id.find(id);
            if (it == orders_by_id.end()){
                return;
            }
            it->second.quantity = new_quant;
        }

        void delete_order(int id){
            auto it = orders_by_id.find(id);
            if (it == orders_by_id.end()){
                return;
            }
            Order order = it->second;
            auto& book = (order.side == 'B') ? bids_by_price : asks_by_price;
            auto price_it = book.find(order.price);
            if (price_it != book.end()){
                auto& vec = price_it->second;
                vec.erase(std::remove(vec.begin(), vec.end(), id), vec.end());
                if (vec.empty()){
                    book.erase(price_it);
                }
            
            }
            orders_by_id.erase(it);
        }
        std::vector<Order> get_order_at_price(double price, char side){
            std::vector<Order> result; 
            auto& book = (side == 'B') ? bids_by_price : asks_by_price;
            auto it = book.find(price); 
            if (it == book.end()){
                return result;
            }
            for (int id : it->second){
                result.push_back(orders_by_id[id]);
            }
            return result; 
        }

        std::optional<Order> get_best_bid(){
            if (bids_by_price.empty()){
                return std::nullopt;
            }
            auto it = bids_by_price.rbegin();
            if (it->second.empty()){
                return std::nullopt;
            }
            int id = it->second[0];
            return orders_by_id[id];
        }

        std::optional<Order> get_best_ask(){
            if (asks_by_price.empty()){
                return std::nullopt;
            }
            auto it = asks_by_price.begin();
            if (it->second.empty()){
                return std::nullopt;
            }
            int id = it->second[0];
            return orders_by_id[id];
        }
};