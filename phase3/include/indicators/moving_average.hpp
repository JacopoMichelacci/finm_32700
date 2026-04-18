#pragma once

#include <stdexcept>
#include <vector>
#include <optional>

#include "indicators/indicator_base.hpp"


template <typename T>
class SMA : public Indicator<T> {
public:
    std::size_t len;
    std::vector<T> history;
    std::size_t idx = 0;
    T sum{};

    explicit SMA(std::size_t len_) : len(len_) {
        if (len_ <= 0) {throw std::invalid_argument("SMA len must be > 0");}
        history.reserve(len);
    }


    std::optional<T> compute(const IndicatorInputs input{}) override {
        if (history.size() < len) {
            history.push_back(val);
            sum += val;
        } else {
            sum -= history[idx];
            history[idx] = val;
            sum += val;
        }

        idx = (++idx) % len;

        if (history.size() != len) {return std::nullopt;}
        return sum / static_cast<T>(history.size());
    }
};