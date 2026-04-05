#include <cmath>
#include <iostream>

#include "mat_vec_col_major.hpp"
#include "mat_vec_row_major.hpp"
#include "mat_mat_naive.hpp"
#include "mat_mat_transposed.hpp"

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