#include <gmock/gmock.h>

template <typename T>
class AutoMock : public T {
public:
    using T::T; // Inherit constructors

    MOCK_METHOD0(Destructor, void()); // Mock the virtual destructor

    // Use template specialization or variadic templates to handle other virtual methods
    // For simplicity, let's assume we only need to mock the destructor for this example
};

// Example class to be mocked
class ExampleClass {
public:
    virtual ~ExampleClass() = default;

    virtual int DoSomething(int x) = 0;
    virtual void DoAnotherThing(const std::string& s) = 0;
};

// Test case
TEST(AutoMockTest, CanMockExampleClass) {
    AutoMock<ExampleClass> mock;

    EXPECT_CALL(mock, DoSomething(10))
        .WillOnce(Return(20));

    EXPECT_CALL(mock, DoAnotherThing("Hello"))
        .WillOnce(::testing::DoNothing());

    // Call the mocked methods
    int result = mock.DoSomething(10);
    mock.DoAnotherThing("Hello");

    EXPECT_EQ(result, 20);

    // Explicitly call the destructor to ensure it's mocked as well
    mock.Destructor();
    EXPECT_CALL(mock, Destructor())
        .Times(0); // The destructor should not be called again
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
