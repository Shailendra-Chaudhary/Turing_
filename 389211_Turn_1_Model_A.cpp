#include <iostream>
#include <atomic>
#include <functional>
#include <thread>
#include <vector>

// Function to increment an atomic value using compare_exchange
bool incrementAtomic(std::atomic<int>& atomicValue) {
    int expected = atomicValue.load();
    int desired = expected + 1;
    return atomicValue.compare_exchange_weak(expected, desired);
}

// Function that uses incrementAtomic to increment the value a number of times
void incrementManyTimes(std::atomic<int>& atomicValue, int count) {
    for (int i = 0; i < count; ++i) {
        if (!incrementAtomic(atomicValue)) {
            // If the increment fails, spin-wait until it succeeds
            while (!incrementAtomic(atomicValue)) {}
        }
    }
}

int main() {
    // Create an atomic integer initialized to 0
    std::atomic<int> counter(0);

    // Number of threads to use for incrementing
    const int numThreads = 5;
    // Number of increments each thread will perform
    const int incrementsPerThread = 1000000;

    // Create a vector of threads
    std::vector<std::thread> threads;

    // Launch threads to increment the counter
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([&counter, incrementsPerThread]() {
            incrementManyTimes(counter, incrementsPerThread);
        });
    }

    // Join all threads
    for (auto& thread : threads) {
        thread.join();
    }

    // Print the final value of the counter
    std::cout << "Final counter value: " << counter.load() << std::endl;

    return 0;
}
