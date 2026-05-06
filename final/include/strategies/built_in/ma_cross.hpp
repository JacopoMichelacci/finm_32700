#pragma once

#include <vector>

#include "strategies/strategy_base.hpp"


struct MACConfig {
    int fast_len = 10;
    int slow_len = 30;
};


class MAC : public Strategy {
public:
    MAC(std::string name_ , StrategyConfig bconfig_, MACConfig config_) 
        : Strategy(std::move(name_), std::move(bconfig_)), config(std::move(config_)) {}


    Signal on_data(const MarketEvent& ev) override;

protected:
    MACConfig config;
};