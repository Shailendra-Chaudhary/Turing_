#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <functional>
#include <queue>
#include <unordered_map>
#include <string>

// Event system simulation
class Event {
public:
    virtual ~Event() {}
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

// Mock an event class
class MockEvent : public Event {};

// Mock a handler using Google Mock
class MockHandler {
public:
    MOCK_METHOD(void, handleEvent, (const Event&), ());
};

// Example Test Class
class EventDispatcherTest : public testing::Test {
protected:
    EventDispatcher dispatcher;
    MockHandler mockHandler;
};

TEST_F(EventDispatcherTest, HandlerReceivesDispatchedEvent) {
    // Set expectation on the mock handler
    EXPECT_CALL(mockHandler, handleEvent(testing::A<const Event&>())).Times(1);

    // Register the mock handler with the event dispatcher
    dispatcher.registerHandler("TestEvent", [&](const Event& event) {
        mockHandler.handleEvent(event);
    });

    // Dispatch the event
    MockEvent event;
    dispatcher.dispatch("TestEvent", event);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
