#include <iostream>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <cstring>

const size_t SIZE = 10000000;   // You can adjust the size as per your system's capabilities

#define BENCHMARK(func)                        \
    do {                                       \
        clock_t start = clock();               \
        func();                                 \
        clock_t end = clock();                  \
        double time_taken = (static_cast<double>(end - start)) / CLOCKS_PER_SEC; \
        std::cout << #func << ": " << time_taken << " seconds\n"; \
    } while (0)

void sequentialAccess_CArray() {
    int* arr = new int[SIZE];
    for (size_t i = 0; i < SIZE; ++i) {
        arr[i] = i;
    }

    for (size_t i = 0; i < SIZE; ++i) {
        arr[i];
    }

    delete[] arr;
}

void sequentialAccess_Deque() {
    std::deque<int> deque;
    for (size_t i = 0; i < SIZE; ++i) {
        deque.push_back(i);
    }

    for (size_t i = 0; i < SIZE; ++i) {
        deque[i];
    }
}

void randomAccess_CArray() {
    int* arr = new int[SIZE];
    for (size_t i = 0; i < SIZE; ++i) {
        arr[i] = i;
    }
    std::srand(static_cast<unsigned>(std::time(0)));

    for (size_t i = 0; i < SIZE; ++i) {
        int random_index = std::rand() % SIZE;
        arr[random_index];
    }

    delete[] arr;
}

void randomAccess_Deque() {
    std::deque<int> deque;
    for (size_t i = 0; i < SIZE; ++i) {
        deque.push_back(i);
    }
    std::srand(static_cast<unsigned>(std::time(0)));

    for (size_t i = 0; i < SIZE; ++i) {
        size_t random_index = std::rand() % SIZE;
        deque[random_index];
    }
}

int main() {
    std::cout << "Benchmarking C-style array and std::deque:\n";

    std::cout << "Sequential access:\n";
    BENCHMARK(sequentialAccess_CArray);
    BENCHMARK(sequentialAccess_Deque);

    std::cout << "\nRandom access:\n";
    BENCHMARK(randomAccess_CArray);
    BENCHMARK(randomAccess_Deque);

    return 0;
}
