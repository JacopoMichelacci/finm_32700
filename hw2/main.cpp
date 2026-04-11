#include <chrono>
#include <vector>
#include <random>
#include <iostream>
#include <unordered_map>

struct alignas(64) MarketData {
    int instrument_id;
    double price;
    std::chrono::high_resolution_clock::time_point timestamp;
};

//////////////////////////////////////////////////////////////////////////////////////////////////


class MarketDataFeed {
public:
    MarketDataFeed(std::vector<MarketData>& ref) : data(ref) {}

    void generateData(int num_ticks) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> price_dist(100.0, 200.0);

        data.reserve(num_ticks);
        for (int i = 0; i < num_ticks; ++i) {
            MarketData md;
            md.instrument_id = i % 10;
            md.price = price_dist(gen);
            md.timestamp = std::chrono::high_resolution_clock::now();
            data.push_back(md);
        }
    }

private:
    std::vector<MarketData>& data;
};



//////////////////////////////////////////////////////////////////////////////////////////////////

struct alignas(64) Order {
    int instrument_id;
    double price;
    bool is_buy;
    std::chrono::high_resolution_clock::time_point timestamp;
};


//////////////////////////////////////////////////////////////////////////////////////////////////


class TradeEngine {
public:
    TradeEngine(const std::vector<MarketData>& feed)
        : market_data(feed) {}

    void process() {
        int signal1_count = 0, signal2_count = 0, signal3_count = 0;
        for (const auto& tick : market_data) {
            // Update history
            updateHistory(tick);

            // Apply signals
            bool buy = false, sell = false;

            if (signal1(tick)){
                buy = true; 
                signal1_count++;
            } 
            if (signal2(tick)) { 
                if (tick.price < getAvg(tick.instrument_id)) {
                    buy = true; 
                } else {
                    sell = true;
                }
                signal2_count++;
            } 
            if (signal3(tick)){
                buy = true; 
                signal3_count++;
            } 

            if (buy || sell) {
                auto now = std::chrono::high_resolution_clock::now();
                Order o { tick.instrument_id, tick.price + (buy ? 0.01 : -0.01), buy, now };
                orders.push_back(o);

                auto latency = std::chrono::duration_cast<std::chrono::nanoseconds>(now - tick.timestamp).count();
                latencies.push_back(latency);
            }
        }
        std::cout << "signal 1 triggered: " << signal1_count << " times\n";
        std::cout << "signal 2 triggered: " << signal2_count << " times\n";
        std::cout << "signal 3 triggered: " << signal3_count << " times\n";
    }

    void reportStats() {
        long long sum = 0, max_latency = 0;
        for (auto l : latencies) {
            sum += l;
            if (l > max_latency) max_latency = l;
        }

        std::cout << "\n--- Performance Report --- \n";
        std::cout << "Total Market Ticks Processed: " << market_data.size() << "\n";
        std::cout << "Total Orders Placed: " << orders.size() << "\n";
        std::cout << "Average Tick-to-Trade Latency (ns): " << (latencies.empty() ? 0 : sum / latencies.size()) << "\n";
        std::cout << "Maximum Tick-to-Trade Latency (ns): " << max_latency << "\n";
    }

private:
    const std::vector<MarketData>& market_data;
    std::vector<Order> orders;
    std::vector<long long> latencies;
    std::unordered_map<int, std::vector<double>> price_history;

    void updateHistory(const MarketData& tick) {
        auto& hist = price_history[tick.instrument_id];
        hist.push_back(tick.price);
        if (hist.size() > 10) hist.erase(hist.begin());
    }

    double getAvg(int id) {
        auto& hist = price_history[id];
        double sum = 0;
        for (double p : hist) sum += p;
        return hist.empty() ? 0 : sum / hist.size();
    }

    // Signal 1: Price thresholds
    bool signal1(const MarketData& tick) {
        return tick.price < 105.0 || tick.price > 195.0;
    }

    // Signal 2: Deviation from average
    bool signal2(const MarketData& tick) {
        if (price_history[tick.instrument_id].size() < 5) return false;
        double avg = getAvg(tick.instrument_id);
        return tick.price < avg * 0.70 || tick.price > avg * 1.30;
    }

    // Signal 3: Simple momentum
    bool signal3(const MarketData& tick) {
        auto& hist = price_history[tick.instrument_id];
        if (hist.size() < 3) return false;
        double diff1 = hist[hist.size() - 2] - hist[hist.size() - 3];
        double diff2 = hist[hist.size() - 1] - hist[hist.size() - 2];
        return diff1 > 0 && diff2 > 0;
    }
};


//////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    {std::vector<MarketData> feed;
    MarketDataFeed generator(feed);

    auto start = std::chrono::high_resolution_clock::now();
    generator.generateData(100000);

    TradeEngine engine(feed);
    engine.process();

    auto end = std::chrono::high_resolution_clock::now();
    auto runtime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    engine.reportStats();
    std::cout << "\nTotal Runtime (ms): " << runtime << std::endl;
    }
    {
    std::cout << "\n-------------------\nRunning with 10x more data\n" << std::endl;
    std::vector<MarketData> feed;
    MarketDataFeed generator(feed);

    auto start = std::chrono::high_resolution_clock::now();
    generator.generateData(1000000);

    TradeEngine engine(feed);
    engine.process();

    auto end = std::chrono::high_resolution_clock::now();
    auto runtime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    engine.reportStats();
    std::cout << "\nTotal Runtime (ms): " << runtime << std::endl;
    }
    return 0;
}



//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////


