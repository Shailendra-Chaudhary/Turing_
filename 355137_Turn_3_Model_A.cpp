
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
        static std::unordered_map<std::string, std::string> configs = {
            {"db_connection_string", "mongodb://localhost:27017/testdb"},
            {"log_level", "info"},
        };
        return configs.find(key)->second;
    }

private:
    ConfigService() = default;
};

class DatabaseService {
public:
    DatabaseService() : connectionString_(ConfigService::GetInstance()->GetStringConfig("db_connection_string")) {
        std::cout << "Connecting to database: " << connectionString_ << std::endl;
    }

    void ExecuteQuery(const std::string& query) {
        std::cout << "Database: Executing query: " << query << std::endl;
    }

private:
    std::string connectionString_;
};

class LoggerService {
public:
    LoggerService() : logLevel_(ConfigService::GetInstance()->GetStringConfig("log_level")) {}

    void LogMessage(const std::string& level, const std::string& message) {
        if (level == logLevel_ || level == "error") {
            std::cout << "Logger [" << logLevel_ << "]: " << message << std::endl;
        }
    }

private:
    std::string logLevel_;
};

class ServiceFactory {
public:
    enum class ServiceType {
        DATABASE,
        LOGGER
    };

    static std::unique_ptr<Service> CreateService(ServiceType serviceType) {
        switch (serviceType) {
            case ServiceType::DATABASE:
                return std::make_unique<DatabaseService>();
            case ServiceType::LOGGER:
                return std::make_unique<LoggerService>();
            default:
                throw std::invalid_argument("Invalid service type requested.");
        }
    }

private:
    ServiceFactory() = default;
};

class Service {
public:
    virtual void PerformAction(const std::string& action) = 0;
    virtual ~Service() = default;
};

class Application {
public:
    void Run() {
        std::unique_ptr<DatabaseService> db = std::dynamic_pointer_cast<DatabaseService>(
                ServiceFactory::CreateService(ServiceFactory::ServiceType::DATABASE));
        db->ExecuteQuery("INSERT INTO users (name) VALUES ('Alice')");

        std::unique_ptr<LoggerService> logger = std::dynamic_pointer_cast<LoggerService>(ServiceFactory::CreateService(ServiceFactory::ServiceType::LOGGER));
        logger->LogMessage("info", "Application started.");
        logger->LogMessage("debug", "Internal debug message.");
        logger->LogMessage("error", "An error occurred!");
    }
};

 int main() {
    Application app;
    app.Run();
    return 0;
 }