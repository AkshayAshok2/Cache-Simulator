# Cache Simulator
## Akshay Ashok

Hello! This project emulates a memory cache using both the "first-in, first-out" and "least recently used" principles.

This file addresses compilation of the `main.cpp` file containing code for the cache analysis project. There are five parameters that affect the output: 
* `cacheSize`: size of the cache (in bytes), should be a positive power of 2
* `blockSize`: size of each block or unit in the cache (in bytes), should be a positive power of 2
* `mode`: replacement method of the cache; `true` = FIFO, `false` = LRU
* `associativity`: for a *set associative* cache, the number of lines in each set within the cache
* The `.trace` file chosen as input

To run:
1. Choose variables
2. Go to terminal:
> Navigate to the directory of `main.cpp`

> Paste `g++ -o main main.cpp -g` and hit enter

When shown the list of options, input 1-3 to select the cache type. If 2 or 3 selected, input 1 (FIFO) or 2 (LRU) to select replacement type.

Once cache type (and in some cases replacement type) are selected, the hit ratio will be output.
