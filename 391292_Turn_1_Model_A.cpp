#include <gtest/gtest.h>
#include "template_class.hpp" // Adjust the include path as necessary

TEST(TemplateClassTest, BasicFunctionality) {
    TemplateClass<int> tc;
    EXPECT_EQ(tc.value(), 0);
    tc.setValue(42);
    EXPECT_EQ(tc.value(), 42);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
