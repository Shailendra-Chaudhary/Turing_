#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

// Define a custom type that uses unique_ptr to manage memory
struct MyResource {
    std::unique_ptr<int> data;

    MyResource(int d) : data(std::make_unique<int>(d)) {}
    MyResource(MyResource&& other) noexcept : data(std::move(other.data)) {}
    MyResource& operator=(MyResource&& other) noexcept {
        data = std::move(other.data);
        return *this;
    }
};

// Custom erase function that uses unique_ptr to free memory
template <typename ForwardIt>
ForwardIt custom_erase(ForwardIt first, ForwardIt last) {
    for (ForwardIt it = first; it != last; ++it) {
        // Make sure to free the memory managed by unique_ptr
        it->data.reset();
    }
    return last;
}

int main() {
    std::vector<MyResource> v{1, 2, 3, 4, 5, 6, 7};

    // Remove elements divisible by 3 using custom predicate
    auto new_end = std::remove_if(v.begin(), v.end(), [](const MyResource& m) { return m.data ? *m.data % 3 == 0 : false; });

    // Use custom eraser to free memory of removed elements
    v.erase(custom_erase(new_end, v.end()), v.end());

    // Display the remaining elements
    for (const auto& element : v) {
        std::cout << *(element.data) << " ";
    }
    std::cout << std::endl;

    return 0;
} 
