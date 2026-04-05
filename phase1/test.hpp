static bool compareArray(const double* actual, const double* expected, int n);
bool test_mat_vec_col_major();

bool test_mat_vec_row_major();
bool test_mat_mat_naive();
bool test_mat_mat_transposed();
void run_all_behcmarks(int size);