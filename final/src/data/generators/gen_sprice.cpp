#include <chrono>
#include <cmath>
#include <random>
#include <vector>

#include "data/generators/gen_sprice.hpp"
#include "core/market_events.hpp"

// Assumptions:
// 1. ts_step_ms is in milliseconds.
// 2. drift and vol are annualized.
// 3. If ts0 == -1, we initialize the first timestamp to current Unix epoch time in ms.
// 4. nticks is the total number of ticks across all instruments.
// 5. Instruments are interleaved: tick i is assigned to instrument (i % n_instruments).

std::vector<SPriceEvent> gen_sprice_gbm(
    int n_instruments,
    int nticks,
    double S0,
    double drift,
    double vol,
    int ts_step_ms,
    long long ts0
) {
    std::vector<SPriceEvent> out;
    out.reserve(nticks);

    // basic safety check
    if (n_instruments <= 0 || nticks <= 0) {
        return out;
    }

    // if no starting timestamp is provided, use current wall-clock time in ms
    if (ts0 == -1) {
        ts0 = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();
    }

    // convert one event step from milliseconds into "fraction of trading year"
    double ms_per_trading_year = 252.0 * 6.5 * 60.0 * 60.0 * 1000.0;
    double dt = static_cast<double>(ts_step_ms) / ms_per_trading_year;

    // RNG for the GBM shock term Z ~ N(0,1)
    std::mt19937 rng(std::random_device{}());
    std::normal_distribution<double> normal(0.0, 1.0);

    // current simulated price for each instrument
    std::vector<double> sprices(n_instruments, S0);

    for (int i = 0; i < nticks; ++i) {
        int instrument_id = i % n_instruments;
        long long ts = ts0 + static_cast<long long>(i) * ts_step_ms;

        // emit current price as an event
        double s = sprices[instrument_id];
        out.emplace_back(ts, s, instrument_id);

        // GBM update:
        // S_{t+dt} = S_t * exp((mu - 0.5*sigma^2)*dt + sigma*sqrt(dt)*Z)
        double z = normal(rng);
        s *= std::exp((drift - 0.5 * vol * vol) * dt + vol * std::sqrt(dt) * z);

        // store updated price for this instrument
        sprices[instrument_id] = s;
    }

    return out;
}