#include <iostream>
#include <chrono>
using namespace std;

#include "mat_mat_transposed.hpp"

void multiply_mm_transposed_b(const double* matrixA, int rowsA, int colsA, const double* matrixB_transposed, int rowsB, int colsB, double* result) {
    // loop rows A
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < rowsB; ++j) {
            for  (int k = 0; k < colsA; ++k) {
                result[i * rowsB + j] += matrixA[i * colsA + k] * matrixB_transposed[j * colsB + k];
            }
        }
    }
}