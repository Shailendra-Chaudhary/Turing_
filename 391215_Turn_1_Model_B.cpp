// Legacy component (possibly not test-friendly)
class Calculator {
public:
    int Add(int a, int b) { return a + b; }
    int Subtract(int a, int b) { return a - b; }
    // Complex legacy method
    int Multiply(int a, int b) { return a * b; }
    // More methods...
};
#include <gtest/gtest.h>
#include "Calculator.h"  // Include the legacy component's header

// Test fixture for Calculator
class CalculatorTest : public ::testing::Test {
protected:
    Calculator calculator;  // Create an instance of the Calculator
};

// Test case for Add function
TEST_F(CalculatorTest, TestAdd) {
    EXPECT_EQ(calculator.Add(10, 5), 15);
    EXPECT_EQ(calculator.Add(-1, 1), 0);
    EXPECT_EQ(calculator.Add(0, 0), 0);
}

// Test case for Subtract function
TEST_F(CalculatorTest, TestSubtract) {
    EXPECT_EQ(calculator.Subtract(10, 5), 5);
    EXPECT_EQ(calculator.Subtract(-1, -1), 0);
    EXPECT_EQ(calculator.Subtract(0, 5), -5);
}

// Test case for Multiply function
TEST_F(CalculatorTest, TestMultiply) {
    EXPECT_EQ(calculator.Multiply(10, 5), 50);
    EXPECT_EQ(calculator.Multiply(-1, 1), -1);
    EXPECT_EQ(calculator.Multiply(0, 5), 0);
}

// More tests as needed...

// Main function to run tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
