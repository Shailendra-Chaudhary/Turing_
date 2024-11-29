
#include <iostream>
#include <dlfcn.h>
#include <string>

// Define a common interface for plugins
class Plugin {
public:
    virtual ~Plugin() {}
    virtual void execute() = 0;
};

// Function to load the plugin
Plugin* load_plugin(const std::string& plugin_path) {
    void* handle = dlopen(plugin_path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Error loading plugin: " << dlerror() << std::endl;
        return nullptr;
    }

    // Get the symbol for the plugin factory function
    typedef Plugin* (*plugin_factory_t)();
    plugin_factory_t factory = reinterpret_cast<plugin_factory_t>(dlsym(handle, "create_plugin"));
    if (!factory) {
        std::cerr << "Error finding plugin factory function: " << dlerror() << std::endl;
        dlclose(handle);
        return nullptr;
    }

    // Create the plugin instance
    Plugin* plugin = factory();
    if (!plugin) {
        std::cerr << "Error creating plugin instance: " << dlerror() << std::endl;
        dlclose(handle);
        return nullptr;
    }

    return plugin;
}

// Function to unload the plugin
void unload_plugin(Plugin* plugin) {
    delete plugin;
}

int main() {
    std::string plugin_path = "./my_plugin.so";  // Replace with the actual path to your plugin
    Plugin* plugin = load_plugin(plugin_path);

    if (plugin) {
        // Execute the plugin
        plugin->execute();

        // Unload the plugin
        unload_plugin(plugin);
    }

    return 0;
}
  
