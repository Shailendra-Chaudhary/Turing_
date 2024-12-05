// feature_toggle.h
#ifndef FEATURE_TOGGLE_H
#define FEATURE_TOGGLE_H

#include <string>

std::string processData(const std::string& input);

#endif  // FEATURE_TOGGLE_H
// feature_toggle.cpp
#include "feature_toggle.h"

#ifdef ENABLE_FEATURE
std::string processData(const std::string& input) {
    return "Processed with Feature Enabled: " + input;
}
#else
std::string processData(const std::string& input) {
    return "Processed without Feature: " + input;
}
#endif
// feature_toggle_test.cpp
#include "gtest/gtest.h"
#include "feature_toggle.h"

#define TEST_MACRO_ENABLED \
    do {                    \
        _Pragma("push_macro(\"ENABLE_FEATURE\")") \
        _Pragma("define ENABLE_FEATURE 1") \
        _Pragma("pop_macro(\"ENABLE_FEATURE\")") \
    } while (0)

TEST(FeatureToggleTest, FeatureEnabled) {
    TEST_MACRO_ENABLED;
    std::string input = "Test Data";
    std::string expectedOutput = "Processed with Feature Enabled: Test Data";
    EXPECT_EQ(expectedOutput, processData(input));
}

TEST(FeatureToggleTest, FeatureDisabled) {
    std::string input = "Test Data";
    std::string expectedOutput = "Processed without Feature: Test Data";
    EXPECT_EQ(expectedOutput, processData(input));
}
