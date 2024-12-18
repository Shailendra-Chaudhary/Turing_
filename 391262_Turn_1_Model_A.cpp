#include <gtest/gtest.h>

int add(int a, int b) {
    return a + b;
}

TEST(ArithmeticTest, AddTwoNumbers) {
    EXPECT_EQ(add(1, 2), 3);
}

TEST(ArithmeticTest, AddZero) {
    EXPECT_EQ(add(0, 0), 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
