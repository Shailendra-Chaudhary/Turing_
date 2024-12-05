// feature.h

#pragma once

#include <string>

inline std::string getFeatureStatus() {
#ifdef USE_ADVANCED_FEATURE
    return "Advanced Feature Active";
#else
    return "Basic Feature Active";
#endif
}
// test_feature.cpp

#include <gtest/gtest.h>

// First, test without the macro defined.
#undef USE_ADVANCED_FEATURE
#include "feature.h"

TEST(FeatureTest, BasicFeature) {
    EXPECT_EQ(getFeatureStatus(), "Basic Feature Active");
}

// Now, define the macro and test the advanced feature.
#define USE_ADVANCED_FEATURE
#include "feature.h"

TEST(FeatureTest, AdvancedFeature) {
    EXPECT_EQ(getFeatureStatus(), "Advanced Feature Active");
}

#undef USE_ADVANCED_FEATURE // Clean up

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
