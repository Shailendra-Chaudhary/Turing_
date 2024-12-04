#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <thread>

// Abstract protocol class
class Protocol {
public:
    virtual bool sendData(const std::string& data) = 0;
    virtual bool receiveData(std::string& data) = 0;
    virtual ~Protocol() = default;
};

// MQTT protocol class (placeholder)
class MQTTProtocol : public Protocol {
public:
    bool sendData(const std::string& data) override {
        std::cout << "MQTT: Sending: " << data << std::endl;
        return true;
    }
    bool receiveData(std::string& data) override {
        data = "MQTT: Received Data";
        std::cout << "MQTT: Received: " << data << std::endl;
        return true;
    }
};

// HTTP protocol class (placeholder)
class HTTPProtocol : public Protocol {
public:
    bool sendData(const std::string& data) override {
        std::cout << "HTTP: Sending: " << data << std::endl;
        return true;
    }
    bool receiveData(std::string& data) override {
        data = "HTTP: Received Data";
        std::cout << "HTTP: Received: " << data << std::endl;
        return true;
    }
};

// Protocol manager class
class ProtocolManager {
public:
    void addProtocol(std::shared_ptr<Protocol> protocol, const std::string& id) {
        protocols[id] = protocol;
    }
    bool sendData(const std::string& protocolId, const std::string& data) {
        auto it = protocols.find(protocolId);
        if (it != protocols.end()) {
            return it->second->sendData(data);
        } else {
            std::cout << "Protocol not found: " << protocolId << std::endl;
            return false;
        }
    }
    bool receiveData(const std::string& protocolId, std::string& data) {
        auto it = protocols.find(protocolId);
        if (it != protocols.end()) {
            return it->second->receiveData(data);
        } else {
            std::cout << "Protocol not found: " << protocolId << std::endl;
            return false;
        }
    }

private:
    std::map<std::string, std::shared_ptr<Protocol>> protocols;
};

// Example usage
int main() {
    ProtocolManager manager;
    manager.addProtocol(std::make_shared<MQTTProtocol>(), "MQTT");
    manager.addProtocol(std::make_shared<HTTPProtocol>(), "HTTP");

    // Send data
    std::string data = "Sample data";
    manager.sendData("MQTT", data);
    manager.sendData("HTTP", data);

    // Receive data
    data.clear();
    manager.receiveData("MQTT", data);
    manager.receiveData("HTTP", data);

    // Non-blocking communication using threads (execution order is non-deterministic)
    std::thread mqttThread([&manager] {
        std::string data;
        while (manager.receiveData("MQTT", data)) {
            std::cout << "MQTT Thread: Received: " << data << std::endl;
        }
    });

    std::thread httpThread([&manager] {
        std::string data;
        while (manager.receiveData("HTTP", data)) {
            std::cout << "HTTP Thread: Received: " << data << std::endl;
        }
    });

    // Join threads
    mqttThread.join();
    httpThread.join();

    return 0;
}
