#include <iostream>
#include <vector>

// Function to demonstrate different paths
void processData(const std::vector<int>& data, bool checkEven = false) {
    for (int value : data) {
        if (checkEven && value % 2 == 0) {
            std::cout << "Even number: " << value << std::endl;
        }
        if (value % 3 == 0) {
            std::cout << "Multiple of three: " << value << std::endl;
        }
    }
}

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6};

    // Simulate different execution paths
    processData(numbers);
    processData(numbers, true);

    // Manual way to note execution paths
    // Could use a simple tracking mechanism instead,
    // but using gcov would be a more standard approach.

    return 0;
}
