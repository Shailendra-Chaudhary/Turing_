#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>
#include <iostream>

// Event system simulation
class Event {
public:
    virtual ~Event() {}
};

class ButtonClickEvent : public Event {
public:
    explicit ButtonClickEvent(const std::string& buttonName) : buttonName(buttonName) {}
    std::string buttonName;
};

class EventDispatcher {
public:
    using HandlerFunc = std::function<void(const Event&)>;

    void registerHandler(const std::string& eventType, HandlerFunc handler) {
        handlers[eventType].push_back(handler);
    }

    void dispatch(const std::string& eventType, const Event& event) {
        if (handlers.find(eventType) != handlers.end()) {
            for (auto& handler : handlers[eventType]) {
                handler(event);
            }
        }
    }

private:
    std::unordered_map<std::string, std::vector<HandlerFunc>> handlers;
};

// Mock handler class using Google Mock
class MockEventHandler {
public:
    MOCK_METHOD(void, onEvent, (const Event&), ());
};

// Example Test Class
class EventDispatcherTest : public testing::Test {
protected:
    EventDispatcher dispatcher;
    MockEventHandler mockHandler;
};

TEST_F(EventDispatcherTest, ButtonClickEventIsHandledCorrectly) {
    // Set expectation on the mock handler
    EXPECT_CALL(mockHandler, onEvent(testing::Truly([](const Event& event) {
        const ButtonClickEvent* clickEvent = dynamic_cast<const ButtonClickEvent*>(&event);
        return clickEvent && clickEvent->buttonName == "SubmitButton";
    }))).Times(1);

    // Register the mock handler with the event dispatcher
    dispatcher.registerHandler("ButtonClick", [&](const Event& event) {
        mockHandler.onEvent(event);
    });

    // Dispatch a button click event
    ButtonClickEvent event("SubmitButton");
    dispatcher.dispatch("ButtonClick", event);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
