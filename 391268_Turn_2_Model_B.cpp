#include <iostream>
#include <chrono>
#include <vector>
#include <memory>
#include <random>
#include <cstdint>
#include <iomanip>

// Custom aligned allocator
template <typename T, std::size_t Alignment>
struct AlignedAllocator {
    using value_type = T;

    AlignedAllocator() = default;

    template <typename U>
    AlignedAllocator(const AlignedAllocator<U, Alignment>&) {}

    T* allocate(std::size_t n) {
        void* ptr = nullptr;
        if (posix_memalign(&ptr, Alignment, n * sizeof(T)) != 0) {
            throw std::bad_alloc();
        }
        return static_cast<T*>(ptr);
    }

    void deallocate(T* p, std::size_t) {
        free(p);
    }
};

uint64_t sumArray(const std::vector<uint64_t, AlignedAllocator<uint64_t, 64>>& arr) {
    uint64_t total = 0;
    for (auto& value : arr) {
        total += value;
    }
    return total;
}

int main() {
    constexpr int size = 1000000; // Array size
    std::vector<uint64_t, AlignedAllocator<uint64_t, 64>> arr(size); // 64-byte aligned storage

    // Fill the array with random numbers
    std::mt19937_64 rng(12345); // Fixed seed for reproducibility
    std::uniform_int_distribution<uint64_t> dist(1, 100);
    for (int i = 0; i < size; ++i) {
        arr[i] = dist(rng);
    }

    // Benchmarking the aligned sumArray
    {
        auto start = std::chrono::high_resolution_clock::now();
        uint64_t sum = sumArray(arr);
        auto end = std::chrono::high_resolution_clock::now();

        std::cout << "Sum using sumArray (aligned): " << sum << std::endl;
        std::cout << "Time taken (aligned): " 
                  << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() 
                  << " microseconds" << std::endl;
    }

    return 0;
}
