#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <cstdlib>

class MemoryAllocator {
public:
    void* allocate(std::size_t size) {
        void* ptr = std::malloc(size);
        if (ptr) {
            std::cout << "Allocated " << size << " bytes at " << ptr << std::endl;
        } else {
            std::cerr << "Memory allocation failed" << std::endl;
        }
        return ptr;
    }

    void deallocate(void* ptr) {
        if (ptr) {
            std::cout << "Deallocated " << ptr << std::endl;
            std::free(ptr);
        } else {
            std::cerr << "Memory deallocation failed" << std::endl;
        }
    }
};

class MemoryTracker {
private:
    MemoryAllocator allocator;
    std::atomic<int> numAllocations;

public:
    MemoryTracker() : numAllocations(0) {}

    void* allocate(std::size_t size) {
        return allocator.allocate(size);
    }

    void deallocate(void* ptr) {
        allocator.deallocate(ptr);
    }

    int getNumAllocations() const {
        return numAllocations;
    }

    void incrementAllocations() {
        ++numAllocations;
    }

    void decrementAllocations() {
        --numAllocations;
    }
};

void concurrentTask(MemoryTracker& tracker, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        void* ptr = tracker.allocate(1024);
        tracker.incrementAllocations();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        tracker.deallocate(ptr);
        tracker.decrementAllocations();
    }
}

int main() {
    MemoryTracker tracker;
    std::vector<std::thread> threads;

    const int numThreads = 4;
    const int iterations = 100;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(concurrentTask, std::ref(tracker), iterations);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Total allocations: " << tracker.getNumAllocations() << std::endl;

    return 0;
}
