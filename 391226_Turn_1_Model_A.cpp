#include <gtest/gtest.h>
#include "event_dispatcher.h"

class MockEventHandler : public EventHandler {
public:
    MOCK_METHOD(void, HandleButtonClick, (), (override));
    MOCK_METHOD(void, HandleKeyPress, (), (override));
};

TEST(EventDispatcherTest, DispatchButtonClickEvent) {
    EventDispatcher dispatcher;
    MockEventHandler mockHandler;

    EXPECT_CALL(mockHandler, HandleButtonClick());
    EXPECT_CALL(mockHandler, HandleKeyPress()).Times(0);

    dispatcher.SetEventHandler(&mockHandler);
    Event event{Event::EventType::ButtonClick};
    dispatcher.DispatchEvent(event);
}

TEST(EventDispatcherTest, DispatchKeyPressEvent) {
    EventDispatcher dispatcher;
    MockEventHandler mockHandler;

    EXPECT_CALL(mockHandler, HandleButtonClick()).Times(0);
    EXPECT_CALL(mockHandler, HandleKeyPress());

    dispatcher.SetEventHandler(&mockHandler);
    Event event{Event::EventType::KeyPress};
    dispatcher.DispatchEvent(event);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
