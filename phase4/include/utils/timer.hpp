#pragma once
#include <string>
#include <chrono>
#include <utility>
#include <cstddef>

class Timer {
public:
    std::string time_measure_type;

    Timer(std::string time_measure_type_ ) 
        : start_(std::chrono::high_resolution_clock::now()), time_measure_type(std::move(time_measure_type_)) {}


    inline void start_timer() {
        start_ = std::chrono::high_resolution_clock::now();
    }

    inline long long time_elapsed() {
        end_ = std::chrono::high_resolution_clock::now();

        return time_measure_();   
    }

    template <typename F>
    long long func_elapsed(F&& f, std::size_t iter) {
        long long sum = 0;

        for (std::size_t i=0; i < iter; ++i) {
            start_ = std::chrono::high_resolution_clock::now();
            f();
            end_ = std::chrono::high_resolution_clock::now();

            sum += time_measure_();
        }

        return sum;
    }
private:
    std::chrono::high_resolution_clock::time_point start_;
    std::chrono::high_resolution_clock::time_point end_;


    inline long long time_measure_() {
        if (time_measure_type == "milliseconds") {
            return std::chrono::duration_cast<std::chrono::milliseconds>(end_ - start_).count();
        }

        if (time_measure_type == "microseconds") {
            return std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_).count();
        }

        if (time_measure_type == "nanoseconds") {
            return std::chrono::duration_cast<std::chrono::nanoseconds>(end_ - start_).count();
        }

        return -1;
    }
};