#include <iostream>
#include <chrono>
using namespace std;

#include "mat_vec_col_major.hpp"


void multiply_mv_col_major(const double* matrix, int rows, int cols, const double* vector, double* result){

    auto start = chrono::high_resolution_clock::now();
    
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            result[i] += matrix[rows*j + i] * vector[j];
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end-start);

    std::cout << "mv_col-maj: " << duration.count() << "ms" << std::endl;
}


