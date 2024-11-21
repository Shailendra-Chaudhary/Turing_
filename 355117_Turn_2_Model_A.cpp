#include <iostream>
#include <deque>
#include <chrono>
#include <array>
#include <random>
#include <cstdlib> // For srand, rand

constexpr size_t DATA_SIZE = 10000000;

template <typename Container>
double benchmark_access(Container& container, bool random_access) {
    auto start = std::chrono::high_resolution_clock::now();

    size_t access_count = DATA_SIZE;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, DATA_SIZE - 1);

    if (random_access) {
        for (size_t i = 0; i < access_count; ++i) {
            size_t index = dis(gen);
            container[index];
        }
    } else {
        for (size_t i = 0; i < access_count; ++i) {
            container[i];
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return static_cast<double>(duration.count()) / 1'000'000; // Return in milliseconds
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    {
        std::deque<int> deque(DATA_SIZE);

        for (size_t i = 0; i < DATA_SIZE; ++i) {
            deque[i] = i;
        }

        std::cout << "std::deque with sequential access: " << benchmark_access(deque, false) << " ms\n";
        std::cout << "std::deque with random access: " << benchmark_access(deque, true) << " ms\n";
    }

    {
        int arr[DATA_SIZE];

        for (size_t i = 0; i < DATA_SIZE; ++i) {
            arr[i] = i;
        }

        std::cout << "C-style array with sequential access: " << benchmark_access(arr, false) << " ms\n";
        std::cout << "C-style array with random access: " << benchmark_access(arr, true) << " ms\n";
    }

    return 0;
}
