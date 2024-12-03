#include <iostream>
#include <vector>
#include <algorithm>

// Interface class representing a graphics resource
class GraphicsResource {
public:
    virtual void release() {
        std::cout << "Releasing resource" << std::endl;
    }
    virtual ~GraphicsResource() {}
};

// Example concrete resource class: Mesh
class Mesh : public GraphicsResource {
private:
    std::vector<float> vertices;
    size_t numVertices;

public:
    Mesh(const std::vector<float>& vertices)
        : vertices(vertices), numVertices(vertices.size()) {}

    void release() override {
        std::cout << "Releasing Mesh resource" << std::endl;
        // In practice, you would free GPU buffers here
    }

    size_t getNumVertices() const { return numVertices; }
};

// Example concrete resource class: Shader
class Shader : public GraphicsResource {
private:
    std::string shaderCode;

public:
    Shader(const std::string& shaderCode)
        : shaderCode(shaderCode) {}

    void release() override {
        std::cout << "Releasing Shader resource" << std::endl;
        // In practice, you would destroy shader program here
    }
};

// Factory method class to create graphics resources
class ResourceFactory {
public:
    virtual GraphicsResource* createMesh(const std::vector<float>& vertices) const = 0;
    virtual GraphicsResource* createShader(const std::string& shaderCode) const = 0;
    virtual ~ResourceFactory() {}
};

// Concrete factory class for generic resources
class GenericResourceFactory : public ResourceFactory {
public:
    GraphicsResource* createMesh(const std::vector<float>& vertices) const override {
        return new Mesh(vertices);
    }
    GraphicsResource* createShader(const std::string& shaderCode) const override {
        return new Shader(shaderCode);
    }
};

// Render logic to simulate use of resources
void render(std::vector<GraphicsResource*> resources) {
    for (GraphicsResource* resource : resources) {
        if (auto mesh = dynamic_cast<Mesh*>(resource)) {
            std::cout << "Rendering mesh with " << mesh->getNumVertices() << " vertices" << std::endl;
        } else if (auto shader = dynamic_cast<Shader*>(resource)) {
            std::cout << "Using shader: " << shader->shaderCode << std::endl;
        }
    }
}

int main() {
    std::vector<GraphicsResource*> resources;
    ResourceFactory* factory = new GenericResourceFactory();

    // Create resources
    resources.push_back(factory->createMesh({1.0f, 2.0f, 3.0f, 4.0f}));
    resources.push_back(factory->createShader("Basic Shader"));

    std::cout << "Resource sizes:\n";
    for (GraphicsResource* resource : resources) {
        std::cout << "\t" << typeid(*resource).name() << ": " << sizeof(*resource) << " bytes" << std::endl;
    }

    // Use resources
    render(resources);

    // Free resources
    for (GraphicsResource* resource : resources) {
        delete resource;
    }

    delete factory;
    return 0;
}
