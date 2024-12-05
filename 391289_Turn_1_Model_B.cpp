#include <iostream>
#include <vector>
#include <omp.h>

int main() {
    const int size = 1000000;
    std::vector<int> data(size);

    // Initialize the vector with some values
    #pragma omp parallel for
    for (int i = 0; i < size; ++i) {
        data[i] = i;
    }

    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < size; ++i) {
        sum += data[i];
    }

    std::cout << "Total sum is: " << sum << std::endl;

    return 0;
}
