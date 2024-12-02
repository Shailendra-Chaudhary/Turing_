#include <iostream>
#include <mutex>
#include <atomic>

class GameResourceManager {
private:
    static std::atomic<GameResourceManager*> instance;
    std::mutex mutex;
    GameResourceManager() = default;
    ~GameResourceManager() = default;

    GameResourceManager(const GameResourceManager&) = delete;
    GameResourceManager& operator=(const GameResourceManager&) = delete;

public:
    static GameResourceManager& GetInstance() {
        if (!instance) {
            // Use double-checked locking with atomic variables
            if (!instance.load(std::memory_order_acquire)) {
                std::lock_guard<std::mutex> lock(mutex);
                if (!instance.load(std::memory_order_acquire)) {
                    instance.store(new GameResourceManager(), std::memory_order_release);
                }
            }
        }
        return *instance;
    }

    void LoadResource(const std::string& filename) {
        std::cout << "Loading resource: " << filename << std::endl;
        // Implement resource loading logic here
    }

    void UnloadResource(const std::string& filename) {
        std::cout << "Unloading resource: " << filename << std::endl;
        // Implement resource unloading logic here
    }

    static void DestroyInstance() {
        delete instance.exchange(nullptr);
    }

private:
    std::mutex resourceMutex;
};

std::atomic<GameResourceManager*> GameResourceManager::instance = nullptr;

int main() {
    GameResourceManager& resourceManager1 = GameResourceManager::GetInstance();
    GameResourceManager& resourceManager2 = GameResourceManager::GetInstance();

    resourceManager1.LoadResource("texture.png");
    resourceManager2.UnloadResource("texture.png");

    GameResourceManager::DestroyInstance();

    return 0;
}
