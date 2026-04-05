#include <cmath>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <string>

#include "mat_vec_col_major.hpp"
#include "mat_vec_row_major.hpp"
#include "mat_mat_naive.hpp"
#include "mat_mat_transposed.hpp"
#include "mat_mat_tiled.hpp"

struct benchresult { 
    double avg; 
    double std; 
};

template <typename Func>
benchresult benchmark(Func func, int iterations = 10){
    std::vector<double> results;
    func(); 
    for(int i = 0; i < iterations; i++){
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        results.push_back(duration.count());
    }
    double sum = std::accumulate(results.begin(), results.end(), 0.0);
    double avg = sum / iterations;

    double sq_sum = std::inner_product(results.begin(), results.end(), results.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / iterations - avg * avg);

    return {avg, stdev};
}

static bool compareArray(const double* actual, const double* expected, int n) {
    for (int i = 0; i < n; ++i) {
        if (std::abs(actual[i] - expected[i]) > 1e-9) {
            return false; // Found a mismatch, fail the test
        }
    }
    return true; // All elements matched
}

bool test_mat_vec_col_major() { 
    const int rows = 2; 
    const int cols = 2; 
    const double matrix[rows * cols] = { 1,2,3,4};
    const double vector[cols] = {3,4};
    double result[rows] = {0,0};
    const double expected[rows] = {15, 22};
    multiply_mv_col_major(matrix, rows, cols, vector, result);
    return compareArray(result, expected, rows);
}

bool test_mat_vec_row_major() { 
    const int rows = 2; 
    const int cols = 2; 
    const double matrix[rows * cols] = { 1,2,3,4};
    const double vector[cols] = {3,4};
    double result[rows] = {0,0};
    const double expected[rows] = {11, 25};
    multiply_mv_row_major(matrix, rows, cols, vector, result);
    return compareArray(result, expected, rows);
}

bool test_mat_mat_naive() { 
    const int rowsA = 2; 
    const int colsA = 2; 
    const int rowsB = 2; 
    const int colsB = 2; 
    const double matrixA[rowsA * colsA] = { 1,2,3,4};
    const double matrixB[rowsB * colsB] = {5,6,7,8};
    double result[rowsA * colsB] = {0,0,0,0};
    const double expected[rowsA * colsB] = {19,22,43,50};
    multiply_mm_naive(matrixA, rowsA, colsA, matrixB, rowsB, colsB, result);
    return compareArray(result, expected, rowsA * colsB);
}

bool test_mat_mat_transposed() { 
    const int rowsA = 2; 
    const int colsA = 2; 
    const int rowsB = 2; 
    const int colsB = 2; 
    const double matrixA[rowsA * colsA] = { 1,2,3,4};
    const double matrixB[rowsB * colsB] = {5,7,6,8};
    double result[rowsA * colsB] = {0,0,0,0};
    const double expected[rowsA * colsB] = {19,22,43,50};
    multiply_mm_transposed_b(matrixA, rowsA, colsA, matrixB, rowsB, colsB, result);
    return compareArray(result, expected, rowsA * colsB);
}

void run_all_behcmarks(int size) {
    std::vector<double> matrixA(size * size, 1.1);
    std::vector<double> matrixB(size * size, 2.2);
    std::vector<double> vector(size, 3.3);

    //results: 
    std::vector<double> matresult(size * size, 0.0);
    std::vector<double> vecresult(size, 0.0);

    std::cout << "Benchmarking with size: " << size << "x" << size << std::endl;
    auto naive_mm = benchmark([&](){ 
        std::fill(matresult.begin(), matresult.end(), 0.0);
        multiply_mm_naive(matrixA.data(), size, size, matrixB.data(), size, size, matresult.data());
    });
    std::cout << "Naive MM: " << naive_mm.avg << " microseconds (± " << naive_mm.std << " microseconds)" << std::endl;
    auto transposed_mm = benchmark([&](){ 
        std::fill(matresult.begin(), matresult.end(), 0.0);
        multiply_mm_transposed_b(matrixA.data(), size, size, matrixB.data(), size, size, matresult.data());
    });
    std::cout << "Transposed MM: " << transposed_mm.avg << " microseconds (± " << transposed_mm.std << " microseconds)" << std::endl;
    auto col_major_mv = benchmark([&](){ 
        std::fill(vecresult.begin(), vecresult.end(), 0.0);
        multiply_mv_col_major(matrixA.data(), size, size, vector.data(), vecresult.data());
    });
    std::cout << "Column Major MV: " << col_major_mv.avg << " microseconds (± " << col_major_mv.std << " microseconds)" << std::endl;
    auto row_major_mv = benchmark([&](){ 
        std::fill(vecresult.begin(), vecresult.end(), 0.0);
        multiply_mv_row_major(matrixA.data(), size, size, vector.data(), vecresult.data());
    });
    std::cout << "Row Major MV: " << row_major_mv.avg << " microseconds (± " << row_major_mv.std << " microseconds)" << std::endl;
    auto tiled = benchmark([&](){ 
        std::fill(matresult.begin(), matresult.end(), 0.0);
        multiply_mm_tiled(matrixA.data(), size, size, matrixB.data(), size, size, matresult.data(), 64);
    });
    std::cout << "Tiled MM: " << tiled.avg << " microseconds (± " << tiled.std << " microseconds)" << std::endl;
}