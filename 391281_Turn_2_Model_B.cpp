#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

// Worker function to mimic memory-intensive work
void worker(size_t id) {
    // Simulate some memory allocation and deallocation
    while (true) {
        std::vector<int> data(1000); // Allocate some memory
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
    }
}

int main() {
    std::cout << "Starting concurrent program...\n";

    size_t numThreads = 4;
    std::vector<std::thread> threads;

    // Launch threads
    for (size_t i = 0; i < numThreads; ++i) {
        threads.emplace_back(worker, i);
    }

    // Allow the threads to run for some time
    std::this_thread::sleep_for(std::chrono::seconds(10));

    // Conclude program execution after enough profiling data is generated
    for (auto& t : threads) {
        if (t.joinable()) {
            t.detach();  // We use detach here since we are terminating forcefully
        }
    }

    std::cout << "Concurrent program completed.\n";
    return 0;
}
