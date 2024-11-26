#include <iostream>
#include <future>
#include <thread>
#include <vector>
#include "gtest/gtest.h"

// A simple asynchronous operation that adds two numbers
std::future<int> asyncAdd(int a, int b) {
    auto promise = std::make_shared<std::promise<int>>();
    std::thread([a, b, promise]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Simulate some work
        promise->set_value(a + b);
    }).detach();
    return promise->get_future();
}

// Test case for the asynchronous operation
TEST(AsyncTest, AsyncAdd) {
    std::future<int> result = asyncAdd(3, 5);
    // Wait for the future to complete
    int expectedResult = 3 + 5;
    int actualResult = result.get();
    EXPECT_EQ(actualResult, expectedResult) << "Expected: " << expectedResult << " but got: " << actualResult;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
