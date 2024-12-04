#include <iostream>
#include <vector>

void someUtilityFunction(std::vector<int>& numbers) {
    for (auto num : numbers) {
        if (num % 2 == 0) {
            std::cout << "Even number: " << num << std::endl;
        }
    }
}

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
    someUtilityFunction(numbers);

    int *memoryLeak = new int;  // For demonstration, to be caught by Valgrind
    *memoryLeak = 42;
    std::cout << "Allocated number: " << *memoryLeak << std::endl;

    return 0;
}
