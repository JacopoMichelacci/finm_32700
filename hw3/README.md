
### Part 2: ###
Questions:
    1. The program crashes at runtime because the object was not freed correctly from the heap.
    2. The memory on the heap is not deleted and causes a memory leak, on modern compilers when the process ends the heap is automatically cleaned.
    3. The program crashed due to the double delete, a trace trap was printed on the terminal because of it "[1]    83226 trace trap  ./main".

### Part 3: ###

Why do we delete the copy constructor?

Why is move semantics allowed?

What happens if you don't define a destructor?

### Part 5: ###

What are the 3 biggest risks of manual memory management?

The three largest risks of manual memory management would be memory leaks where we never delete the pointer, losing it to memory while the OS still thinks that it is in use which we cannot use then after a leak. Another large risk is dangling pointers or when we call delete on a pointer and try to still use it, this pointer could point to a object that is completly different which could corrupt our data over time. The last major risk of manual memory management is if we were to try and call delete twice on the same memory address. This would cause the allocator's process to get corrupted which would then potentially cause the entire program to crash

What real-world problems could occur in HFT systems due to memory leaks or fragmentation?

Considering memory leaks in a HFT system we can consider that if memory is being leaked on a system that handles millions of ticks of data a day and leaks some number of bytes per tick, even if small, this would cause the RAM to not be allocated properly. The OS would essentially start to run our of memory and in the extreme case of memeory leakage could then cause the OS to try and swap memory to the hard drive which would drastically slow things down. 

For fragementation, real-world problems that could occur in HFT systems include the o

How does RAII reduce the risk of bugs?

What tradeoffs exist between manual and automatic memory management in performance-critical code?