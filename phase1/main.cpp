#include <iostream>
#include "test.hpp"
using namespace std; 


int main() {
    cout << "Running tests..." << endl;
    if (test_mat_vec_col_major()) {
        cout << "Matrix vector column major test passed" << endl; 
    } else {
        cout << "Matrix vector column major test failed" << endl;
    }

    if (test_mat_vec_row_major()) {
        cout << "Matrix vector row major test passed" << endl; 
    } else {
        cout << "Matrix vector row major test failed" << endl;
    }

    if (test_mat_mat_naive()) {
        cout << "Matrix matrix naive test passed" << endl; 
    } else {
        cout << "Matrix matrix naive test failed" << endl;
    }

    if (test_mat_mat_transposed()) {
        cout << "Matrix matrix transposed test passed" << endl; 
    } else {
        cout << "Matrix matrix transposed test failed" << endl;
    }
    return 0;
}