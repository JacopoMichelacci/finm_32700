Questions:
    1. The program crashes at runtime because the object was not freed correctly from the heap.
    2. The memory on the heap is not deleted and causes a memory leak, on modern compilers when the process ends the heap is automatically cleaned.
    3. The program crashed due to the double delete, a trace trap was printed on the terminal because of it "[1]    83226 trace trap  ./main".