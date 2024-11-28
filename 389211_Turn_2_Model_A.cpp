#include <iostream>
#include <atomic>
#include <functional>
#include <thread>
#include <vector>

// Function to apply a transformation to an atomic value using compare_exchange
template <typename T>
bool applyAtomicTransform(std::atomic<T>& atomicValue, const std::function<T(T)>& transform) {
    T expected = atomicValue.load();
    T desired = transform(expected);
    return atomicValue.compare_exchange_weak(expected, desired);
}

// Function to apply a transformation repeatedly until it succeeds
template <typename T>
void applyAtomicTransformUntilSuccess(std::atomic<T>& atomicValue, const std::function<T(T)>& transform) {
    while (!applyAtomicTransform(atomicValue, transform)) {}
}

// Example of a transform function that increments the value
int increment(int value) {
    return value + 1;
}

// Example of a transform function that decrements the value
int decrement(int value) {
    return value - 1;
}

int main() {
    // Create an atomic integer initialized to 0
    std::atomic<int> counter(0);

    // Function to increment the counter repeatedly
    auto incrementCounter = [&counter]() {
        applyAtomicTransformUntilSuccess(counter, increment);
    };

    // Function to decrement the counter repeatedly
    auto decrementCounter = [&counter]() {
        applyAtomicTransformUntilSuccess(counter, decrement);
    };

    // Number of threads to use for incrementing and decrementing
    const int numThreads = 10;
    // Number of operations each thread will perform
    const int operationsPerThread = 10000;

    // Create vectors of threads for increment and decrement
    std::vector<std::thread> incrementThreads;
    std::vector<std::thread> decrementThreads;

    // Launch threads to increment and decrement the counter
    for (int i = 0; i < numThreads; ++i) {
        incrementThreads.emplace_back(incrementCounter);
        decrementThreads.emplace_back(decrementCounter);
    }

    // Join all increment threads
    for (auto& thread : incrementThreads) {
        thread.join();
    }

    // Join all decrement threads
    for (auto& thread : decrementThreads) {
        thread.join();
    }

    // Print the final value of the counter
    std::cout << "Final counter value: " << counter.load() << std::endl;

    return 0;
}
