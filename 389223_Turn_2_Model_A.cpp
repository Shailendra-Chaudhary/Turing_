#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

// Define a custom type that can be moved
struct HeavyStruct {
    int data;
    std::vector<int> buffer;

    HeavyStruct(int d, size_t size) : data(d), buffer(size, 0) {}
    HeavyStruct(HeavyStruct&& other) noexcept : data(other.data), buffer(std::move(other.buffer)) {}
    HeavyStruct& operator=(HeavyStruct&& other) noexcept {
        data = other.data;
        buffer = std::move(other.buffer);
        return *this;
    }
    // No copy constructor or copy assignment operator to avoid unnecessary copying
};

// Function to move elements in a vector using move semantics
template <typename Iterator>
Iterator move_iterator(Iterator begin, Iterator end) {
    Iterator dest = begin;
    while (begin != end) {
        *dest = std::move(*begin);
        ++dest;
        ++begin;
    }
    return dest;
}

int main() {
    std::vector<HeavyStruct> v = {
        {1, 100000}, {2, 100000}, {3, 100000}, {4, 100000}, {5, 100000},
        {6, 100000}, {7, 100000}
    };

    // Use std::remove_if to remove elements divisible by 3 with move semantics
    auto new_end = std::remove_if(v.begin(), v.end(), [](const HeavyStruct& m) { return m.data % 3 == 0; });

    // Erase the remaining elements using move semantics
    v.erase(new_end, v.end());

    // Display the remaining elements
    for (const auto& element : v) {
        std::cout << element.data << " ";
    }
    std::cout << std::endl;

    return 0;
}
