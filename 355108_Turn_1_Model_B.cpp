#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

// Simple function to simulate gameplay logic
void gameLogic(std::vector<int>& data) {
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] *= 2; // Performing some operation on each element
    }
}

int main() {
    const size_t DATA_SIZE = 1000000; // Large dataset to simulate game state
    std::vector<int> gameData(DATA_SIZE, 1); // Initialize with some values

    // Compiler optimization level
    const int OPT_LEVEL = 3; // Change this to 0, 1, 2, or 3 to compare different optimizations

    // Disable compiler optimizations for timing purposes
    #pragma GCC push_options
    #pragma GCC optimize ("O" #OPT_LEVEL) // Use O0, O1, O2, O3 for different optimization levels

    std::clock_t start, end;

    // Measure execution time without optimization
    start = std::clock();
    gameLogic(gameData);
    end = std::clock();
    double time_taken = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    std::cout << "Time taken with optimization level " << #OPT_LEVEL << ": " << time_taken << " seconds\n";

    // Restore default compiler optimization settings
    #pragma GCC pop_options

    return 0;
}
