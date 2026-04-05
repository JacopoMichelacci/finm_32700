#include <iostream>
#include <chrono>
using namespace std;

#include "mat_mat_naive.hpp"

void multiply_mm_naive(const double* matrixA, int rowsA, int colsA, const double* matrixB, int rowsB, int colsB, double* result){

    auto start = chrono::high_resolution_clock::now();

    for(int i = 0; i < rowsA; i++){
        for(int j = 0; j < colsB; j++){
            for(int k = 0; k < rowsB; k++) { 
                result[i*colsB + j] += matrixA[i*colsA + k] * matrixB[k*colsB + j];
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end-start);

    std::cout << "mm_naive: " << duration.count() << "ms" << std::endl;
}
