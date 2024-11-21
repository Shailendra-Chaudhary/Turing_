#include <iostream>
#include <deque>
#include <array>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>

#define DATA_SIZE 1000000

const int iterations = 1000;

template<typename Container>
void testRandomAccess(const Container& container) {
    std::cout << "\nRandom Access Test: \n";
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; i++) {
        int randomIndex = std::rand() % DATA_SIZE;
        container[randomIndex];
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << std::fixed << std::setprecision(3)
              << "Time taken for " << iterations << " random accesses: "
              << duration.count() << " ms\n";
}

template<typename Container>
void testSequentialAccess(const Container& container) {
    std::cout << "\nSequential Access Test: \n";
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; i++) {
        for (const auto& element : container) {
            element;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << std::fixed << std::setprecision(3) 
              << "Time taken for " << iterations << " sequential accesses: " 
              << duration.count() << " ms\n";
}

int main() {
    srand(static_cast<unsigned>(std::time(0)));

    // C-style array
    int* cArray = new int[DATA_SIZE];
    for (int i = 0; i < DATA_SIZE; i++) {
        cArray[i] = i;
    }

    {
        std::cout << "\nTesting C Array: \n";
        testRandomAccess(cArray);
        testSequentialAccess(cArray);
    }

    // std::deque
    std::deque<int> deque;
    for (int i = 0; i < DATA_SIZE; i++) {
        deque.push_back(i);
    }

    {
        std::cout << "\nTesting std::deque: \n";
        testRandomAccess(deque);
        testSequentialAccess(deque);
    }

    // Cleanup
    delete[] cArray;

    return 0;
}
