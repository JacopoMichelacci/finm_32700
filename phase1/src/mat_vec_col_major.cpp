#include <iostream> 
#include "mat_vec_col_major.hpp"
using namespace std; 



void multiply_mv_col_major(const double* matrix, int rows, int cols, const double* vector, double* result){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            result[i] += matrix[rows*j + i] * vector[j];
        }
    }
}


