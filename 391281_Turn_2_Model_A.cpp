#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>

// Global mutex to protect shared memory access
std::mutex mutex;

// Function to simulate work and memory allocation
void work() {
    // Simulate work by allocating memory in a thread
    std::vector<int> data(10000);  // Allocate a large vector
    std::cout << "Thread " << std::this_thread::get_id() << ": Allocated " << data.size() * sizeof(int) << " bytes\n";

    // Simulate work duration
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

int main() {
    const size_t numThreads = 10;
    std::vector<std::thread> threads;

    // Start multiple threads
    for (size_t i = 0; i < numThreads; ++i) {
        threads.emplace_back(work);
    }

    // Join all threads
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "All threads completed.\n";
    return 0;
}
