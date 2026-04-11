# HW2 - Simplified HFT Engine

## Files Included
- `main.cpp`: complete C++ source code
- Console output: included below
- Short write-up: included below

## Console Output
```text
signal 1 triggered: 9990 times
signal 2 triggered: 7786 times
signal 3 triggered: 16711 times

--- Performance Report --- 
Total Market Ticks Processed: 100000
Total Orders Placed: 26853
Average Tick-to-Trade Latency (ns): 37384694
Maximum Tick-to-Trade Latency (ns): 58041375

Total Runtime (ms): 70

-------------------
Running with 10x more data

signal 1 triggered: 99875 times
signal 2 triggered: 78833 times
signal 3 triggered: 167424 times

--- Performance Report --- 
Total Market Ticks Processed: 1000000
Total Orders Placed: 269505
Average Tick-to-Trade Latency (ns): 317488154
Maximum Tick-to-Trade Latency (ns): 528021791

Total Runtime (ms): 637
```

## Short Write-Up
Signal 3 triggered the most orders. In the 100,000-tick run it triggered 16,711 times, more than signal 1 (9,990) and signal 2 (7,786), and in the 1,000,000-tick run it remained the most active with 167,424 triggers. Based on these results, the simple momentum rule was the dominant trading signal in this implementation.

A few optimizations are still possible. Since instrument IDs are fixed from 0 to 9, `std::unordered_map` could be replaced with a fixed-size array or vector, which would reduce lookup overhead. The average price could also be maintained incrementally with a running sum instead of recomputing it each time in `getAvg()`, and `orders` / `latencies` could be reserved in advance to reduce reallocations.

With 10x more data, the code behavior is close to linear: total runtime rises from 70 ms to 637 ms and total orders rise from 26,853 to 269,505. The increase in Average Tick-to-Trade Latency should not be interpreted as the trading logic itself becoming dramatically slower. In this program, each tick timestamp is assigned during data generation, but all ticks are processed only after the full batch has been generated. That means the reported latency includes time spent waiting in the generated vector before processing starts, so larger datasets artificially inflate the measured average latency. In other words, the latency growth is largely a measurement artifact of the data-generation approach, not purely a true execution-latency increase in the signal engine.
