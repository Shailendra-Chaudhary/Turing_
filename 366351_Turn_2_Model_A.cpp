#include <iostream>
#include <future>
#include <thread>
#include <vector>
#include <stdexcept>
#include "gtest/gtest.h"

// Function to simulate asynchronous addition with error handling
std::future<int> asyncAdd(int a, int b) {
    auto promise = std::make_shared<std::promise<int>>();
    std::thread([a, b, promise]() {
        if (a < 0 || b < 0) {
            throw std::invalid_argument("Negative input detected");
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Simulate work
        promise->set_value(a + b);
    }).detach();
    return promise->get_future();
}

// Test case for synchronous future comparison
TEST(AsyncTest, AsyncAddSuccess) {
    ::testing::Future<int> result = asyncAdd(3, 5);
    int expectedResult = 3 + 5;
    int actualResult = result.get();
    EXPECT_EQ(actualResult, expectedResult);
}

// Test case for synchronous future comparison with timeout
TEST(AsyncTest, AsyncAddTimeout) {
    ::testing::Future<int> result = asyncAdd(3, 5);
    int expectedResult = 3 + 5;
    int actualResult = result.get();
    EXPECT_EQ(actualResult, expectedResult);
}

// Test case for asynchronous operation throwing an exception
TEST(AsyncTest, AsyncAddException) {
    ::testing::Future<int> result = asyncAdd(-3, 5);
    EXPECT_THROW(result.get(), std::invalid_argument);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
