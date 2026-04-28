#pragma once
#include <map>
#include <string>
#include <algorithm>
#include <iostream>

template<typename PriceType, typename OrderIdType>
struct Order {
    OrderIdType id;
    std::string symbol;
    PriceType price;
    int quantity;
    bool is_buy;
    OrderStatus status;
};

template<typename PriceType, typename OrderIdType>
class OrderBook {
public:
    using OrderType = Order<PriceType, OrderIdType>;

private:
    // buy: highest price first
    std::multimap<PriceType, OrderType, std::greater<PriceType>> buyBook;

    // sell: lowest price first
    std::multimap<PriceType, OrderType> sellBook;

public:

    // -------------------------
    // ADD ORDER
    // -------------------------
    void addOrder(const OrderType& order) {
        if (order.is_buy)
            buyBook.insert({order.price, order});
        else
            sellBook.insert({order.price, order});
    }

    // -------------------------
    // TOP OF BOOK CHECKS
    // -------------------------
    bool hasBuys() const { return !buyBook.empty(); }
    bool hasSells() const { return !sellBook.empty(); }

    PriceType bestBid() const {
        return buyBook.begin()->first;
    }

    PriceType bestAsk() const {
        return sellBook.begin()->first;
    }

    // quantity at top level order
    int bestBuyQty() const {
        return buyBook.begin()->second.quantity;
    }

    int bestSellQty() const {
        return sellBook.begin()->second.quantity;
    }

    // -------------------------
    // MATCHING SUPPORT (mutation helpers)
    // -------------------------

    void reduceBestBuy(int qty) {
        auto it = buyBook.begin();
        it->second.quantity -= qty;
    }

    void reduceBestSell(int qty) {
        auto it = sellBook.begin();
        it->second.quantity -= qty;
    }

    void removeBestBuyIfFilled() {
        auto it = buyBook.begin();
        if (it->second.quantity <= 0)
            buyBook.erase(it);
    }

    void removeBestSellIfFilled() {
        auto it = sellBook.begin();
        if (it->second.quantity <= 0)
            sellBook.erase(it);
    }

    // -------------------------
    // DEBUG
    // -------------------------
    void printBook() const {
        std::cout << "\nBUY BOOK\n";
        for (auto& [price, order] : buyBook)
            std::cout << price << " x " << order.quantity << "\n";

        std::cout << "\nSELL BOOK\n";
        for (auto& [price, order] : sellBook)
            std::cout << price << " x " << order.quantity << "\n";
    }
};