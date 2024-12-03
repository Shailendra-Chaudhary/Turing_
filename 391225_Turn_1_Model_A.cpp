#include <iostream>

// Simple singleton pattern for a resource manager
class ResourceManager {
private:
    static ResourceManager* instance;
    ResourceManager() = default;
    ~ResourceManager() = default;

public:
    static ResourceManager* getInstance() {
        if (!instance) {
            instance = new ResourceManager();
        }
        return instance;
    }

    void release() {
        if (instance) {
            delete instance;
            instance = nullptr;
        }
    }
};

ResourceManager* ResourceManager::instance = nullptr;

int main() {
    // Calculate the size of the ResourceManager object
    std::cout << "Size of ResourceManager: " << sizeof(ResourceManager) << " bytes" << std::endl;

    // Create an instance of the Singleton
    ResourceManager* manager = ResourceManager::getInstance();

    // Assuming you have some memory management mechanism
    // to keep track of allocated resources, you can use
    // std::cout or equivalent to report on those allocations.

    // For demonstration, let's simulate a resource allocation:
    std::cout << "Simulating allocation of a texture..." << std::endl;

    // Simulated texture data
    unsigned char textureData[1024 * 1024]; // Assume 1MB texture
    std::cout << "Texture data size: " << sizeof(textureData) << " bytes" << std::endl;

    // Release the Singleton instance
    manager->release();

    return 0;
}
