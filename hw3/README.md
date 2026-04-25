
### Part 2: ###
Questions:
    1. The program crashes at runtime because the object was not freed correctly from the heap.
    2. The memory on the heap is not deleted and causes a memory leak, on modern compilers when the process ends the heap is automatically cleaned.
    3. The program crashed due to the double delete, a trace trap was printed on the terminal because of it "[1]    83226 trace trap  ./main".

### Part 3: ###

Why do we delete the copy constructor?

We delete the copy constructor to ensure that we do not have shallow copies of objects on the heap that are not being used. 

Why is move semantics allowed?

Move semantics allow us to transfer ownership of an object instead of copying which helps avoid double delete and unnecessary allocations

What happens if you don't define a destructor?

If our class allocated memory on the heap and never deallocates that memory or defines a destructor then this will cause a memory leak as this memory will become orphaned and we will not be able to recover it 


### Part 5: ###

What are the 3 biggest risks of manual memory management?

The three largest risks of manual memory management would be memory leaks where we never delete the pointer, losing it to memory while the OS still thinks that it is in use which we cannot use then after a leak. Another large risk is dangling pointers or when we call delete on a pointer and try to still use it, this pointer could point to a object that is completly different which could corrupt our data over time. The last major risk of manual memory management is if we were to try and call delete twice on the same memory address. This would cause the allocator's process to get corrupted which would then potentially cause the entire program to crash

What real-world problems could occur in HFT systems due to memory leaks or fragmentation?

Considering memory leaks in a HFT system we can consider that if memory is being leaked on a system that handles millions of ticks of data a day and leaks some number of bytes per tick, even if small, this would cause the RAM to not be allocated properly. The OS would essentially start to run our of memory and in the extreme case of memeory leakage could then cause the OS to try and swap memory to the hard drive which would drastically slow things down. 

For fragementation, real-world problems that could occur in HFT systems include the possibility of available memory being split into small noncontiguous blocks. This would mean that there is potentially enough space but due to it not being contiguous causees issues in latency and storage.  

How does RAII reduce the risk of bugs?

RAII ensures that we do not double delete, have memory leaks or double frees all of which ensure that when memory goes out of scoped it is freed up automatically 

What tradeoffs exist between manual and automatic memory management in performance-critical code?

Manual memory allocation allows for full control and more possiblity to optimize for latency while drawbacks also exist like being error-prone and more difficult to maintain. 

Automatic memory management in performance critical code is generally seen as safer with fewer bugs. Some drawbacks include slight overhead and a lack of control compared to manual allocation