#include <gmock/gmock.h>

template <typename T>
class AutoMock : public T {
public:
    using T::T; // Inherit constructors

    // Template to automatically mock each virtual method
    template <typename Ret, typename... Args>
    MOCK_METHOD(Ret, virtualMethod, (Args...));
};
#include "gtest/gtest.h"

TEST(AutoMockTest, CanMockBase) {
    AutoMock<Base> baseMock;

    EXPECT_CALL(baseMock, add(5, 3))
        .WillOnce(Return(8));

    // Call the mocked method
    int result = baseMock.add(5, 3);
    EXPECT_EQ(result, 8);
}

TEST(AutoMockTest, CanMockDerived) {
    AutoMock<Derived> derivedMock;

    EXPECT_CALL(derivedMock, add(5, 3))
        .WillOnce(Return(8));

    EXPECT_CALL(derivedMock, multiply(4, 6))
        .WillOnce(Return(24));

    // Call the mocked methods
    int addResult = derivedMock.add(5, 3);
    int multiplyResult = derivedMock.multiply(4, 6);
    EXPECT_EQ(addResult, 8);
    EXPECT_EQ(multiplyResult, 24);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
