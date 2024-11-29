#include <iostream>
#include <string>
#include <vector>
#include <dlfcn.h> // Unix/Linux only
#include <windows.h> // Windows only
#include "plugin_interface.h"

#ifdef __linux__ // Unix/Linux
#define LOAD_LIBRARY(name) dlopen(name, RTLD_NOW)
#define GET_FUNCTION(lib, name) dlsym(lib, name)
#define UNLOAD_LIBRARY(lib) dlclose(lib)
#elseif defined(_WIN32) // Windows
#define LOAD_LIBRARY(name) LoadLibrary(name)
#define GET_FUNCTION(lib, name) GetProcAddress(lib, name)
#define UNLOAD_LIBRARY(lib) FreeLibrary(lib)
#endif

int main() {
    std::string pluginName = "plugin.so"; // Plugin file name (Unix/Linux)
    // std::string pluginName = "plugin.dll"; // Plugin file name (Windows)

    // Load the shared library
    void* lib = LOAD_LIBRARY(pluginName.c_str());
    if (lib == nullptr) {
        std::cerr << "Failed to load the library: " << pluginName << std::endl;
#ifdef __linux__
        std::cerr << dlerror() << std::endl;
#elseif defined(_WIN32)
        std::cerr << GetLastError() << std::endl;
#endif
        return 1;
    }

    // Retrieve the function pointer from the library
    PluginFunction executePlugin = reinterpret_cast<PluginFunction>(GET_FUNCTION(lib, "execute"));
    if (executePlugin == nullptr) {
        std::cerr << "Failed to retrieve the function pointer." << std::endl;
#ifdef __linux__
        std::cerr << dlerror() << std::endl;
#elseif defined(_WIN32)
        std::cerr << GetLastError() << std::endl;
#endif
        UNLOAD_LIBRARY(lib);
        return 1;
    }

    // Call the plugin function
    executePlugin("Hello from the plugin!");

    // Unload the shared library
    UNLOAD_LIBRARY(lib);

    return 0;
}
