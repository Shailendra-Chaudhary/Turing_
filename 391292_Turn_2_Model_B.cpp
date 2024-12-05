#include <gtest/gtest.h>
#include "template_class.hpp" // Ensure this path is correct

// Basic tests for a template class
TEST(TemplateClassTest, DefaultConstructor) {
    TemplateClass<int> tc;
    EXPECT_EQ(tc.value(), 0);
}

TEST(TemplateClassTest, SetValue) {
    TemplateClass<int> tc;
    tc.setValue(42);
    EXPECT_EQ(tc.value(), 42);
}

// Add more tests as needed for other template types and functions

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
