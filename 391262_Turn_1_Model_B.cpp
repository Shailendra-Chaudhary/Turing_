// my_math.h
#ifndef MY_MATH_H
#define MY_MATH_H

int add(int a, int b);
int subtract(int a, int b);

#endif // MY_MATH_H

// my_math.cpp
#include "my_math.h"

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

// test_my_math.cpp
#include "gtest/gtest.h"
#include "my_math.h"

TEST(MyMathTest, AddTest) {
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_EQ(add(-1, 1), 0);
}

TEST(MyMathTest, SubtractTest) {
    EXPECT_EQ(subtract(5, 3), 2);
    EXPECT_EQ(subtract(2, 2), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
