#include <random>

#include "../include/stress_test.hpp"

void stressTest(OrderBook& book, int numOrders) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> priceDist(50.0, 100.0);
    std::uniform_int_distribution<int> quantityDist(1, 500);

    for (int i = 0; i < numOrders; ++i) {
        std::string id = "ORD" + std::to_string(i);
        double price = priceDist(rng);
        int quantity = quantityDist(rng);

        book.addOrder(Order(id, price, quantity, true));
    }
}