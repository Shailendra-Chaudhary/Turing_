#include <iostream>
#include <deque>
#include <array>
#include <chrono>
#include <random>
#include <cstdlib>

using namespace std;

const size_t DATA_SIZE = 1000000;

template <typename T>
void randomAccessTest(T& container) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, DATA_SIZE - 1);

    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < DATA_SIZE; ++i) {
        container[dis(gen)] = i;
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Random access time for " << typeid(container).name() << ": " << duration << " microseconds" << endl;
}

template <typename T>
void sequentialAccessTest(T& container) {
    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < DATA_SIZE; ++i) {
        container[i] = i;
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Sequential access time for " << typeid(container).name() << ": " << duration << " microseconds" << endl;
}

int main() {
    std::cout << "Cache Performance Comparison: std::deque vs C-style array" << std::endl;

    std::array<int, DATA_SIZE> arr;
    std::deque<int> deque;

    sequentialAccessTest(arr);
    sequentialAccessTest(deque);

    randomAccessTest(arr);
    randomAccessTest(deque);

    return 0;
}
