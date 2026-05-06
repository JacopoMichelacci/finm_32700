#pragma once

#include <cstddef>
#include <vector>
#include <span>
#include <optional>
#include <utility>
#include <type_traits>
#include <string_view>

#include "core/market_events.hpp"

// this templated class is what we pass into the indicator for the calculation of its new value ---
struct IndicatorInputs {
    const MarketEvent* ev1 = nullptr;
    const MarketEvent* ev2 = nullptr;
    const MarketEvent* ev3 = nullptr;
    const MarketEvent* ev4 = nullptr;
    const MarketEvent* ev5 = nullptr;

    std::optional<double> d1;
    std::optional<double> d2;
    std::optional<double> d3;

    std::optional<int> i1;
    std::optional<int> i2;
    std::optional<int> i3;

    std::string_view str1;
    std::string_view str2;
    std::string_view str3;
};


template <typename Derived, typename Tout>
class Indicator {
public:

    // returns new indicator value
    std::optional<Tout> update(const IndicatorInputs& input) {
        return derived().compute(input);
    }

    // computes new ind value and updates buffer
    void update_buffer(const IndicatorInputs& input) {
        buffer.emplace_back(derived().compute(input));
    }

    // handle buffer
    const std::optional<Tout>& operator[](std::size_t i) const { return buffer[i]; }                // index
    std::size_t size() const { return buffer.size(); }                                              // get size
    std::span<const std::optional<Tout>> view_buffer() const { return buffer; }                     // view buffer



protected:
    // storage of past indicator values in time idx order  ( 0 -> first; .size() -1 -> last )
    std::vector<std::optional<Tout>> buffer;

    // constructor and destructor
    Indicator(std::size_t buffer_len_ = 64) {
        static_assert(
            std::is_same_v<decltype(std::declval<Derived&>().compute(std::declval<const IndicatorInputs&>())), std::optional<Tout>>,
            "Derived must implement: std::optional<Tout> compute(const IndicatorInputs&)"
        );

        buffer.reserve(buffer_len_);
    }
    ~Indicator() = default;

private:
    // CRTP
    Derived& derived() {
        return static_cast<Derived&>(*this);
    }
    const Derived& derived() const {
        return static_cast<const Derived&>(*this);
    }
};