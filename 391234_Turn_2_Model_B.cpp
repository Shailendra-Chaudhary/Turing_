#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

// Define protocol interface
class ProtocolHandler {
public:
    virtual ~ProtocolHandler() {}
    virtual void sendMessage(const std::string &message) = 0;
    virtual void receiveMessage() = 0;
};

// HTTP Handler
class HTTPHandler : public ProtocolHandler {
public:
    void sendMessage(const std::string &message) override {
        // Implement HTTP send code
        std::cout << "HTTP: Sending message " << message << std::endl;
    }
    
    void receiveMessage() override {
        // Implement HTTP receive code
        std::cout << "HTTP: Message Received" << std::endl;
    }
};

// MQTT Handler
class MQTTHandler : public ProtocolHandler {
public:
    void sendMessage(const std::string &message) override {
        // Implement MQTT send code
        std::cout << "MQTT: Sending message " << message << std::endl;
    }
    
    void receiveMessage() override {
        // Implement MQTT receive code
        std::cout << "MQTT: Message Received" << std::endl;
    }
};

// IoT Device using multiple protocols
class IoTDevice {
private:
    std::vector<ProtocolHandler*> handlers;
    
public:
    void addProtocolHandler(ProtocolHandler *handler) {
        handlers.push_back(handler);
    }
    
    void broadcastMessage(const std::string &message) {
        for (auto handler : handlers) {
            handler->sendMessage(message);
        }
    }

    void fetchMessages() {
        for (auto handler : handlers) {
            handler->receiveMessage();
        }
    }
};

int main() {
    IoTDevice device;
    
    // Initialize and add different protocol handlers
    HTTPHandler httpHandler;
    MQTTHandler mqttHandler;
    
    device.addProtocolHandler(&httpHandler);
    device.addProtocolHandler(&mqttHandler);

    // Simulate sending and receiving messages
    for (int i = 0; i < 5; ++i) {
        std::string message = "Data point " + std::to_string(i);
        device.broadcastMessage(message);
        device.fetchMessages();
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate delay
    }

    return 0;
}
