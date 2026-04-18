#pragma once

#include <vector>
#include <optional>

#include "core/market_events.hpp"

// this templated class is what we pass into the indicator for the calculation of its new value ---
template <typename T1 = void, typename T2 = void, typename T3 = void>
struct IndicatorInputs {
    const MarketEvent *ev1 = nullptr;
    const MarketEvent *ev2 = nullptr;
    const MarketEvent *ev3 = nullptr;

    const T1 *v1 = nullptr;
    const T2 *v2 = nullptr;
    const T3 *v3 = nullptr;

    const double *d1 = nullptr;
    const int *i1 = nullptr;
    const bool *b1 = nullptr;
};


template <typename TOut, typename T1 = void, typename T2 = void, typename T3 = void>
class Indicator {
public:
    std::vector<std::optional<TOut>> buffer;

    Indicator(std::size_t buffer_len_ = 0) {
        buffer.reserve(buffer_len_);
    }
    virtual ~Indicator() = default;

    // returns new indicator value
    std::optional<TOut> update(const IndicatorInputs<T1, T2, T3>& input) {
        return compute(input);
    }

    // computes new ind value and updates buffer
    void update_buffer(const IndicatorInputs<T1, T2, T3>& input) {
        buffer.emplace_back(compute(input));
    }

protected:
    virtual std::optional<TOut> compute(const IndicatorInputs<T1, T2, T3>& input) = 0;
};