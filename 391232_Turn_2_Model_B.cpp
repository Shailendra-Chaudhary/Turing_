#include <gtest/gtest.h>
#include "calculator.h"

TEST(CalculatorTest, AddsTwoNumbers) {
    Calculator calc;
    EXPECT_EQ(calc.add(3, 4), 7);
}

TEST(CalculatorTest, SubtractsTwoNumbers) {
    Calculator calc;
    EXPECT_EQ(calc.subtract(10, 4), 6);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
