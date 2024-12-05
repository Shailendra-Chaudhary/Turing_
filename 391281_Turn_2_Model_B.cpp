#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>

// A simple memory allocation profiler
class MemoryProfiler {
public:
    static void allocate(size_t size) {
        std::lock_guard<std::mutex> lock(mutex_);
        totalAllocated_ += size;
        std::cout << "Allocated " << size << " bytes. Total allocated: " << totalAllocated_ << " bytes\n";
    }

    static void deallocate(size_t size) {
        std::lock_guard<std::mutex> lock(mutex_);
        totalAllocated_ -= size;
        std::cout << "Deallocated " << size << " bytes. Total allocated: " << totalAllocated_ << " bytes\n";
    }

private:
    static size_t totalAllocated_;
    static std::mutex mutex_;
};

size_t MemoryProfiler::totalAllocated_ = 0;
std::mutex MemoryProfiler::mutex_;

// Overriding new and delete to capture memory allocation and deallocation
void* operator new(size_t size) {
    void* ptr = std::malloc(size);
    if (ptr) {
        MemoryProfiler::allocate(size);
    }
    return ptr;
}

void operator delete(void* ptr) noexcept {
    if (ptr) {
        // Size of deallocating memory can't be passed to the delete operator, hence not tracked here.
        MemoryProfiler::deallocate(0);
    }
    std::free(ptr);
}

// Implementing a concurrent task
void taskFunction(int threadId) {
    std::cout << "Thread " << threadId << " is starting.\n";

    // Simulating memory allocation
    // Using a 1000-int vector as an example of dynamic allocation
    std::vector<int> vec(1000, threadId); // Memory allocated here

    // Simulate some work
    for (int& num : vec) {
        num *= 2;
    }

    std::cout << "Thread " << threadId << " has finished work.\n";
}

int main() {
    const std::size_t numThreads = 4;
    std::vector<std::thread> threads;

    // Start threads
    for (std::size_t i = 0; i < numThreads; ++i) {
        threads.emplace_back(taskFunction, i);
    }

    // Join threads
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "All threads have finished execution.\n";
    return 0;
}
