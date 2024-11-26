
#include <gtest/gtest.h>
#include <future>
#include <thread>
#include <random>
#include <chrono>

// Long-running asynchronous function (simulating a complex operation)
int LongRunningAsyncOperation() {
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Simulate random error or success
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    int randomNumber = dis(gen);
    
    if (randomNumber == 0) {
        // Throw an exception to simulate error
        throw std::runtime_error("Async operation failed!");
    } else {
        return 42; // Return a successful result
    }
}

TEST(AsyncTest, ShouldReturnExpectedResult) {
    // Use a promise to capture the result asynchronously
    std::promise<int> promise;
    auto future = promise.get_future();

    // Run the asynchronous operation in a separate thread
    std::thread asyncThread([&promise]() {
        try {
            int result = LongRunningAsyncOperation();
            promise.set_value(result);
        } catch (const std::exception& e) {
            promise.set_exception(std::current_exception());
        }
    });

    // Assert that the future has a value available within a reasonable timeout
    bool succeeded = false;
    try {
        int result = future.get();  // This will block until the result is ready
        succeeded = true;
        EXPECT_EQ(result, 42); // Assert the expected result
    } catch (const std::runtime_error& e) {
        succeeded = false;
        // Handle unexpected exceptions gracefully
        EXPECT_EQ(e.what(), std::string("Async operation failed!"));
    }

    // Wait for the asynchronous thread to finish
    asyncThread.join();

    ASSERT_TRUE(succeeded) << "Async operation did not complete successfully";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}  
