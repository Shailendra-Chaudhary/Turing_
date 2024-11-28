#include <atomic>
#include <iostream>
#include <thread>

using namespace std;

template<typename T>
struct Counter {
    std::atomic<T> value = T{};

    // Increment the counter using compare_exchange_weak (functional style)
    template<typename Func>
    void increment(Func&& func) {
        T expected = value.load(memory_order_relaxed);
        while (!value.compare_exchange_weak(expected, func(expected), memory_order_relaxed, memory_order_relaxed)) {
            // Wait for another thread to increment if compare_exchange_weak fails
            std::this_thread::sleep_for(std::chrono::microseconds(1));
            expected = value.load(memory_order_relaxed);
        }
    }

    // Read the current value
    T get_value() const {
        return value.load(memory_order_relaxed);
    }
};


int main() {
    Counter<int> counter;

    std::thread increment_thread([&]() {
        for (int i = 0; i < 100000; ++i) {
            counter.increment([](int current) { return current + 1; });
        }
    });

    std::thread decrement_thread([&]() {
        for (int i = 0; i < 100000; ++i) {
            counter.increment([](int current) { return current - 1; });
        }
    });

    increment_thread.join();
    decrement_thread.join();

    // Check the final value using functional style operations
    cout << "Final value: " << (counter.get_value() == 0 ? "0 (Expected)" : "Not 0 (Unexpected)") << endl;

    return 0;
} 
