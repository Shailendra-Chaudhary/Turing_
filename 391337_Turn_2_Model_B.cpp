#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <random>
#include <functional>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <catch2/catch.hpp>

// Function to filter values greater than a threshold using boost::range::filtered
std::vector<int> filterData(const std::vector<int>& data, int threshold) {
    std::vector<int> filteredData;
    filteredData.assign(data | boost::adaptors::filtered([threshold](int value) { return value > threshold; }));
    return filteredData;
}

// Function to scale the data by a factor using boost::range::transformed and std::vector::assign
std::vector<double> scaleData(const std::vector<int>& data, double scaleFactor) {
    std::vector<double> scaledData;
    scaledData.assign(data | boost::adaptors::transformed([scaleFactor](int value) { return value * scaleFactor; }));
    return scaledData;
}

// Function to calculate average of the data in-place
double calculateAverage(std::vector<int>& data) {
    if (data.empty()) {
        return 0.0;
    }
    std::accumulate(data.begin(), data.end(), 0, std::plus<>());
    return static_cast<double>(data[0]) / data.size();
}

TEST_CASE("Test filterData", "[filterData]") {
    SECTION("Empty data vector") {
        std::vector<int> testData{};
        std::vector<int> filteredData = filterData(testData, 3);
        REQUIRE(filteredData.empty());
    }
    SECTION("Single element data vector") {
        std::vector<int> testData{4};
        std::vector<int> filteredData = filterData(testData, 3);
        REQUIRE(filteredData == std::vector<int>{4});
    }
    SECTION("Multiple element data vector") {
        std::vector<int> testData = {1, 2, 3, 4, 5, 6};
        std::vector<int> filteredData = filterData(testData, 3);
        REQUIRE(filteredData == std::vector<int>{4, 5, 6});
    }
}

TEST_CASE("Test scaleData", "[scaleData]") {
    SECTION("Empty data vector") {
        std::vector<int> testData{};
        std::vector<double> scaledData = scaleData(testData, 2.0);
        REQUIRE(scaledData.empty());
    }
    SECTION("Single element data vector") {
        std::vector<int> testData{4};
        std::vector<double> scaledData = scaleData(testData, 2.0);
        REQUIRE(scaledData == std::vector<double>{8.0});
    }
    SECTION("Multiple element data vector") {
        std::vector<int> testData = {1, 2, 3, 4, 5};
        std::vector<double> scaledData = scaleData(testData, 2.0);
        REQUIRE(scaledData == std::vector<double>{2.0, 4.0, 6.0, 8.0, 10.0});
    }
}

TEST_CASE("Test calculateAverage", "[calculateAverage]") {
    SECTION("Empty data vector") {
        std::vector<int> testData{};
        double average = calculateAverage(testData);
        REQUIRE(average == 0.0);
    }
    SECTION("Single element data vector") {
