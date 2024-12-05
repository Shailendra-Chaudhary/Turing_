#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>

// Template class that generates a mock class for any given interface
template <typename Interface>
class MockInterface : public Interface {
public:
    // Use macros to generate mock methods for the known virtual functions
    MOCK_METHOD(void, initialize, (), (override));
    MOCK_METHOD(void, shutdown, (), (override));
    MOCK_METHOD(int, performAction, (int), (override));
};

// Example interface
class DeviceInterface {
public:
    virtual ~DeviceInterface() = default;
    virtual void initialize() = 0;
    virtual void shutdown() = 0;
    virtual int performAction(int actionCode) = 0;
};

// Example class using the DeviceInterface
class Device : public DeviceInterface {
public:
    void initialize() override {
        // Actual implementation
        std::cout << "Initializing device..." << std::endl;
    }

    void shutdown() override {
        // Actual implementation
        std::cout << "Shutting down device..." << std::endl;
    }

    int performAction(int actionCode) override {
        // Simulated action
        return actionCode * 2;
    }
};

// Test using the mock class
TEST(MockInterfaceTest, TestDeviceInterface) {
    MockInterface<DeviceInterface> mockDevice;

    // Set up expectations
    EXPECT_CALL(mockDevice, initialize())
        .Times(1);
    
    EXPECT_CALL(mockDevice, shutdown())
        .Times(1);

    EXPECT_CALL(mockDevice, performAction(::testing::Gt(10)))
        .WillOnce(::testing::Return(42));

    // Use the mock object in place of the real one
    mockDevice.initialize();
    int result = mockDevice.performAction(20);
    EXPECT_EQ(result, 42);
    mockDevice.shutdown();
}

// Main function to run the tests
int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
