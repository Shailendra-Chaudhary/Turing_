#include <gtest/gtest.h>

// Example function to test
int add(int a, int b) {
    return a + b;
}

TEST(AdditionTest, AddsTwoNumbers) {
    EXPECT_EQ(add(1, 1), 2);
    EXPECT_EQ(add(0, 0), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}