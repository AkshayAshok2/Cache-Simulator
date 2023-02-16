# Cache Simulator
## Akshay Ashok

Hello! This project emulates a memory cache using both the "first-in, first-out" and "least recently used" principles.

This file addresses compilation of the `main.cpp` file containing code for the cache analysis project. There are five parameters that affect the output: cacheSize, blockSize, mode (replacement method, true = FIFO, false = LRU), associativity, and the ".trace" file chosen as input. cacheSize and blockSize should be positive powers of 2.

To run:
1. Choose variables
2. Go to terminal:
> `g++ -o main main.cpp -g` at the directory of the main.cpp file.

When shown the list of options, input 1-3 to select the cache type. If 2 or 3 selected, input 1 (FIFO) or 2 (LRU) to select replacement type.

Once cache type (and in some cases replacement type) are selected, the hit ratio will be output.

