#include <iostream>
using namespace std;

#include "mat_vec_row_major.hpp"

// row major order means the rows are stored contiguously
void multiply_mv_row_major(const double* matrix, int rows, int cols, const double* vector, double* result) {
    // loop though row
    for (int i = 0; i < rows; ++i) {
        // loop through col 
        for (int j = 0; j < cols; ++j) {
            result[i] += (matrix[cols * i + j]) * (vector[j]);
        }
    }
    
}




