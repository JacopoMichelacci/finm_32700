Overview of your system architecture

For this part of the project for phase 3 we continued building on the previous phases. For this specifcally going from the matrix operations in phase 1 and HFT infrastructure in phase 2 we then built our marketsnapshot, order manager, the feed parser, and built out the trading strategy in the main file. We also implemented a header file for price level so that it could be included accross files and used. The main goal we had in mind was maintaining live market snapshots and managing order fills.

Explanation of how memory is managed safely

Memory is managed safely by using standard c++ containers like std::vector and map for feeds and price levels as well as using RAII to ensure that cleanup is automatic. Specifcally, we made sure to also not use manually allocated memory to avoid double cleanup or memory leaks. Because with larger datasets we wanted to ensure that our platform safely and without error could handle large amounts of informaiton. 

Instructions on how to compile and run the code

We utilized CMake for this project so by calling build and make and then calling /run.sh the full phase can be built and run. 


How to verify correctness and memory safety

Ran with the sample feed we ensured that the expected output takes place and running as well as using Valgrind to ensure that no memory leaks were taking place. 

Findings: 

Building from the previous phases we found that these parts intertwined and we were able to build on the base that we had established. Using RAII and automatic cleanup of pointers allowed us to not need to worry about destructors or manually calling delete which should also be beneficial for further applications of the next steps of the project. 