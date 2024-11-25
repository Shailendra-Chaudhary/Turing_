#include <iostream>
#include <memory>
#include <string>

// The Singleton class
class Logger {
public:
    static std::unique_ptr<Logger>& GetInstance() {
        static std::unique_ptr<Logger> instance = std::make_unique<Logger>();
        return instance;
    }

    void LogMessage(const std::string& message) {
        std::cout << "Logger: " << message << std::endl;
    }

private:
    Logger() = default; // Prevent direct instantiation from outside
};

// The Factory class
class ServiceFactory {
public:
    enum class ServiceType {
        LOGGER
    };

    static std::unique_ptr<Service> CreateService(ServiceType serviceType) {
        switch (serviceType) {
            case ServiceType::LOGGER:
                return std::make_unique<Logger>();
            default:
                throw std::invalid_argument("Invalid service type requested.");
        }
    }
};

// Base class for services
class Service {
public:
    virtual void PerformServiceAction() = 0;
    virtual ~Service() = default;
};

// Client code
int main() {
    // Accessing the Singleton instance through the Factory
    auto loggerService = ServiceFactory::CreateService(ServiceFactory::ServiceType::LOGGER);
    auto logger = std::dynamic_pointer_cast<Logger>(loggerService);

    if (logger) {
        logger->LogMessage("Hello from the application!");
    } else {
        std::cerr << "Failed to obtain Logger service." << std::endl;
        return 1;
    }

    // Even though the service is a Singleton, the Factory abstracts away this detail
    // allowing for easy addition of other services with different lifecycle patterns in the future.

    return 0;
}
