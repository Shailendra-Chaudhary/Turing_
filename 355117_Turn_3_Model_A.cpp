#include <iostream>
#include <vector>
#include <deque>
#include <chrono>
#include <cstdlib> // For rand() function
#include <ctime>   // For seeding rand()

// Function to measure the access time for a given data structure
template <typename T>
double measureAccessTime(T& data, size_t size, bool randomAccess) {
    std::chrono::high_resolution_clock::time_point start, end;
    double timeElapsed;

    // Seed rand() for random access
    std::srand(static_cast<unsigned>(std::time(0)));

    if (randomAccess) {
        // Random access pattern
        start = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < size; ++i) {
            size_t randomIndex = std::rand() % size;
            data[randomIndex];
        }
        end = std::chrono::high_resolution_clock::now();
    } else {
        // Sequential access pattern
        start = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < size; ++i) {
            data[i];
        }
        end = std::chrono::high_resolution_clock::now();
    }

    // Calculate the time elapsed in nanoseconds
    timeElapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    // Return the time elapsed in milliseconds
    return timeElapsed / 1e6;
}

int main() {
    const size_t DATA_SIZE = 1'000'000; // 1 million elements

    // Compare std::deque and C-style array for sequential and random access
    std::deque<int> dequeData(DATA_SIZE);
    int* cArrayData = new int[DATA_SIZE];

    // Initialize data with random values to avoid caching of previous data
    for (size_t i = 0; i < DATA_SIZE; ++i) {
        dequeData[i] = rand();
        cArrayData[i] = rand();
    }

    // Sequential access test
    double dequeSeqTime = measureAccessTime(dequeData, DATA_SIZE, false);
    double cArraySeqTime = measureAccessTime(cArrayData, DATA_SIZE, false);

    std::cout << "Sequential Access Test Results:\n";
    std::cout << "std::deque: " << dequeSeqTime << " milliseconds\n";
    std::cout << "C-style array: " << cArraySeqTime << " milliseconds\n";

    // Random access test
    double dequeRandTime = measureAccessTime(dequeData, DATA_SIZE, true);
    double cArrayRandTime = measureAccessTime(cArrayData, DATA_SIZE, true);

    std::cout << "\nRandom Access Test Results:\n";
    std::cout << "std::deque: " << dequeRandTime << " milliseconds\n";
    std::cout << "C-style array: " << cArrayRandTime << " milliseconds\n";

    // Clean up memory allocated for the C-style array
    delete[] cArrayData;

    return 0;
}
