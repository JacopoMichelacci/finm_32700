#pragma once

#include <vector>

#ifdef __x86_64__
#include <immintrin.h>
#endif
#include <chrono>
#include <iostream>


std::vector<double> moving_average_naive(const std::vector<double>& prices, int window) {
    int n = prices.size(); 
    std::vector<double> result(n, 0.0);
    for (int i = window - 1; i < n; i++) { 
        double sum = 0.0; 
        for (int j = 0; j < window; j++){ 
            sum += prices[i-j];
        }
        result[i] = sum / window; 
    }
    return result; 
}

#ifdef __x86_64__

std::vector<double> moving_average_simd(const std::vector<double>& prices, int window) { 
    int n = prices.size();
    std::vector<double> result(n, 0.0); 

    for (int i = window - 1; i < n; i++) { 
        __m256d sum_vec = _mm256_setzero_pd();
        int j = 0; 

        for (; j <= window - 4; j += 4) {
            int base = i - j - 3;

            __m256d vals = _mm256_set_pd(
                prices[base + 3],
                prices[base + 2],
                prices[base + 1],
                prices[base]
            );

            sum_vec = _mm256_add_pd(sum_vec, vals);
        }

        double temp[4];
        _mm256_storeu_pd(temp, sum_vec); 

        double sum = temp[0] + temp[1] + temp[2] + temp[3];

        for (; j < window; j++) {
            sum += prices[i - j];
        }

        result[i] = sum / window;
    }

    return result;
}

#else

std::vector<double> moving_average_simd(const std::vector<double>& prices, int window) {
    return moving_average_naive(prices, window);
}

#endif

void benchmark_moving_averages(const std::vector<double>& prices, int window) { 
    auto start1 = std::chrono::high_resolution_clock::now();
    auto naive_result = moving_average_naive(prices, window);
    auto end1 = std::chrono::high_resolution_clock::now();
    auto start2 = std::chrono::high_resolution_clock::now();
    auto simd_result = moving_average_simd(prices, window);
    auto end2 = std::chrono::high_resolution_clock::now();
    auto naive_time = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count();
    auto simd_time  = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count();

    
    std::cout << "Naive: " << naive_time << " us\n";
    std::cout << "SIMD : " << simd_time << " us\n";
}