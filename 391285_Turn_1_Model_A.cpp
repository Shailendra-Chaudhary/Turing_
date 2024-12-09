#include <gtest/gtest.h>
#include "feature.h" // Replace with your header file

// Helper function to simulate compiler conditions
void TestWithCompilerMacro(bool gcc, bool msvc, const std::string& expectedOutput) {
    // Simulate GCC macro
    #ifdef __GNUC__
    #undef __GNUC__
    #endif
    #if gcc
    #define __GNUC__
    #endif

    // Simulate MSVC macro
    #ifdef _MSC_VER
    #undef _MSC_VER
    #endif
    #if msvc
    #define _MSC_VER
    #endif

    Feature feature;
    std::ostringstream oss;
    std::streambuf* orig = std::cout.rdbuf(oss.rdbuf());

    feature.doSomething();
    std::cout.rdbuf(orig);

    std::string output = oss.str();
    ASSERT_EQ(output, expectedOutput) << "Expected: " << expectedOutput << "; Got: " << output;
}

TEST(FeatureTest, GCC_Compiler) {
    TestWithCompilerMacro(true, false, "Running on GCC.\n");
}

TEST(FeatureTest, MSVC_Compiler) {
    TestWithCompilerMacro(false, true, "Running on MSVC.\n");
}

TEST(FeatureTest, Unknown_Compiler) {
    TestWithCompilerMacro(false, false, "Unknown compiler.\n");
}
