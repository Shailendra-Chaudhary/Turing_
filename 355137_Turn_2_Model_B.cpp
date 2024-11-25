#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

// Singleton classes
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
    Logger() = default;
};

class Database {
public:
    static std::unique_ptr<Database>& GetInstance() {
        static std::unique_ptr<Database> instance = std::make_unique<Database>();
        return instance;
    }

    void Connect(const std::string& connectionString) {
        std::cout << "Database: Connecting to " << connectionString << std::endl;
    }

private:
    Database() = default;
};

// Factory class
class ServiceFactory {
public:
    enum class ServiceType {
        LOGGER,
        DATABASE
    };

    static std::unique_ptr<Service> CreateService(ServiceType serviceType) {
        static std::unordered_map<ServiceType, std::function<std::unique_ptr<Service>()>> serviceCreators = {
            {ServiceType::LOGGER, []() { return std::make_unique<Logger>(); }},
            {ServiceType::DATABASE, []() { return std::make_unique<Database>(); }}
        };

        auto it = serviceCreators.find(serviceType);
        if (it == serviceCreators.end()) {
            throw std::invalid_argument("Invalid service type requested.");
        }
        return it->second();
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
    // Accessing the Singleton instances through the Factory
    auto loggerService = ServiceFactory::CreateService(ServiceFactory::ServiceType::LOGGER);
    auto logger = std::dynamic_pointer_cast<Logger>(loggerService);

    if (logger) {
        logger->LogMessage("Hello from the application!");
    } else {
        std::cerr << "Failed to obtain Logger service." << std::endl;
        return 1;
    }

    auto databaseService = ServiceFactory::CreateService(ServiceFactory::ServiceType::DATABASE);
    auto database = std::dynamic_pointer_cast<Database>(databaseService);

    if (database) {
        database->Connect("db.example.com:3306");
    } else {
        std::cerr << "Failed to obtain Database service." << std::endl;
        return 1;
    }

    return 0;
}
