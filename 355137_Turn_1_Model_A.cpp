#include <iostream>
#include <memory>
#include <string>

// Abstract Factory class
class ServiceFactory {
public:
    virtual ~ServiceFactory() = default;

    virtual std::unique_ptr<IService> createService() = 0;
};

// Concrete Factory class for creating LogService
class LogServiceFactory : public ServiceFactory {
public:
    std::unique_ptr<IService> createService() override {
        return std::make_unique<LogService>();
    }
};

// Concrete Factory class for creating DataService
class DataServiceFactory : public ServiceFactory {
public:
    std::unique_ptr<IService> createService() override {
        return std::make_unique<DataService>();
    }
};

// Singleton base class
class Singleton {
protected:
    Singleton() = default;
    ~Singleton() = default;

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static std::unique_ptr<Singleton>& getInstance() {
        static std::unique_ptr<Singleton> instance;
        if (!instance) {
            instance = std::make_unique<Singleton>();
        }
        return instance;
    }
};

// Service interface
class IService {
public:
    virtual ~IService() = default;

    virtual void doWork() = 0;
};

// Concrete LogService
class LogService : public IService, public Singleton {
public:
    void doWork() override {
        std::cout << "LogService: Doing logging work..." << std::endl;
    }
};

// Concrete DataService
class DataService : public IService, public Singleton {
public:
    void doWork() override {
        std::cout << "DataService: Doing data processing work..." << std::endl;
    }
};

int main() {
    // Using Factory to create LogService
    std::unique_ptr<ServiceFactory> logFactory = std::make_unique<LogServiceFactory>();
    std::unique_ptr<IService> logService = logFactory->createService();
    logService->doWork();  // Output: LogService: Doing logging work...

    // Using Factory to create DataService
    std::unique_ptr<ServiceFactory> dataFactory = std::make_unique<DataServiceFactory>();
    std::unique_ptr<IService> dataService = dataFactory->createService();
    dataService->doWork();  // Output: DataService: Doing data processing work...

    // Accessing the same instances through Singleton
    LogService::getInstance()->doWork();  // Output: LogService: Doing logging work...
    DataService::getInstance()->doWork();  // Output: DataService: Doing data processing work...

    return 0;
}
