// math_utils.h
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

int add(int a, int b);
int subtract(int a, int b);

#endif // MATH_UTILS_H

// math_utils.cpp
#include "math_utils.h"

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

// tests/math_utils_test.cpp
#include <gtest/gtest.h>
#include "math_utils.h"

namespace math_utils_test {

// Test fixture for math utility functions
class MathUtilsTest : public ::testing::Test {
protected:
    // Setup code (if needed) goes here
    void SetUp() override {
        // Can initialize variables, allocate resources, etc.
    }

    // Teardown code (if needed) goes here
    void TearDown() override {
        // Can deallocate resources, reset states, etc.
    }
};

// Test cases using the fixture
TEST_F(MathUtilsTest, AddTest) {
    EXPECT_EQ(add(1, 2), 3);
    EXPECT_EQ(add(-1, -1), -2);
    EXPECT_EQ(add(-1, 1), 0);
}

TEST_F(MathUtilsTest, SubtractTest) {
    EXPECT_EQ(subtract(5, 3), 2);
    EXPECT_EQ(subtract(2, 3), -1);
    EXPECT_EQ(subtract(-1, -1), 0);
}

} // namespace math_utils_test

// main.cpp (the test runner)
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
