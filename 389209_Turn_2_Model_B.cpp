#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

class MyClass {
public:
    int value;
    MyClass(int v) : value(v) {}
};

int main() {
    // Factors to consider when choosing the STL container:
    1. **Element Usage**:
        - Determine if you need to access elements efficiently by index (e.g., for arrays, vectors, lists).
        - If your application requires fast lookups by key, consider maps or unordered_maps.
        - If order doesn't matter, unordered_sets or sets can be a better choice for unique elements.
    
    2. **Memory Management**:
        - If elements have dynamic memory, you might want to consider containers that provide deep copy or move semantics for their members (e.g., std::vector<std::unique_ptr<MyClass>>).
    
    3. **Operational Costs**:
        - Evaluation should involve measuring the time and space complexities of common operations like insertion, deletion, finding, and traversing the container.
    
    4. **Additional Requirements**:
        - Decide if you need ordered elements or unordered elements.
        - Consider if you need fast insertion or deletion at specific locations (e.g., std::deque).
        - Check if the container supports iterators with constant-time dereferencing, if necessary.
    
    // Example scenarios and appropriate containers:
    
    // 1. Needs elements to be stored in fixed order and accessed by index efficiently.
    // Suitable: std::vector
    std::vector<MyClass> myVector = {MyClass(1), MyClass(3), MyClass(2)};
    for (const auto& element : myVector) {
        std::cout << element.value << " "; // Output: 1 3 2
    }
    std::cout << std::endl;

    // 2. Needs elements to be stored in sorted order and support fast lookups by key.
    // Suitable: std::set (or std::map for key-value pairs)
    std::set<MyClass> mySet = {MyClass(1), MyClass(3), MyClass(2)};
    for (const auto& element : mySet) {
        std::cout << element.value << " "; // Output: 1 2 3 (sorted order)
    }
    std::cout << std::endl;
    
    return 0;
}
