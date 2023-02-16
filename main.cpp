#include <fstream>
#include <sstream>
#include <iostream>
#include <bitset>
#include <vector>
#include <math.h>
#include <unordered_map>
using namespace std;

/* Run command:
    g++ -o main main.cpp -g
*/

double directMapped(vector<string> inputs, int cacheSize, int blockSize)
{
    unordered_map<string, string> cache;

    int numHits = 0;
    int currSize = 0;
    int lines = cacheSize / blockSize;
    int lineBits = log(lines) / log(2);
    int offsetBits = log(blockSize) / log(2);
    int tagBits = 32 - lineBits - offsetBits;

    for (string binary : inputs)
    {
        string tag = binary.substr(0, tagBits);
        string line = binary.substr(tagBits, lineBits);

        if (cache.count(line) && cache[line] == tag)
            numHits++;
        else if (cache.count(line))
            cache[line] = tag;
        else if (currSize < lines)
        {
            cache[line] = tag;
            currSize++;
        }
    }

    return numHits / (double)inputs.size();
}

// mode == true -> FIFO, mode == false -> LRU
double fullyAssoc(vector<string> inputs, int cacheSize, int blockSize, bool mode)
{
    unordered_map<string, int> cache;
    
    int numHits = 0;
    int lines = cacheSize / blockSize;
    int lineBits = log(lines) / log(2);
    int offsetBits = log(blockSize) / log(2);
    int tagBits = 32 - lineBits - offsetBits;

    for (int i = 0; i < inputs.size(); i++)
    {
        string tag = inputs[i].substr(0, tagBits);

        if (cache.count(tag))
        {
            //cout << "Hit" << " " << tag << endl;
            numHits++;
            if (!mode) cache[tag] = i; // Only if LRU
        }
        else if (cache.size() < lines)
        {
            //cout << "Inserted" << " " << tag << endl;
            cache[tag] = i;
        }
        else
        {
            int min;
            string minTag;
            for (auto iter = cache.begin(); iter != cache.end(); iter++)
            {
                if (iter == cache.begin() || min > iter->second)
                {
                    min = iter->second;
                    minTag = iter->first;
                }
            }
            //cout << "Replaced" << " " << minTag << endl;
            cache.erase(minTag);
            cache[tag] = i;
        }
        
    }

    return numHits / (double)inputs.size();
}

// mode == true -> FIFO, mode == false -> LRU
double setAssoc(vector<string> inputs, int cacheSize, int blockSize, bool mode, int associativity) 
{
    unordered_map<string, unordered_map<string, int>> cache;

    int numHits = 0;
    int lines = cacheSize / blockSize;
    int numSets = lines / associativity;
    int lineBits = log(numSets) / log(2);
    int offsetBits = log(blockSize) / log(2);
    int tagBits = 32 - lineBits - offsetBits;

    for (int i = 0; i < inputs.size(); i++)
    {
        // Get tag and line bits
        string tag = inputs[i].substr(0, tagBits);
        string line = inputs[i].substr(tagBits, lineBits);

        if (!cache[line].empty() && cache[line].count(tag))
        {
            numHits++;
            if (!mode) cache[line][tag] = i; // Only if LRU
        }
        else if (cache[line].size() < associativity)
        {
            cache[line][tag] = i;
        }
        else
        {
            int min;
            string minTag;
            for (auto iter = cache[line].begin(); iter != cache[line].end(); iter++)
            {
                if (iter == cache[line].begin() || min > iter->second)
                {
                    min = iter->second;
                    minTag = iter->first;
                }
            }
            cache[line].erase(minTag);
            cache[line][tag] = i;
        }
    }

    return numHits / (double)inputs.size();
}

int main()
{
    vector<string> addresses;
    ifstream inFile("Input/gcc.trace");
    string line, buffer, address, buffer2;

    while (getline(inFile, line))
    {
        istringstream ss(line);
        ss >> buffer;
        ss >> address;
        ss >> buffer2;

        address = address.substr(2, 8);

        // Hex to binary for input address
        stringstream ss2;
        ss2 << hex << address;
        unsigned temp; ss2 >> temp;
        bitset<32> binary(temp);

        addresses.push_back(binary.to_string());
    }

    cout << "Size of input: " << addresses.size() << endl;
    int cacheSize = 1024, blockSize = 64; // Sizes of cache and block in bytes
    cout << "1. Direct Mapped\n2. Fully Associative\n3. Set Associative" << endl;
    int input; cin >> input;

    switch (input)
    {
        case 1:
            cout << "Number of hits: " << directMapped(addresses, cacheSize, blockSize) << endl;
            break;
        case 2:
            cout << "1. FIFO\n2. LRU\n";
            cin >> input;
            if (input == 1) 
                cout << "Hit ratio (FIFO): " << fullyAssoc(addresses, cacheSize, blockSize, true);
            else if (input == 2) 
                cout << "Hit ratio (LRU): " << fullyAssoc(addresses, cacheSize, blockSize, false);
            break;
        case 3:
            cout << "1. FIFO\n2. LRU\n";
            cin >> input;
            if (input == 1) 
                cout << "Hit ratio (FIFO): " << setAssoc(addresses, cacheSize, blockSize, true, 4);
            else if (input == 2) 
                cout << "Hit ratio (LRU): " << setAssoc(addresses, cacheSize, blockSize, false, 4);
            break;
    }
    return 0;
}
