// calculator.h
#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator {
public:
    int add(int a, int b);
    int subtract(int a, int b);
    double divide(int a, int b);
    // More operations can be added
};

#endif // CALCULATOR_H

// calculator.cpp
#include "calculator.h"
#include <stdexcept>

int Calculator::add(int a, int b) {
    return a + b;
}

int Calculator::subtract(int a, int b) {
    return a - b;
}

double Calculator::divide(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return static_cast<double>(a) / b;
}

// tests/calculator_test.cpp
#include <gtest/gtest.h>
#include "calculator.h"

namespace calculator_test {

// Test fixture for the Calculator class
class CalculatorTest : public ::testing::Test {
protected:
    Calculator calculator;

    void SetUp() override {
        // If there's any common setup for your tests, it goes here.
        // For example, initializing complex structures.
    }

    void TearDown() override {
        // Any cleanup logic after each test goes here.
    }
};

TEST_F(CalculatorTest, AddTest) {
    EXPECT_EQ(calculator.add(3, 4), 7);
    EXPECT_EQ(calculator.add(-1, -1), -2);
    EXPECT_EQ(calculator.add(-1, 1), 0);
}

TEST_F(CalculatorTest, SubtractTest) {
    EXPECT_EQ(calculator.subtract(10, 5), 5);
    EXPECT_EQ(calculator.subtract(-5, -5), 0);
    EXPECT_EQ(calculator.subtract(0, 5), -5);
}

TEST_F(CalculatorTest, DivideTest) {
    EXPECT_DOUBLE_EQ(calculator.divide(10, 2), 5.0);
    EXPECT_THROW(calculator.divide(1, 0), std::invalid_argument);
}

} // namespace calculator_test

// main.cpp (the test runner)
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
