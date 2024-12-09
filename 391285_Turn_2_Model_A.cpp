#include "gtest/gtest.h"
#include "variant_example.h"

// Test for C++17 or later compiler
TEST(VariantTestCpp17, IntBehavior) {
#if __cplusplus >= 201703L
    VariantType variant = getVariant();
    ASSERT_EQ(getIntFromVariant(variant), 42);
    EXPECT_THROW(getStringFromVariant(variant), std::bad_variant_access);
#endif
}

// Simulate a C++11 compiler environment (if not already in C++11 or earlier)
// In practice, you would need to set up the compiler appropriately for C++11 or earlier.
// Below example simulates using conditional compilation directives
TEST(VariantTestCpp11, IntBehavior) {
#if !defined(__cplusplus) || __cplusplus < 201402L
    #define __cplusplus 201103L  // Simulating C++11
    VariantType variant = getVariant();
    ASSERT_EQ(getIntFromVariant(variant), 42);
    EXPECT_THROW(getStringFromVariant(variant), std::bad_variant_access);
    #undef __cplusplus
#endif
}

// Main function to run the tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
