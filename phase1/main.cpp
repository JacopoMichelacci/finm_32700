#include <iostream>
#include "test.hpp"
using namespace std; 


int main() {
    bool all_tests_passed = true;
    cout << "Running tests..." << endl;
    if (test_mat_vec_col_major() && test_mat_vec_row_major() && test_mat_mat_naive() && test_mat_mat_transposed()) {
        cout << "All tests passed!" << endl;
    } else {
        cout << "Some tests failed." << endl;
        all_tests_passed = false;
    }
    if (all_tests_passed) {
        cout << "Running benchmarks..." << endl;
        std::vector<int> sizes = {64, 256, 512};
        for (int size: sizes) {
            run_all_behcmarks(size);
            cout << "______________________" << endl;
        }
    
    } else{
        cout << "Benchmarks skipped due to failed tests." << endl;
    }
    return 0;
}

    