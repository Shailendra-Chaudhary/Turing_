#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

// Define a custom type with move semantics
struct HeavyObject {
    int data;
    std::unique_ptr<int[]> buffer; // unique_ptr ensures memory is deallocated

    // Constructor
    HeavyObject(int d, size_t size) : data(d), buffer(new int[size]) {}

    // Move constructor
    HeavyObject(HeavyObject&& other) noexcept 
        : data(std::move(other.data)), 
          buffer(std::move(other.buffer)) {}

    // Move assignment operator
    HeavyObject& operator=(HeavyObject&& other) noexcept {
        data = std::move(other.data);
        buffer = std::move(other.buffer);
        return *this;
    }

    // Default destructor to clean up the buffer
    ~HeavyObject() {
        // Automatically deleted by std::unique_ptr
    }
};

// Lambda function to be used as the predicate in std::remove_if
auto removeIfEven = [](const HeavyObject& obj) {
    return obj.data % 2 == 0;
};

// Main function
int main() {
    std::vector<HeavyObject> objects = {
        {1, 1000}, {2, 1000}, {3, 1000}, {4, 1000}, {5, 1000}
    };

    // Use std::remove_if to partition the vector and mark elements to be removed
    auto it = std::remove_if(objects.begin(), objects.end(), removeIfEven);

    // Erase the marked elements efficiently using move semantics
    objects.erase(it, objects.end());

    // Display the remaining elements' data
    for (const auto& obj : objects) {
        std::cout << obj.data << " ";
    }
    std::cout << std::endl;

    return 0;
}
