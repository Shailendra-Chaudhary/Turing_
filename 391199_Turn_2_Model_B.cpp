#include <iostream>
#include <mutex>
#include <atomic>

// Forward declaration of LogManager (Example of Dependency Management)
class LogManager;

class GameEngine {
private:
    GameEngine() = default;
    ~GameEngine() = default;
    GameEngine(const GameEngine&) = delete;           // Disable copy-constructor
    GameEngine& operator=(const GameEngine&) = delete; // Disable copy-assignment

    // The Singleton instance will be lazily initialized on demand.
    static std::atomic<GameEngine*> instance;
    std::mutex mutex;

    // Example of dependency management: Hold a reference to LogManager
    LogManager& logManager;

    // Ensure that other threads cannot initialize the Singleton concurrently
    GameEngine(LogManager& logManager);

public:
    // Function to get the Singleton instance (thread-safe)
    static GameEngine& GetInstance();

    void StartEngine();
    void StopEngine();

    static void DestroyInstance();
};

// Singleton Implementation in cpp file for better organization
#include "GameEngine.h"

std::atomic<GameEngine*> GameEngine::instance = nullptr;

GameEngine::GameEngine(LogManager& logManager) 
    : logManager(logManager) {
    // Additional initialization code here...
    logManager.Log("GameEngine initialized.");
}

GameEngine& GameEngine::GetInstance() {
    if (!instance) {
        std::call_once(once_flag, []() {
            instance.store(new GameEngine(LogManager::GetInstance())); // Initialize with LogManager dependency
        });
    }
    return *instance;
}

void GameEngine::StartEngine() {
    // Implement engine start logic...
    logManager.Log("Game engine started.");
}

void GameEngine::StopEngine() {
    // Implement engine stop logic...
    logManager.Log("Game engine stopped.");
}

void GameEngine::DestroyInstance() {
    // Delete the Singleton instance (note: it's not always necessary to explicitly destroy it)
    delete instance.exchange(nullptr);
}
 
 // Example of LogManager class (used as a dependency)
class LogManager {
private:
    LogManager() = default;
    LogManager(const LogManager&) = delete;
    LogManager& operator=(const LogManager&) = delete;

    static std::atomic<LogManager*> instance;
    std::mutex mutex;

public:
    static LogManager& GetInstance();

    void Log(const std::string& message) {
        // Implement actual logging logic...
        std::lock_guard<std::mutex> lock(mutex);
