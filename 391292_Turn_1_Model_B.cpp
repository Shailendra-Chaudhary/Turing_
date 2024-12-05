#include <gtest/gtest.h>

// Example template function you want to test
template<typename T>
T add(T a, T b) {
    return a + b;
}

// Test case for the 'add' function
TEST(AdditionTest, HandlesIntegers) {
    EXPECT_EQ(add(1, 1), 2);
}

TEST(AdditionTest, HandlesDoubles) {
    EXPECT_DOUBLE_EQ(add(1.5, 1.5), 3.0);
}

// Add more test cases as needed
