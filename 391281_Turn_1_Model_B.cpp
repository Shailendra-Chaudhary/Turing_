#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

// Simple memory tracker
class MemoryTracker {
public:
    static void allocate(size_t size) {
        std::lock_guard<std::mutex> lock(mutex_);
        totalAllocated_ += size;
        std::cout << "Allocated " << size << " bytes, Total: " << totalAllocated_ << " bytes\n";
    }

    static void deallocate(size_t size) {
        std::lock_guard<std::mutex> lock(mutex_);
        totalAllocated_ -= size;
        std::cout << "Deallocated " << size << " bytes, Total: " << totalAllocated_ << " bytes\n";
    }

private:
    static size_t totalAllocated_;
    static std::mutex mutex_;
};

size_t MemoryTracker::totalAllocated_ = 0;
std::mutex MemoryTracker::mutex_;

// Custom new and delete overloads for tracking
void* operator new(size_t size) {
    void* ptr = std::malloc(size);
    if (ptr) MemoryTracker::allocate(size);
    return ptr;
}

void operator delete(void* ptr, size_t size) noexcept {
    if (ptr) MemoryTracker::deallocate(size);
    std::free(ptr);
}

// Worker function for threads
void work() {
    std::vector<int> data(1000); // Allocate memory
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
}

int main() {
    const size_t numThreads = 10;
    std::vector<std::thread> threads;

    // Start threads
    for (size_t i = 0; i < numThreads; ++i) {
        threads.emplace_back(work);
    }

    // Join threads
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "All threads completed.\n";
    return 0;
}
