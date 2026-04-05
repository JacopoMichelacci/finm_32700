#include "mat_mat_tiled.hpp"
#include <algorithm>


void multiply_mm_tiled(const double* A, int rowsA, int colsA, const double* B, int rowsB, int colsB, double* C, int tileSize){
    for (int i = 0; i < rowsA; i += tileSize) {
        for (int j = 0; j < colsB; j += tileSize) {
            for (int k = 0; k < colsA; k += tileSize) {
                // Implementation for tiled matrix multiplication
                //inner loops for tiling: 

                for (int ii = i; ii < std::min(i + tileSize, rowsA); ++ii) { 
                    for (int kk = k; kk < std::min(k + tileSize, colsA); ++kk) { // Swap kk and jj
                        double valA = A[ii * colsA + kk];
                        for (int jj = j; jj < std::min(j + tileSize, colsB); ++jj) {
                            C[ii * colsB + jj] += valA * B[kk * colsB + jj];
                        }
                    }
                }
            }
        }
    }
}