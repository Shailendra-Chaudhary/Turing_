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
#include "feature.h"

TEST(FeatureTest, TestFeatureDisabled) {
    #undef FEATURE_FLAG
    EXPECT_EQ(getFeatureValue(), "Feature disabled");
    #ifdef FEATURE_FLAG
    #error FEATURE_FLAG should not be defined here
    #endif
}

TEST(FeatureTest, TestFeatureEnabled) {
    #define FEATURE_FLAG
    EXPECT_EQ(getFeatureValue(), "Feature enabled");
    #ifndef FEATURE_FLAG
    #error FEATURE_FLAG should be defined here
    #endif
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
