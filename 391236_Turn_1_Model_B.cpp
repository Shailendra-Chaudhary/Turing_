#include <iostream>
#include <vector>

void processData(const std::vector<int>& data) {
    for (int value : data) {
        if (value % 2 == 0) {
            std::cout << "Even number: " << value << std::endl;
        }
    }
}

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6};

    // Simulate some processing
    processData(numbers);

    // Intentional memory leak for demonstration
    int* leak = new int(10);
    std::cout << "Leaked value: " << *leak << std::endl;
    // delete leak; // This line is omitted to simulate a memory leak

    return 0;
}
