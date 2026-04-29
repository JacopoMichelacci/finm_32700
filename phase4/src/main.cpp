#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <string>
#include <random>

#include "utils/timer.hpp"

#include "Order.hpp"
#include "OrderBook.hpp"

using OrderType = Order<double, int>;

int main() {
    std::string time_measure = "nanoseconds";
    std::vector<long long> latencies;
    int ticks_list[3] = {1000, 10'000, 100'000};


    // random device
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> num_trades_dist(1, 50);
    int num_trades = 0;

    std::uniform_int_distribution<int> qty_dist(1, 10);
    int qty_of_trade = 0;

    for (auto ticks : ticks_list) {
        // create orderbook
        OrderBook <double, int> order_book;

        for (int i = 0; i < ticks; ++i) {
            // gen num or orders sent in x tick
            num_trades = num_trades_dist(gen);

            // create Order vector x tick
            std::vector<OrderType> ord_vector;
            ord_vector.clear();
            ord_vector.reserve(50);

            // start timer
            Timer timer(time_measure);
            timer.start();

            for (int i=0; i < num_trades; ++i) {
                qty_of_trade = qty_dist(gen);

                ord_vector.emplace_back(i, "AAPL", 150.0 + (i % 5), qty_of_trade, i % 2 == 0);
            }
            // Simulated tick + order match (replace with real logic)
            for (auto ord : ord_vector) {
                order_book.addOrder(ord);
            }
            // simulate match logic here

            latencies.push_back(timer.elapsed());
        }

        // std::cout << "\nOrderBook with: " << ticks;
        // order_book.printBook();
        // std::cout << "\n\n";
    }

    // Analyze latency
    auto min = *std::min_element(latencies.begin(), latencies.end());
    auto max = *std::max_element(latencies.begin(), latencies.end());
    double mean = std::accumulate(latencies.begin(), latencies.end(), 0.0) / latencies.size();

    std::cout << "Tick-to-Trade Latency (" << time_measure << "): \n";
    std::cout << "Min: " << min << " | Max: " << max << " | Mean: " << mean << '\n';
}