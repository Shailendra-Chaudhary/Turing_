#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class ConfigService {
public:
    static std::unique_ptr<ConfigService>& GetInstance() {
        static std::unique_ptr<ConfigService> instance = std::make_unique<ConfigService>();
        return instance;
    }

    std::string GetStringConfig(const std::string& key) const {
        // Simulated configuration retrieval
        static std::unordered_map<std::string, std::string> configs = {
            {"app_name", "MyApp"},
            {"log_level", "info"},
        };
        return configs.find(key)->second;
    }

private:
    ConfigService() = default;
};

class Logger {
public:
    Logger(const std::string& logLevel) : logLevel_(logLevel) {}

    void LogMessage(const std::string& message) {
        std::cout << "Logger [" << logLevel_ << "]: " << message << std::endl;
    }

private:
    std::string logLevel_;
};

class Database {
public:
    Database(const std::string& connectionString) : connectionString_(connectionString) {}

    void ExecuteQuery(const std::string& query) {
        std::cout << "Database: Executing query: " << query << std::endl;
    }

private:
    std::string connectionString_;
};

class ServiceRegistry {
public:
    enum class ServiceType {
        LOGGER,
        DATABASE
    };

    static std::unique_ptr<ServiceRegistry>& GetInstance() {
        static std::unique_ptr<ServiceRegistry> instance = std::make_unique<ServiceRegistry>();
        return instance;
    }

    template <typename T>
    std::unique_ptr<T> GetService(ServiceType serviceType) {
        if (services_.find(serviceType) == services_.end()) {
            CreateService(serviceType);
        }
        return std::static_pointer_cast<T>(services_[serviceType]);
    }

private:
    ServiceRegistry() = default;

    void CreateService(ServiceType serviceType) {
        const std::string configPrefix = "service.";
        switch (serviceType) {
            case ServiceType::LOGGER: {
                std::string logLevel = ConfigService::GetInstance()->GetStringConfig(configPrefix + "logger.level");
                services_[serviceType] = std::make_unique<Logger>(logLevel);
                break;
            }
            case ServiceType::DATABASE: {
                std::string connectionString = ConfigService::GetInstance()->GetStringConfig(configPrefix + "database.connection");
                services_[serviceType] = std::make_unique<Database>(connectionString);
                break;
            }
            default:
                throw std::invalid_argument("Invalid service type requested.");
        }
    }

    std::unordered_map<ServiceType, std::unique_ptr<void>> services_;
};

int main() {
    auto logger = ServiceRegistry::GetInstance()->GetService<Logger>(ServiceRegistry::ServiceType::LOGGER);
    logger->LogMessage("Application started.");

    auto database = ServiceRegistry::GetInstance()->GetService<Database>(ServiceRegistry::ServiceType::DATABASE);
    database->ExecuteQuery("SELECT * FROM users;");

    return 0;
}  
