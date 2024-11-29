#include <iostream>
#include <vector>
#include <future>
#include <thread>

// Function to calculate the sum of an array
double sumArray(const std::vector<double>& arr) {
    double total = 0.0;
    for (double num : arr) {
        total += num;
    }
    return total;
}

int main() {
    const int size = 1'000'000;
    std::vector<double> array(size);

    // Initialize array with random values
    for (int i = 0; i < size; ++i) {
        array[i] = static_cast<double>(rand()) / RAND_MAX;
    }

    // Start an asynchronous computation
    std::future<double> futureSum = std::async(std::launch::async, sumArray, array);

    // Perform other tasks without waiting for the computation to finish
    std::cout << "Doing some other work in the main thread...\n";

    // Wait for the computation to complete and retrieve the result
    double totalSum = futureSum.get();

    // Output the result
    std::cout << "The sum of the array is: " << totalSum << std::endl;

    return 0;
}
