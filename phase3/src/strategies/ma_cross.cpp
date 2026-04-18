#include <string>
#include <utility>

#include "core/market_events.hpp"
#include "strategies/ma_cross.hpp"

// indicators
#include "indicators/moving_average.hpp"

Signal MAC::on_data(const MarketEvent& ev) {
    
    SMA<double> sma_fast(config.fast_len);
    SMA<double> sma_slow(config.slow_len);

    if (sma_fast > )

    
}