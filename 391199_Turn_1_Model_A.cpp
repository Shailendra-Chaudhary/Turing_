#include <iostream>
#include <mutex>
#include <atomic>

class GameEngine {
private:
    static std::atomic<GameEngine*> instance;
    std::mutex mutex;
    GameEngine() = default;
    ~GameEngine() = default;

public:
    static GameEngine& GetInstance() {
        if (!instance) {
            {
                std::lock_guard<std::mutex> lock(mutex);
                if (!instance) {
                    instance.store(new GameEngine());
                }
            }
        }
        return *instance;
    }

    void StartEngine() {
        std::cout << "Game engine started." << std::endl;
    }

    void StopEngine() {
        std::cout << "Game engine stopped." << std::endl;
    }

    static void DestroyInstance() {
        delete instance.exchange(nullptr);
    }
};

std::atomic<GameEngine*> GameEngine::instance = nullptr;

int main() {
    GameEngine& engine1 = GameEngine::GetInstance();
    GameEngine& engine2 = GameEngine::GetInstance();

    engine1.StartEngine();
    engine2.StopEngine();

    GameEngine::DestroyInstance();

    return 0;
}
