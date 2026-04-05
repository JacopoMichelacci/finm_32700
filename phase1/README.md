### Team members:
Jacopo Michelacci and Karsten Kropp

### Build Instruction:
 - to build and run the project: ./run.sh
 - to run the build: ./build/phase1


### Part 3.
 1. pointers store an address while references are aliases to variables in the program. References are fixed (they cannot be changed) and
    cannot be initialized null, while pointers can be reassigned and can be initialized as nullptr
 2. In the row-major matrix-vector code, matrix[i*cols + j] with j in the inner loop reads each row contiguously, so cache locality is good.
    In naive matrix-matrix, A[i*colsA + k] is contiguous, but B[k*colsB + j] walks down a column of B with a stride, so cache use is worse.
    In transposed-B, B_transposed[j*rowsB + k] is also contiguous in the inner loop, so both operands are read sequentially. That matched the benchmark/profiler: multiply_mm_naive was about 1.88 s (56.3%), while multiply_mm_transposed_b was about 1.26 s (37.8%), showing better locality and lower runtime.
 3. CPU caches are small, fast memories between the CPU and RAM: L1 is the smallest and fastest, L2 is larger and a bit slower, and L3 is the largest and shared across 
    cores but slower than L1/L2.
    Spatial locality means nearby memory locations are likely used together; temporal locality means recently used data is likely used again soon.
 4.