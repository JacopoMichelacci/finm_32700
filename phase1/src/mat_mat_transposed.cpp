#include <chrono>

void multiply_mm_transposed_b(const double* matrixA, int rowsA, int colsA, const double* matrixB_transposed, int rowsB, int colsB, double* result) {

    // loop rows A
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < rowsB; ++j) {
            for  (int k = 0; k < colsA; ++k) {
                result[i + colsB * j] += matrixA[i + k * colsA] * matrixB_transposed[j + k * colsB];
            }
        }
    }

}