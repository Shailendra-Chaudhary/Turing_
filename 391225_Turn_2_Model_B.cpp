#include <iostream>
#include <memory>
#include <vector>

// Mock class representing a texture
class Texture {
private:
    int width, height;
    std::unique_ptr<unsigned char[]> data;  // Using smart pointer for automatic memory management

public:
    Texture(int w, int h) : width(w), height(h), data(new unsigned char[w * h * 4]) {
        std::cout << "Texture created: " << w << "x" << h << std::endl;
        // Initialize texture data (simulate loading)
    }

    ~Texture() {
        std::cout << "Texture destroyed" << std::endl;
    }
    
    size_t getSize() const {
        return width * height * 4;
    }
};

// TextureFactory using Factory Pattern to manage texture creation
class TextureFactory {
public:
    std::shared_ptr<Texture> createTexture(int width, int height) {
        return std::make_shared<Texture>(width, height);  // Shared ownership
    }
};

int main() {
    TextureFactory factory;
    std::vector<std::shared_ptr<Texture>> textures;

    // Create and manage multiple textures
    for (int i = 0; i < 5; ++i) {
        auto texture = factory.createTexture(512, 512);
        textures.push_back(texture);
        std::cout << "Texture size: " << texture->getSize() << " bytes" << std::endl;
    }

    // Display memory usage
    size_t totalMemoryUsage = 0;
    for (const auto& texture : textures) {
        totalMemoryUsage += texture->getSize();
    }
    std::cout << "Total memory usage for textures: " << totalMemoryUsage << " bytes" << std::endl;

    // `textures` goes out of scope and all resources are released
    return 0;
}
