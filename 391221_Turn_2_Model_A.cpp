// math_utils.h
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <vector>

int add(int a, int b);
int subtract(int a, int b);

// Helper function for adding a vector of numbers
std::vector<int> addVector(const std::vector<int>& numbers);

#endif // MATH_UTILS_H

// math_utils.cpp
#include "math_utils.h"

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

std::vector<int> addVector(const std::vector<int>& numbers) {
    std::vector<int> result;
    for (int i = 0; i < numbers.size() - 1; ++i) {
        result.push_back(add(numbers[i], numbers[i + 1]));
    }
    return result;
}

// tests/math_utils_test.cpp
#include <gtest/gtest.h>
#include "math_utils.h"

namespace math_utils_test {

// Base test fixture for basic arithmetic operations
class MathUtilsBaseTest : public ::testing::Test {
protected:
    // Setup code goes here
    void SetUp() override {
        // Example of setting up shared data
        positive_pair = {1, 2};
        negative_pair = {-1, -2};
        zero_pair = {0, 0};
    }

    // Teardown code goes here
    void TearDown() override {
        // Example of cleaning up resources
    }

    std::pair<int, int> positive_pair;
    std::pair<int, int> negative_pair;
    std::pair<int, int> zero_pair;
};

// Test fixture derived from MathUtilsBaseTest for vector addition
class VectorAdditionTest : public MathUtilsBaseTest {};

TEST_F(MathUtilsBaseTest, AddTest) {
    EXPECT_EQ(add(positive_pair.first, positive_pair.second), 3);
    EXPECT_EQ(add(negative_pair.first, negative_pair.second), -4);
    EXPECT_EQ(add(zero_pair.first, zero_pair.second), 0);
}

TEST_F(MathUtilsBaseTest, SubtractTest) {
    EXPECT_EQ(subtract(positive_pair.first, positive_pair.second), -1);
    EXPECT_EQ(subtract(negative_pair.first, negative_pair.second), 1);
    EXPECT_EQ(subtract(zero_pair.first, zero_pair.second), 0);
}

// Parameterized test for vector addition
TEST_P(VectorAdditionTest, AddVectorTest) {
    const std::vector<int>& numbers = GetParam();
    const std::vector<int> expected_result = {1, 3, 6};
    std::vector<int> result = addVector(numbers);
    EXPECT_EQ(result, expected_result);
}

INSTANTIATE_TEST_SUITE_P(VectorAddition, VectorAdditionTest,
                         ::testing::Values(std::vector<int>{1, 2, 3},
                                           std::vector<int>{-1, -2, -3},
                                           std::vector<int>{0, 0, 0}));

} // namespace math_utils_test

// main.cpp (the test runner)
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
