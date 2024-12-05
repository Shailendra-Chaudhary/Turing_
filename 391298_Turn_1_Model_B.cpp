#include <gtest/gtest.h>

// Sample interface for demonstration
struct SampleInterface {
    virtual int Compute(int x, int y) = 0;
    virtual void Log(const std::string& message) = 0;
};

// Test case demonstrating the usage
class SampleTest : public ::testing::Test {
protected:
    // Create mock objects for integer-returning and void-returning functions
    FlexibleMock<int, int, int> computeMock;
    FlexibleMock<void, const std::string&> logMock;
};

TEST_F(SampleTest, ComputeTest) {
    SampleInterface* mockInterface = &computeMock;

    EXPECT_CALL(computeMock, Invoke(3, 4))
        .WillOnce(::testing::Return(7));

    EXPECT_EQ(mockInterface->Compute(3, 4), 7);
}

TEST_F(SampleTest, LogTest) {
    SampleInterface* mockInterface = &logMock;

    EXPECT_CALL(logMock, Invoke("Hello World"));

    mockInterface->Log("Hello World");
}
