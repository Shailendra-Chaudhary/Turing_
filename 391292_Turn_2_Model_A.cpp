#include <gtest/gtest.h>
#include "template_class.hpp"  // Include your class

TEST(TemplateClassTest, TypeSafety) {
    // Test cases involving your template class
    TemplateClass<int> tc_int;
    tc_int.setValue(42);
    EXPECT_EQ(tc_int.value(), 42);

    TemplateClass<double> tc_double;
    tc_double.setValue(3.14);
    EXPECT_EQ(tc_double.value(), 3.14);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
