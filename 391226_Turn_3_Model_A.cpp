#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <functional>
#include <vector>

// Define an event interface
class Event {
public:
    virtual ~Event() {}
};

// Define a specific event type
class ButtonClickEvent : public Event {
public:
    ButtonClickEvent(const std::string& buttonId) : buttonId(buttonId) {}
    std::string buttonId;
};

// Define an interface for event handlers
class EventHandler {
public:
    virtual ~EventHandler() {}
    virtual void handleEvent(const Event& event) = 0;
};

// Define the event dispatcher
class EventDispatcher {
public:
    void addHandler(const std::string& eventType, const std::shared_ptr<EventHandler>& handler) {
        handlers[eventType].push_back(handler);
    }

    void dispatchEvent(const std::string& eventType, const Event& event) {
        for (const auto& handler : handlers.at(eventType)) {
            handler->handleEvent(event);
        }
    }

private:
    std::unordered_map<std::string, std::vector<std::shared_ptr<EventHandler>>> handlers;
};

// Test class
class EventDispatcherTest : public ::testing::Test {
protected:
    EventDispatcher dispatcher;
};

// Mock the EventHandler to test interactions
class MockEventHandler : public EventHandler {
public:
    MOCK_METHOD(void, handleEvent, (const Event&), ());
};

// Test: Ensure a ButtonClickEvent is dispatched correctly
TEST_F(EventDispatcherTest, ButtonClickEventDispatched) {
    // Create a mock event handler
    auto mockHandler = std::make_shared<MockEventHandler>();
    
    // Set an expectation that handleEvent is called once
    EXPECT_CALL(*mockHandler, handleEvent(_))
        .Times(1)
        .WillOnce([&](const Event& event) {
            ButtonClickEvent* clickEvent = dynamic_cast<ButtonClickEvent*>(&event);
            ASSERT_TRUE(clickEvent != nullptr) << "Expected a ButtonClickEvent";
            EXPECT_EQ(clickEvent->buttonId, "SubmitButton");
        });

    // Add the mock handler to the dispatcher for "ButtonClick" events
    dispatcher.addHandler("ButtonClick", mockHandler);

    // Dispatch a ButtonClickEvent
    ButtonClickEvent buttonEvent("SubmitButton");
    dispatcher.dispatchEvent("ButtonClick", buttonEvent);

    // Verify the expectation was satisfied
    ::testing::AssertNoFatalFailures();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
