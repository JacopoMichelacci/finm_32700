#include <iostream>
#include <chrono>
using namespace std;

#include "mat_mat_naive.hpp"

void multiply_mm_naive(const double* matrixA, int rowsA, int colsA, 
                        const double* matrixB, int rowsB, int colsB, 
                        double* result,
                        chrono::nanoseconds& time_elapsed){
                            
    for(int i = 0; i < rowsA; i++){
        for(int j = 0; j < colsB; j++){
            for(int k = 0; k < rowsB; k++) { 
                result[i*colsB + j] += matrixA[i*colsA + k] * matrixB[k*colsB + j];
            }
        }
    }
}
