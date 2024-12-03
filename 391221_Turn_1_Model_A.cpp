// main.cpp
#include <gtest/gtest.h>
#include <string>

// Class to be tested
class MathOperations {
public:
    int add(int a, int b) const {
        return a + b;
    }

    int subtract(int a, int b) const {
        return a - b;
    }
};

// Test fixture for MathOperations
class MathOperationsTest : public ::testing::Test {
protected:
    // Setup logic that runs before each test
    void SetUp() override {
        // Initialize any necessary resources here
    }

    // Teardown logic that runs after each test
    void TearDown() override {
        // Clean up any resources here
    }

    // Helper function to manage test data
    std::string generateTestData(int a, int b, int expected) {
        return std::string("a=") + std::to_string(a) + ", b=" + std::to_string(b) + ", expected=" + std::to_string(expected);
    }

    // Access the MathOperations object
    MathOperations mathOps;
};

// Test cases for MathOperations::add
TEST_F(MathOperationsTest, AddPositiveNumbers) {
    EXPECT_EQ(mathOps.add(3, 5), 8);
}

TEST_F(MathOperationsTest, AddZero) {
    EXPECT_EQ(mathOps.add(0, 7), 7);
}

TEST_F(MathOperationsTest, AddNegativeNumbers) {
    EXPECT_EQ(mathOps.add(-2, -3), -5);
}

// Test cases for MathOperations::subtract
TEST_F(MathOperationsTest, SubtractPositiveNumbers) {
    EXPECT_EQ(mathOps.subtract(8, 3), 5);
}

TEST_F(MathOperationsTest, SubtractZero) {
    EXPECT_EQ(mathOps.subtract(7, 0), 7);
}

TEST_F(MathOperationsTest, SubtractNegativeNumbers) {
    EXPECT_EQ(mathOps.subtract(-5, -2), -3);
}

// Parameterized test for MathOperations::add
TEST_P(MathOperationsTest, ParameterizedAddition) {
    int a = GetParam().first;
    int b = GetParam().second;
    int expected = GetParam().third;
    EXPECT_EQ(mathOps.add(a, b), expected);
}

INSTANTIATE_TEST_CASE_P(
    MathAdditionTests,
    MathOperationsTest,
    ::testing::Values(
        std::make_tuple(3, 5, 8),
        std::make_tuple(0, 7, 7),
        std::make_tuple(-2, -3, -5),
        std::make_tuple(10, 0, 10),
        std::make_tuple(-10, 0, -10)
    )
);

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
