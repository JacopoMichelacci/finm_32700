#pragma once 

#include <map> 
#include <iostream>
#include <memory> 
#include "price_level.h"

class MarketSnapshot { 
public: 
    void update_bid(double price, int quantity); 
    void update_ask(double price, int quantity);
    PriceLevel* get_best_bid() const;
    PriceLevel* get_best_ask() const;
private: 
    std::map<double, std::unique_ptr<PriceLevel>> bids; // sorted descending
    std::map<double, std::unique_ptr<PriceLevel>> asks; // sorted ascending
    void cleanup_bid(double price); 
    void cleanup_ask(double price);
};