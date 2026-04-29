#pragma once 
#include "OrderManager.hpp"
#include "OrderBook.hpp"
#include <vector>
#include <chrono>
#include <algorithm>
template<typename PriceType, typename OrderIdType>
class MatchingEngine { 
    public: 
        using Clock = std::chrono::high_resolution_clock;
        struct Trade{
            PriceType price; 
            int quantity; 
        };

        std::vector<Trade> trades; 
        std::vector<long long> latencies; 
        void run(OrderBook<PriceType, OrderIdType>& book, OrderManager<PriceType, OrderIdType>& oms){
            while (book.hasBuys() && book.hasSells()) {
                auto start = Clock::now();
                
                // make sure that we can make a trade
                if (book.bestBid() < book.bestAsk()){
                    break;
                }

                //calculate the qty of the trade
                int qty = std::min(book.bestBuyQty(), book.bestSellQty());
                PriceType price = book.bestAsk(); 
                book.reduceBestBuy(qty);
                book.reduceBestSell(qty);

                book.removeBestBuyIfFilled();
                book.removeBestSellIfFilled();

                trades.push_back({price, qty});
                auto end = Clock::now(); 

                latencies.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end- start).count());

            }
        }
};