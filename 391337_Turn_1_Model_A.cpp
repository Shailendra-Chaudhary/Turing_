#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <random>
#include <functional>
#include <cassert>

// Function to filter values greater than a threshold
std::vector<int> filterData(const std::vector<int>& data, int threshold) {
    std::vector<int> filtered;
    std::copy_if(data.begin(), data.end(), std::back_inserter(filtered),
                 [threshold](int value) { return value > threshold; });
    return filtered;
}

// Function to scale the data by a factor
std::vector<double> scaleData(const std::vector<int>& data, double scaleFactor) {
    std::vector<double> scaled;
    std::transform(data.begin(), data.end(), std::back_inserter(scaled),
                   [scaleFactor](int value) { return value * scaleFactor; });
    return scaled;
}

// Function to calculate average of the data
double calculateAverage(const std::vector<int>& data) {
    if (data.empty()) {
        return 0.0;
    }
    return static_cast<double>(std::accumulate(data.begin(), data.end(), 0)) / data.size();
}

// Unit test function
void runTests() {
    // Test filterData
    std::vector<int> testData = {1, 2, 3, 4, 5, 6};
    std::vector<int> filteredData = filterData(testData, 3);
    assert((filteredData == std::vector<int>{4, 5, 6}));

    // Test scaleData
    std::vector<double> scaledData = scaleData(testData, 2.0);
    std::vector<double> expectedScaledData = {2.0, 4.0, 6.0, 8.0, 10.0, 12.0};
    assert((scaledData == expectedScaledData));

    // Test calculateAverage
    double average = calculateAverage(testData);
    assert(average == 3.5);

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    // Generate large dataset
    const int N = 1000000;
    std::vector<int> data(N);
    std::iota(data.begin(), data.end(), 1); // Fill with 1, 2, ..., N

    // Data operations
    int threshold = 500000; // Example threshold for filtering
    std::vector<int> filteredData = filterData(data, threshold);
    
    double scaleFactor = 2.5; // Example scaling factor
    std::vector<double> scaledData = scaleData(filteredData, scaleFactor);
    
    double average = calculateAverage(filteredData);

    // Output results
    std::cout << "Number of filtered data points: " << filteredData.size() << std::endl;
    std::cout << "Average of filtered data: " << average << std::endl;

    // Run unit tests
    runTests();

    return 0;
}
