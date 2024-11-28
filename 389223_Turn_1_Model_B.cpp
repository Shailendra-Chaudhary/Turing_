#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

// Define a custom type that can be moved
struct MyStruct {
    int data;

    MyStruct(int d) : data(d) {}
    MyStruct(MyStruct&& other) noexcept : data(other.data) {}
    MyStruct& operator=(MyStruct&& other) noexcept {
        data = other.data;
        return *this;
    }
    // No copy constructor or copy assignment operator to avoid unnecessary copying
};

// Custom erase algorithm that uses move semantics to remove elements
template <typename ForwardIt, typename Predicate>
ForwardIt custom_erase_if(ForwardIt first, ForwardIt last, Predicate pred) {
    ForwardIt d_first = first;
    while (first != last) {
        if (!pred(*first)) {
            *d_first = std::move(*first);
            ++d_first;
        }
        ++first;
    }
    return d_first;
}

int main() {
    std::vector<MyStruct> v{1, 2, 3, 4, 5, 6, 7};

    // Use custom erase and move algorithm to remove elements divisible by 3
    v.erase(custom_erase_if(v.begin(), v.end(), [](const MyStruct& m) { return m.data % 3 == 0; }), v.end());

    // Display the remaining elements
    for (const auto& element : v) {
        std::cout << element.data << " ";
    }
    std::cout << std::endl;

    return 0;
}
