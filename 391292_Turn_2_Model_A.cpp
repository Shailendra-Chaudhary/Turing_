// template_class.h
template <typename T>
class TemplateClass {
public:
    T square(T x) {
        return x * x;
    }
};

// template_class.cpp
#include "template_class.h"

// template_tests.cpp
#include "template_class.h"
#include <gtest/gtest.h>

TEST(TemplateClassTest, SquareInt) {
    TemplateClass<int> intClass;
    EXPECT_EQ(intClass.square(3), 9);
}

TEST(TemplateClassTest, SquareDouble) {
    TemplateClass<double> doubleClass;
    EXPECT_NEAR(doubleClass.square(3.0), 9.0, 0.0001);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
