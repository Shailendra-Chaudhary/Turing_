#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>  // for aligned_alloc in C++17
#include <new>     // for std::align
#include <cstring> // for std::memset

// Function to perform vector addition
void vectorAdd(const float* a, const float* b, float* c, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        c[i] = a[i] + b[i];
    }
}

// Utility function to simulate memory usage profiling
size_t getMemoryUsageEstimate(size_t elementCount, size_t elementSize) {
    // This is a naive estimation assuming contiguous block allocation
    return elementCount * elementSize;
}

int main() {
    constexpr size_t alignment = 32; // Align to 32 bytes
    constexpr size_t numElements = 1'000'000;
    constexpr size_t dataSize = numElements * sizeof(float);

    // Allocate aligned memory
    float* a = static_cast<float*>(std::aligned_alloc(alignment, dataSize));
    float* b = static_cast<float*>(std::aligned_alloc(alignment, dataSize));
    float* c = static_cast<float*>(std::aligned_alloc(alignment, dataSize));

    if (!a || !b || !c) {
        std::cerr << "Memory allocation failed" << std::endl;
        return 1;
    }

    // Initialize vectors
    std::memset(a, 1, dataSize);
    std::memset(b, 2, dataSize);

    // Memory alignment check
    if ((reinterpret_cast<std::uintptr_t>(a) % alignment != 0) ||
        (reinterpret_cast<std::uintptr_t>(b) % alignment != 0) ||
        (reinterpret_cast<std::uintptr_t>(c) % alignment != 0)) {
        std::cerr << "Memory is not properly aligned" << std::endl;
        std::free(a);
        std::free(b);
        std::free(c);
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Run the algorithm
    vectorAdd(a, b, c, numElements);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Vector addition completed in " << elapsed.count() << " seconds" << std::endl;

    // Profile memory usage
    size_t estimatedMemoryUsage = getMemoryUsageEstimate(numElements, sizeof(float));
    std::cout << "Estimated memory usage: " << estimatedMemoryUsage << " bytes" << std::endl;

    // Free the memory
    std::free(a);
    std::free(b);
    std::free(c);

    return 0;
}
