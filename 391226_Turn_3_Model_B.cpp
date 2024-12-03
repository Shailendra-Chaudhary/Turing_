#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

// Base Event class
class Event {
public:
    virtual ~Event() = default;
};

// Specific Event example
class ClickEvent : public Event {
public:
    std::string button;
    ClickEvent(const std::string& button) : button(button) {}
};

// Event dispatcher class
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

// Mock handler using Google Mock
class MockHandler {
public:
    MOCK_METHOD(void, handleEvent, (const Event&), ());
};

// Test cases using GoogleTest
class EventDispatcherTest : public ::testing::Test {
protected:
    EventDispatcher dispatcher;
    MockHandler mockHandler;
};

TEST_F(EventDispatcherTest, TriggerClickEvent) {
    // Expectation for the handleEvent called with a ClickEvent having button == "ConfirmButton"
    EXPECT_CALL(mockHandler, handleEvent(testing::Field(&Event::dynamic_type_id, testing::Eq([]{return typeid(ClickEvent);}))
                           && testing::Property(&ClickEvent::button, testing::StrEq("ConfirmButton"))))
        .Times(1);

    // Register the mock handler
    dispatcher.registerHandler("ClickEvent", [&](const Event& event) {
        mockHandler.handleEvent(event);
    });

    // Dispatch a ClickEvent
    ClickEvent clickEvent("ConfirmButton");
    dispatcher.dispatch("ClickEvent", clickEvent);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
