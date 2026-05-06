#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <unordered_map>
#include <queue>

#include "robinhood_hash.hpp"
#include "heap_queue.hpp"
#include "timeseries.hpp"
#include "orderbook.hpp"

using namespace std;

//random price generator: 

vector<double> generate_prices(int n) {
    vector<double> prices(n);
    for (int i = 0; i < n; i++) {
        prices[i] = 100.0 + (rand() % 1000) / 10.0;
    }
    return prices;
}

//testing robinhood hashing: 

void bench_hash() { 
    cout << "testing hash" << endl; 
    const int N = 100000; 
    RobinHoodHash rh(N * 2);
    unordered_map<string, double> umap; 
    vector<string> keys; 
    for (int i = 0; i < N; i++) { 
        keys.push_back("SYM" + to_string(i)); 
    }
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++){ 
        umap[keys[i]] = i * 1.0;
    }

    auto mid = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++){ 
        rh.insert(keys[i], i * 1.0);
    }
    auto end = chrono::high_resolution_clock::now();

    cout << "Robinhood benchmark result: " << chrono::duration_cast<chrono::milliseconds>(end - mid).count() << "ms" << endl;
    cout << "umap benchmark result: " << chrono::duration_cast<chrono::milliseconds>(mid - start).count() << "ms" << endl;
}

void heap_bench() { 
    cout << "benchmarking heap" << endl; 
    const int N = 100000; 
    HeapQueue myh; 
    priority_queue<HeapOrder> stdHeap; 
    vector<HeapOrder> orders;
    for (int i = 0; i < N; i ++){
        orders.push_back({(double)(rand() % 1000), i});
    }
    
    auto start = chrono::high_resolution_clock::now();
    for (const auto& order : orders) {
        stdHeap.push(order);
    }
    auto mid = chrono::high_resolution_clock::now();
    for (const auto& order : orders) {
        myh.push(order);
    }
    auto end = chrono::high_resolution_clock::now();
    
    cout << "std::priority_queue push result: " << chrono::duration_cast<chrono::milliseconds>(mid - start).count() << "ms" << endl;
    cout << "HeapQueue push result: " << chrono::duration_cast<chrono::milliseconds>(end - mid).count() << "ms" << endl;
}

void timeseries_bench() { 
    cout << "benchmarking timeseries: " << endl; 
    auto prices = generate_prices(100000);
    int window = 50; 
    benchmark_moving_averages(prices, window);
}

void test_orderbook() { 
    cout << "benchmarking order book" << endl; 
    OrderBook ob; 
    ob.add_order(1, 100.5, 2, 'B');
    ob.add_order(2, 101.0, 5, 'B');
    ob.add_order(3, 102.0, 7, 'S');
    ob.add_order(4, 103.0, 8, 'S');
    auto best_bid = ob.get_best_bid();
    auto best_ask = ob.get_best_ask();
    if (best_bid) {
        cout << "Best bid: " << best_bid->price << endl;
    }
    if (best_ask){
        cout << "Best ask: " << best_ask->price << endl;
    
    }
    ob.modify_order(1, 20); 
    ob.delete_order(2); 
    auto orders = ob.get_order_at_price(100.5, 'B');
    cout << "Orders at price 100.5: " << orders.size() << endl;
}

void orderbook_bench() { 
    cout << "Benchmarking orderbook performance" << endl; 
    OrderBook ob;
    const int N = 100000;
    auto start_add = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        double price = 100.0 + (rand() % 100) / 10.0;
        char side = (i % 2 == 0) ? 'B' : 'S';
        ob.add_order(i, price, 10, side);
    }
    auto end_add = chrono::high_resolution_clock::now();
    auto start_mod = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        ob.modify_order(i, 20);
    }
    auto end_mod = chrono::high_resolution_clock::now();
    

    auto start_best = chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; i++) {
        ob.get_best_bid();
        ob.get_best_ask();
    }
    auto end_best = chrono::high_resolution_clock::now();
    
    auto start_del = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        ob.delete_order(i);
    }
    auto end_del = chrono::high_resolution_clock::now();
    
    cout << "Add " << N << " orders: " << chrono::duration_cast<chrono::milliseconds>(end_add - start_add).count() << "ms\n";
    cout << "Modify " << N << " orders: " << chrono::duration_cast<chrono::milliseconds>(end_mod - start_mod).count() << "ms\n";
    cout << "Query Best Bid/Ask 10,000 times: " << chrono::duration_cast<chrono::microseconds>(end_best - start_best).count() << "us\n";
    cout << "Delete " << N << " orders: " << chrono::duration_cast<chrono::milliseconds>(end_del - start_del).count() << "ms\n";
}

int main() {
    bench_hash(); 
    heap_bench(); 
    timeseries_bench(); 
    test_orderbook(); 
    orderbook_bench(); 

    return 0;
}