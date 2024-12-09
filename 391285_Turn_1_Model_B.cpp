#include "gtest/gtest.h"
#include "feature.h"

// Test when FEATURE_X_ENABLED is defined
TEST(FeatureTest, FeatureXEnabled) {
    // Simulate FEATURE_X_ENABLED being defined
    #define FEATURE_X_ENABLED
    EXPECT_EQ(getFeatureValue(), 42);
    #undef FEATURE_X_ENABLED
}

// Test when FEATURE_X_ENABLED is not defined
TEST(FeatureTest, FeatureXDisabled) {
    // Ensure FEATURE_X_ENABLED is not defined
    #undef FEATURE_X_ENABLED
    EXPECT_EQ(getFeatureValue(), 0);
}

// Main function to run the tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
