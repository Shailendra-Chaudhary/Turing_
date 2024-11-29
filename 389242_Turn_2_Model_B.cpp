#include <iostream>
#include <chrono>
#include <thread>
#include <assert.h>

const int NUM_ITERATIONS = 1000000;
const int SAMPLING_RATE = 10;  // in Hz

int main() {
    std::cout << "Real-time Assertion Performance Test" << std::endl;

    // Simulate a real-time task that processes data at a fixed rate
    double data = 0.0;
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        // Simulate some work
        data += 0.1;

        // Assertion to check that data is always positive
        assert(data >= 0.0, "Data became negative!");

        // Add a delay to simulate sampling at a fixed rate
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / SAMPLING_RATE));
    }

    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
    double executionTime = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime).count();

    std::cout << "Execution Time: " << executionTime << " seconds" << std::endl;

    // Calculate the average loop time
    double averageLoopTime = executionTime / static_cast<double>(NUM_ITERATIONS);
    std::cout << "Average Loop Time: " << averageLoopTime * 1000.0 << " ms" << std::endl;

    return 0;
} 
