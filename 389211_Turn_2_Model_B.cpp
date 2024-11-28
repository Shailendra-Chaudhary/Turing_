#include <iostream>
#include <atomic>
#include <functional>
#include <thread>
#include <vector>

// Functional pipeline to increment an atomic value
std::function<void(std::atomic<int>&)> incrementPipeline() {
    return [](std::atomic<int>& atomicValue) {
        int expected = atomicValue.load();
        int desired = expected + 1;
        while (!atomicValue.compare_exchange_weak(expected, desired)) {
            expected = atomicValue.load();
            desired = expected + 1;
        }
    };
}

int main() {
    std::atomic<int> counter(0);
    const int numThreads = 5;
    const int incrementsPerThread = 1000000;

    std::vector<std::thread> threads;
    std::function<void(std::atomic<int>&)> incrementor = incrementPipeline();

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([&counter, incrementsPerThread, incrementor]() {
            for (int j = 0; j < incrementsPerThread; ++j) {
                incrementor(counter);
            }
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Final counter value: " << counter.load() << std::endl;

    return 0;
}  
