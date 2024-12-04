// example.cpp

#include <iostream>

int add(int a, int b) {
    return a + b;
}
// example_test.cpp

 // Include the function to test
#include <gtest/gtest.h>

// Test case for the add function
TEST(AdditionTest, AddsTwoNumbers) {
    EXPECT_EQ(add(2, 3), 5);
}

TEST(AdditionTest, AddsZero) {
    EXPECT_EQ(add(0, 0), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
