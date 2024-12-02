#include <iostream>
#include <mutex>
#include <atomic>
#include <memory>

class GameEngine {
private:
    // Static variable to hold the singleton instance
    static std::atomic<std::unique_ptr<GameEngine>> instance;

    // Private constructor to prevent direct instantiation from outside
    GameEngine() = default;

    // Private destructor to ensure proper cleanup
    ~GameEngine() {
        std::cout << "Game engine destroyed." << std::endl;
    }

    // Copy constructor and assignment operator are deleted to prevent copying
    GameEngine(const GameEngine&) = delete;
    GameEngine& operator=(const GameEngine&) = delete;

public:
    // Static method to get the singleton instance
    static GameEngine& GetInstance() {
        if (!instance) {
            // Use a double-checked locking pattern with an atomic variable
            if (!instance.load(std::memory_order_acquire)) {
                std::lock_guard<std::mutex> lock(mutex);
                if (!instance.load(std::memory_order_acquire)) {
                    instance.store(std::make_unique<GameEngine>(), std::memory_order_release);
                }
            }
        }
        return *instance.load(std::memory_order_relaxed);
    }

    // Method to start the game engine
    void StartEngine() {
        std::cout << "Game engine started." << std::endl;
    }

    // Method to stop the game engine
    void StopEngine() {
        std::cout << "Game engine stopped." << std::endl;
    }

    // Static method to destroy the singleton instance (not typically used in game engines, but for testing purposes)
    static void DestroyInstance() {
        instance.store(nullptr, std::memory_order_release);
    }

private:
    // Static mutex to protect the instance variable
    static std::mutex mutex;
};

// Initialize the static variables
std::atomic<std::unique_ptr<GameEngine>> GameEngine::instance = nullptr;
std::mutex GameEngine::mutex;

int main() {
    GameEngine& engine = GameEngine::GetInstance();
    engine.StartEngine();
    // ...
    // Game engine loop here
    // ...
    engine.StopEngine();

    return 0;
}
