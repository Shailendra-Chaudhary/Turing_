// feature.h

#pragma once

#ifdef FEATURE_FLAG
inline std::string getFeatureValue() {
    return "Feature enabled";
}
#else
inline std::string getFeatureValue() {
    return "Feature disabled";
}
#endif
// test_feature.cpp

#include <gtest/gtest.h>

// Include the feature header multiple times with different flags.
#undef FEATURE_FLAG

#include "feature.h"

TEST(FeatureTest, TestFeatureDisabled) {
    EXPECT_EQ(getFeatureValue(), "Feature disabled");
}

#define FEATURE_FLAG 1
#include "feature.h"

TEST(FeatureTest, TestFeatureEnabled) {
    EXPECT_EQ(getFeatureValue(), "Feature enabled");
}

#undef FEATURE_FLAG

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
