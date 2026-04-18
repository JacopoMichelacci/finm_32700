#include "MarketSnapshot.h"

void MarketSnapshot::update_bid(double price, int quantity) { 
    auto it = bids.find(price); 
    if (it == bids.end()) {
        if (quantity > 0) {
            bids[price] = std::make_unique<PriceLevel>(price, quantity);
        }
        return;
    }
    it->second->add(quantity);
    if (it->second->is_empty()) {
        bids.erase(it);
    }
}

void MarketSnapshot::update_ask(double price, int quantity) { 
    auto it = asks.find(price); 
    if (it == asks.end()) {
        if (quantity > 0) {
            asks[price] = std::make_unique<PriceLevel>(price, quantity);
        }
        return;
    }
    it->second->add(quantity);
    if (it->second->is_empty()) {
        asks.erase(it);
    }
}

PriceLevel* MarketSnapshot::get_best_bid() const {
    if (bids.empty()) {
        return nullptr;
    }
    return bids.begin()->second.get();
}

PriceLevel* MarketSnapshot::get_best_ask() const {
    if (asks.empty()) {
            return nullptr;
        }
    return asks.begin()->second.get();
}