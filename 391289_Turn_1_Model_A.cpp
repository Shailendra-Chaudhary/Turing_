#include <iostream>
#include <cstdlib>
#include <omp.h>

int main() {
    const int arraySize = 1000000;
    double* array = new double[arraySize];

    // Initialize the array
    for (int i = 0; i < arraySize; ++i) {
        array[i] = static_cast<double>(rand()) / RAND_MAX;
    }

    double sum = 0.0;

    // Parallel sum using OpenMP
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arraySize; ++i) {
        sum += array[i];
    }

    std::cout << "Sum using OpenMP: " << sum << std::endl;

    delete[] array;

    return 0;
}
