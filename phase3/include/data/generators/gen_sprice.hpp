#pragma once

#include <vector>

#include "core/market_events.hpp"

std::vector<SPriceEvent> gen_sprice_gbm(
    int n_instruments,
    int nticks,
    double S0,
    double drift,
    double vol,
    int ts_step_ms,
    long long ts0 = -1
);