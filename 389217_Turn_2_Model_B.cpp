#include <iostream>
#include <vector>
#include <omp.h>

void squareElements(std::vector<int>& data) {
    #pragma omp parallel for
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] *= data[i];
    }
}

int main() {
    // Sample data
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Set the number of threads to use
    omp_set_num_threads(4);

    // Parallel processing of vector elements
    squareElements(data);

    // Output the results
    std::cout << "Squared values: ";
    for (int value : data) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
