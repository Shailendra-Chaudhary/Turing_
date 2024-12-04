#include <gtest/gtest.h>
#include "my_code.h"

TEST(MyClassTest, AddTest) {
    MyClass myClass;
    EXPECT_EQ(myClass.add(1, 1), 2);
    EXPECT_EQ(myClass.add(-1, 1), 0);
    EXPECT_EQ(myClass.add(-1, -1), -2);
}

TEST(MyClassTest, MultiplyTest) {
    MyClass myClass;
    EXPECT_EQ(myClass.multiply(2, 3), 6);
    EXPECT_EQ(myClass.multiply(-1, 3), -3);
    EXPECT_EQ(myClass.multiply(0, 5), 0);
}
