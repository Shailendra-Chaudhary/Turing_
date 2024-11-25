#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <exception>

namespace fs = std::filesystem;

// Function to save data to persistent memory
void saveDataToPersistentMemory(const std::string& data, const std::string& filePath) {
    try {
        std::ofstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open the file for writing.");
        }
        file << data;
        file.close();
        std::cout << "Data saved to " << filePath << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error saving data: " << e.what() << std::endl;
    }
}

// Function to load data from persistent memory
std::string loadDataFromPersistentMemory(const std::string& filePath) {
    std::string data;
    try {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open the file for reading.");
        }
        std::getline(file, data);
        file.close();
        if (data.empty()) {
            throw std::runtime_error("File is empty.");
        }
        std::cout << "Data loaded from " << filePath << std::endl;
        return data;
    } catch (const std::exception& e) {
        std::cerr << "Error loading data: " << e.what() << std::endl;
        return "";
    }
}

// Function to ensure the directory exists
void createDirectoryIfNotExists(const std::string& dirPath) {
    try {
        fs::create_directory(dirPath);
        std::cout << "Directory " << dirPath << " created if it didn't exist." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error creating directory: " << e.what() << std::endl;
    }
}

int main() {
    const std::string dataToSave = "Hello, IoT World!";
    const std::string dataFilePath = "./persistent_data/saved_data.txt";
    const std::string dataDirectoryPath = "./persistent_data";

    // Create the directory if it doesn't exist
    createDirectoryIfNotExists(dataDirectoryPath);

    // Save data to persistent memory
    saveDataToPersistentMemory(dataToSave, dataFilePath);

    // Load data from persistent memory
    std::string loadedData = loadDataFromPersistentMemory(dataFilePath);

    // Display the loaded data
    if (!loadedData.empty()) {
        std::cout << "Loaded data: " << loadedData << std::endl;
    }

    return 0;
}
