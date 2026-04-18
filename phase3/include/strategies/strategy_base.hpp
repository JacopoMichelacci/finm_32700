#pragma once

#include <vector>
#include <span>
#include <string>
#include "core/market_events.hpp"



// this templated class is what we pass into the strategy for the calculation of the new signal
// all members of the struct are initialized as follows when a StrategyInputs object is created
struct StrategyInputs {
    const MarketEvent *ev1 = nullptr;
};

enum class Signal {
    SELL = -2,
    SHORT = -1,
    FLAT = 0,
    LONG = 1,
    COVER = 2,
};

struct StrategyConfig {
    bool long_active = true;
    bool short_active = true;
};


template <typename Derived>
class Strategy {
public:
    std::string name;
    long long id;
    std::string tag;

    Strategy(std::string name_, StrategyConfig bconfig_ = {}) 
        : name(std::move(name_)), 
        bconfig(std::move(bconfig_)),
        id(++id_state), 
        tag(std::move(name + "#" + std::to_string(id))) {}

    virtual ~Strategy() = default;

    // works for: Live and Backtest -- generates a signal action event
    virtual Signal on_data(const StrategyInputs& input) = 0;

    // works for backtest
    void on_bt_data(std::span<const StrategyInputs* const> inputs, std::vector<Signal>& out) {
        out.clear();
        out.reserve(inputs.size());

        for (auto *in : inputs) {
            out.push_back(on_data(*in));
        }
    }

protected:
    StrategyConfig bconfig;
    inline static long long id_state = 0;
};
