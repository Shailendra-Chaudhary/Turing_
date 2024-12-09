#include <gtest/gtest.h>

// Sample template function
template <typename T>
T add(T a, T b) {
    return a + b;
}

// Test case for the template function
TEST(AdditionTest, Integers) {
    EXPECT_EQ(add<int>(1, 2), 3);
}

TEST(AdditionTest, Floats) {
    EXPECT_FLOAT_EQ(add<float>(1.5, 2.5), 4.0);
}
