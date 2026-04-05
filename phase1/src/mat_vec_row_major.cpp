#include <iostream>
#include <chrono>
using namespace std;

#include "mat_vec_row_major.hpp"

// row major order means the rows are stored contiguously
void multiply_mv_row_major(const double* matrix, int rows, int cols, const double* vector, double* result) {

    auto start = chrono::high_resolution_clock::now();

    // loop though row
    for (int i = 0; i < rows; ++i) {
        // loop through col 
        for (int j = 0; j < cols; ++j) {
            result[i] += (matrix[cols * i + j]) * (vector[j]);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end-start);

    std::cout << "mv_row-maj: " << duration.count() << "ns" << std::endl;
    
}




