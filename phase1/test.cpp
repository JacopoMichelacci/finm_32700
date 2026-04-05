#include <cmath>
#include <iostream>

#include "mat_vec_col_major.hpp"
#include "mat_vec_row_major.hpp"
#include "mat_mat_naive.hpp"

static bool compareArray(const double* actual, const double* expected, int n, double tol = 1e-9) {
    for (int i = 0; i < n; ++i) {
        if (std::fabs(actual[i] - expected[i]) > tol) {
            return false;
        }
    }
    return true;
}

bool test_mat_vec_col_major() { 

}

