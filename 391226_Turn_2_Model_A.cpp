#include "event_dispatcher.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::StrictMock;

class MockEventHandler : public StrictMock<Event> {
public:
    MOCK_METHOD(void, handleEvent, (const Event&));
};

TEST(EventDispatcherTest, HandlerReceivesEvent) {
    EventDispatcher dispatcher;
    MockEventHandler handler;

    // Register the handler for the button_click event
    dispatcher.registerHandler("button_click", [&](const Event& event) {
        handler.handleEvent(event);
    });

    // Dispatch a button_click event
    ButtonClickEvent buttonClickEvent("Submit");
    dispatcher.dispatch(buttonClickEvent);

    // Verify that the handler received the event
    EXPECT_CALL(handler, handleEvent(testing::_)).Times(1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
