#include <iostream>
#include <mutex>
#include <atomic>

class GameEngine {
private:
    // Static variable to hold the singleton instance
    static std::atomic<GameEngine*> instance;
    
    // Private constructor to prevent direct instantiation from outside
    GameEngine() = default;
    
    // Private destructor to prevent direct deletion from outside
    ~GameEngine() = default;
    
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
                    instance.store(new GameEngine(), std::memory_order_release);
                }
            }
        }
        return *instance;
    }
    
    // Method to start the game engine
    void StartEngine() {
        std::cout << "Game engine started." << std::endl;
    }
    
    // Method to stop the game engine
    void StopEngine() {
        std::cout << "Game engine stopped." << std::endl;
    }
    
    // Static method to destroy the singleton instance
    static void DestroyInstance() {
        delete instance.exchange(nullptr);
    }

private:
    // Static mutex to protect the instance variable
    static std::mutex mutex;
};

// Initialize the static variables
std::atomic<GameEngine*> GameEngine::instance = nullptr;
std::mutex GameEngine::mutex;

int main() {
    GameEngine& engine1 = GameEngine::GetInstance();
    GameEngine& engine2 = GameEngine::GetInstance();

    engine1.StartEngine();
    engine2.StopEngine();

    // Ensure the singleton is destroyed when done
    GameEngine::DestroyInstance();

    return 0;
}
