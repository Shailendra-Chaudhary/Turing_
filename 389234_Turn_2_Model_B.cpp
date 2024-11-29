#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <dlfcn.h> // Unix/Linux
#include <windows.h> // Windows

// Interface class for all plugins
class Plugin {
public:
    virtual ~Plugin() = default;
    virtual std::string getName() const = 0;
    virtual void execute(const std::string& message) = 0;
};

// Function to dynamically load a plugin
std::unique_ptr<Plugin> loadPlugin(const std::string& pluginName) {
#ifdef __linux__
    void* lib = dlopen(pluginName.c_str(), RTLD_NOW);
    if (lib == nullptr) {
        std::cerr << "Failed to load the library: " << pluginName << std::endl;
        std::cerr << dlerror() << std::endl;
        return nullptr;
    }

    using CreatePluginFunc = std::unique_ptr<Plugin> (*)();
    CreatePluginFunc createPlugin = reinterpret_cast<CreatePluginFunc>(dlsym(lib, "createPlugin"));
    if (createPlugin == nullptr) {
        std::cerr << "Failed to retrieve the createPlugin function." << std::endl;
        std::cerr << dlerror() << std::endl;
        dlclose(lib);
        return nullptr;
    }

    return createPlugin();
#elseif defined(_WIN32)
    HMODULE lib = LoadLibrary(pluginName.c_str());
    if (lib == nullptr) {
        std::cerr << "Failed to load the library: " << pluginName << std::endl;
        std::cerr << GetLastError() << std::endl;
        return nullptr;
    }

    using CreatePluginFunc = std::unique_ptr<Plugin> (*)();
    CreatePluginFunc createPlugin = reinterpret_cast<CreatePluginFunc>(GetProcAddress(lib, "createPlugin"));
    if (createPlugin == nullptr) {
        std::cerr << "Failed to retrieve the createPlugin function." << std::endl;
        std::cerr << GetLastError() << std::endl;
        FreeLibrary(lib);
        return nullptr;
    }

    return createPlugin();
#endif
}

int main() {
    std::vector<std::unique_ptr<Plugin>> plugins;

    // Load all plugins dynamically
    const std::vector<std::string> pluginNames = {"plugin1.so", "plugin2.so"}; // Linux plugins
    // const std::vector<std::string> pluginNames = {"plugin1.dll", "plugin2.dll"}; // Windows plugins

    for (const std::string& pluginName : pluginNames) {
        auto plugin = loadPlugin(pluginName);
        if (plugin) {
            plugins.push_back(std::move(plugin));
        }
    }

    // Execute all plugins
    std::string message = "Hello from the main application!";
    for (const auto& plugin : plugins) {
        plugin->execute(message);
    }

    return 0;
}
