#include <iostream>
#include <chrono>
#include <vector>
#include <cstdint>
#include <memory>

// Function to sum the array
uint64_t sumArray(const std::vector<uint64_t>& arr) {
    uint64_t total = 0;
    for (auto& value : arr) {
        total += value;
    }
    return total;
}

// Function to sum the array with aligned storage
uint64_t sumArrayAligned(const std::vector<uint64_t>& arr) {
    uint64_t total = 0;
    for (size_t i = 0; i < arr.size(); ++i) {
        total += arr[i];
    }
    return total;
}

int main() {
    const int size = 1000000; // Array size
    std::vector<uint64_t> arr(size);

    // Fill the array with random numbers
    for (int i = 0; i < size; ++i) {
        arr[i] = i % 100;
    }

    // Benchmarking the normal sumArray
    {
        auto start = std::chrono::high_resolution_clock::now();
        uint64_t sum = sumArray(arr);
        auto end = std::chrono::high_resolution_clock::now();

        std::cout << "Sum using sumArray: " << sum << std::endl;
        std::cout << "Time taken (normal): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;
    }

    // Benchmarking the sumArrayAligned
    {
        auto start = std::chrono::high_resolution_clock::now();
        uint64_t sum = sumArrayAligned(arr);
        auto end = std::chrono::high_resolution_clock::now();

        std::cout << "Sum using sumArrayAligned: " << sum << std::endl;
        std::cout << "Time taken (aligned): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;
    }

    return 0;
}
