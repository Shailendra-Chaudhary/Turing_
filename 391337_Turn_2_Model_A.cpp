#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <random>
#include <cassert>
#include <chrono>

// Function to generate large dataset
std::vector<int> generateDataset(size_t size) {
    std::vector<int> data(size);
    std::generate(data.begin(), data.end(), [n = 0]() mutable { return n++ % 100; }); // Generate numbers 0 to 99
    return data;
}

// Function to filter values above a threshold
std::vector<int> filterData(const std::vector<int>& data, int threshold) {
    std::vector<int> filtered;
    std::copy_if(data.begin(), data.end(), std::back_inserter(filtered),
                 [threshold](int value) { return value > threshold; });
    return filtered;
}

// Function to normalize the data between 0 and 1
std::vector<double> normalizeData(const std::vector<int>& data) {
    double maxVal = *std::max_element(data.begin(), data.end());
    double minVal = *std::min_element(data.begin(), data.end());

    std::vector<double> normalized;
    std::transform(data.begin(), data.end(), std::back_inserter(normalized),
                   [maxVal, minVal](int value) { return (value - minVal) / (maxVal - minVal); });
    return normalized;
}

// Function to calculate the maximum and minimum of the dataset
std::pair<int, int> calculateMinMax(const std::vector<int>& data) {
    auto result = std::minmax_element(data.begin(), data.end());
    return { *result.first, *result.second };
}

// Unit test function
void runTests() {
    // Test for generating dataset
    auto testData = generateDataset(100);
    assert(testData.size() == 100);

    // Test for filterData
    auto filteredData = filterData(testData, 50);
    assert(std::all_of(filteredData.begin(), filteredData.end(), [](int value) { return value > 50; }));

    // Test for normalizeData
    auto normalizedData = normalizeData(testData);
    assert(normalizedData.size() == testData.size());
    assert(std::all_of(normalizedData.begin(), normalizedData.end(), [](double value) { return value >= 0.0 && value <= 1.0; }));

    // Test for calculateMinMax
    auto [minVal, maxVal] = calculateMinMax(testData);
    assert(minVal >= 0 && maxVal < 100);

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    size_t N = 1000000; // Size of the dataset
    auto data = generateDataset(N);

    // Start the timer for performance measurement
    auto start = std::chrono::high_resolution_clock::now();

    // Data operations
    int threshold = 50;
    auto filteredData = filterData(data, threshold);
    auto normalizedData = normalizeData(filteredData);
    auto [minVal, maxVal] = calculateMinMax(filteredData);

    // End the timer and calculate duration
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Output results
    std::cout << "Filtered data size: " << filteredData.size() << std::endl;
    std::cout << "Min value: " << minVal << ", Max value: " << maxVal << std::endl;
    std::cout << "Time taken for processing: " << duration.count() << " seconds" << std::endl;

    // Run unit tests
    runTests();

    return 0;
}
