#include <iostream>
#include <deque>
#include <ctime>
#include <cstdlib>
#include <random>
#include <chrono>

const int SIZE = 1000000;

void randomAccessTest(void* data) {
    const int size = SIZE;

    if (data == nullptr) {
        std::cout << "Array: Random Access Test\n";
    } else {
        std::cout << "Deque: Random Access Test\n";
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size - 1);

    auto start = std::chrono::high_resolution_clock::now();

    volatile long sum = 0;

    if (data == nullptr) {
        int* array = (int*)data;
        for (int i = 0; i < size; ++i) {
            int rand_idx = dis(gen);
            sum += array[rand_idx];
        }
    } else {
        std::deque<int>& deque = *(std::deque<int>*)data;
        for (int i = 0; i < size; ++i) {
            int rand_idx = dis(gen);
            sum += deque[rand_idx];
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end - start;

    std::cout << "Elapsed time: " << elapsed_time.count() << " seconds\n";
    std::cout << "Sum: " << sum << "\n";
}

void sequentialAccessTest(void* data) {
    const int size = SIZE;

    if (data == nullptr) {
        std::cout << "Array: Sequential Access Test\n";
    } else {
        std::cout << "Deque: Sequential Access Test\n";
    }

    auto start = std::chrono::high_resolution_clock::now();

    volatile long sum = 0;

    if (data == nullptr) {
        int* array = (int*)data;
        for (int i = 0; i < size; ++i) {
            sum += array[i];
        }
    } else {
        std::deque<int>& deque = *(std::deque<int>*)data;
        for (int i = 0; i < size; ++i) {
            sum += deque[i];
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end - start;

    std::cout << "Elapsed time: " << elapsed_time.count() << " seconds\n";
    std::cout << "Sum: " << sum << "\n";
}
 
int main() {
    std::srand(static_cast<unsigned>(std::time(0)));

    int* array = new int[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        array[i] = std::rand();
    }

    std::deque<int> deque(array, array + SIZE);

    std::cout << "\nTest Started:\n";

    randomAccessTest(nullptr);
    randomAccessTest(&deque);

    sequentialAccessTest(nullptr);
    sequentialAccessTest(&deque);

    delete[] array;

    std::cout << "\nTest Finished.\n";
    return 0;
}
