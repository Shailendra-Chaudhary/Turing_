#include <memory>
#include <mutex>
#include <unordered_map>

// Example resource class
class Texture {
public:
    Texture(const std::string& filename) { /* Load texture from file */ }
    ~Texture() { /* Free texture resources */ }
};

// Singleton resource manager
class ResourceManager {
public:
    static ResourceManager& GetInstance() {
        static std::unique_ptr<ResourceManager> instance;
        static std::once_flag onceFlag;
        std::call_once(onceFlag, [] {
            instance = std::make_unique<ResourceManager>();
        });
        return *instance;
    }

    // Load a texture from file and store it in the resource map
    std::shared_ptr<Texture> LoadTexture(const std::string& filename) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = textures_.find(filename);
        if (it != textures_.end()) {
            return it->second;
        }
        std::shared_ptr<Texture> texture = std::make_shared<Texture>(filename);
        textures_[filename] = texture;
        return texture;
    }

    // Release a texture from the resource map
    void ReleaseTexture(const std::string& filename) {
        std::lock_guard<std::mutex> lock(mutex_);
        textures_.erase(filename);
    }

private:
    ResourceManager() = default;
    ~ResourceManager() = default;

    // Prevent copying and moving
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    std::unordered_map<std::string, std::shared_ptr<Texture>> textures_;
    std::mutex mutex_;
};
