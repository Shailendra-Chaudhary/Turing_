using testing::_;
using testing::Action;
using testing::Return;
using testing::SaveArg;

TEST(AsyncTest, AsyncAdd_UsingAction) {
    std::promise<int> promise;
    std::future<int> future = promise.get_future();

    EXPECT_CALL(promise, set_value(42)).WillOnce(SaveArg<0>());
    asyncAdd(3, 5);

    int expectedResult = 42;
    int actualResult;
    EXPECT_TRUE(future.wait_for(std::chrono::seconds(1)) == std::future_status::ready);
    actualResult = future.get();

    EXPECT_EQ(actualResult, expectedResult);
}
