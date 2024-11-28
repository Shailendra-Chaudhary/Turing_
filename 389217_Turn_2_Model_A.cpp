#include <iostream>
#include <vector>
#include <omp.h> // Include the OpenMP header

int main() {
    // Sample data
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const int numElements = data.size();

    #pragma omp parallel for // Parallelize the loop
    for (int i = 0; i < numElements; ++i) {
        // No need for explicit synchronization because we are not modifying the vector outside the loop
        data[i] *= data[i];
    }

    // Output the results
    std::cout << "Squared values: ";
    for (int value : data) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
