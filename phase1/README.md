### Team members:
Jacopo Michelacci and Karsten Kropp

### Build Instruction:
 - to build and run the project: ./run.sh
 - to run the build: ./build/phase1

## Findings and Reflection: 

In attempting to complete this first part of the project our group initially started with considering the storage and basic math operations that we would need to consider to complete the linear algebra processes of matrix vector and matrix matrix multiplication. After completing 
this outlining phase of first understanding how the math needed to be completed and considering what we believed would be fast before writing a line 
of code we agreed that the transpose and row major processes of conducting the multiplication would be faster because of the use of contiguous memory and being able to access elements of rows and columns faster through this contigious memory. 

Following this we then worked on part I by working through the implementation of the 4 functions. The process of sketching out and consdiering 
out approach before coding was of course helpful as we were able to establish the behavior required to calculate the resulting vectors and matrices and needed to just implement this approach into our code. From there once we got all 4 functions working, we started to build our test suite in a seperate dedicated file. To do this there were two main types of testing that we considered, basic functionality and larger, more storage dependent tests. First to understand the behavior of our funcitons and that they were producing the correct result we hard coded matrices and vectors that allowed us to establish what our functions should be producing against its result. We ran this kind of hard coded test for each of the four functions to ensure that the funcitonality met the reqruiements. 
From there, knowing that the functions were working properly we moved onto the benchmarking aspect of understanding using chrono how long each of the functions were taking. Initially we implemented the timing aspect in the function itself but to understand the mean and std dev. of each process we then moved this time calculation to the specific benchmarking function that was used to see time taken for each process. 
This benchmarking process established 10 iterations of various sizes of matrices for each of the functions. We found that the transpose approach for matrix matrix multiplication and the row major implementation of matrix vector multiplication were fastest with the results shown below: 

Running tests...
All tests passed!
Running benchmarks...
Benchmarking with size: 64x64
Naive MM: 1056.4 microseconds (± 61.0953 microseconds)
Transposed MM: 916.5 microseconds (± 82.9099 microseconds)
Column Major MV: 10 microseconds (± 0 microseconds)
Row Major MV: 10 microseconds (± 0 microseconds)
Tiled MM: 1392 microseconds (± 118.029 microseconds)
______________________
Benchmarking with size: 256x256
Naive MM: 39845.4 microseconds (± 186.987 microseconds)
Transposed MM: 23243.6 microseconds (± 89.5089 microseconds)
Column Major MV: 154.8 microseconds (± 12.2703 microseconds)
Row Major MV: 69 microseconds (± 0 microseconds)
Tiled MM: 47674.1 microseconds (± 222.991 microseconds)
______________________
Benchmarking with size: 512x512
Naive MM: 360561 microseconds (± 858.538 microseconds)
Transposed MM: 188748 microseconds (± 409.567 microseconds)
Column Major MV: 731.4 microseconds (± 9.05759 microseconds)
Row Major MV: 273.1 microseconds (± 3.3 microseconds)
Tiled MM: 400496 microseconds (± 571.114 microseconds)
______________________

We bench marked with various sizes and the results showed that tranposed MM was faster than naive and column major MV was slower than row major MV as we expected. 

From there we then expanded the approach by including the tiling approach of matrix multiplication. This interestingly, while expected to improve performance, was slower than even naive matrix multiplication. When considering this process and trying to understand why this tiling approach did not help, we believed that the fact that newer macbooks have enough space in the cache that this increase in the number of for loops in the function, from 3 to 6, compared to naive and transposed approach led to this increase in overhead of running these for loops compared to the other approaches we used. 

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
 5. 
 6. The main performance bottlenecks
 7. 