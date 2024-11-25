#include <iostream>
#include <fstream>
#include <system_error>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>

const std::string DATA_FILE_PATH = "./persistent_data/mapped_data.bin";
const int DATA_SIZE = 1024; // 1KB data size

// Function to create or truncate the data file to the specified size
void prepareDataFile() {
    try {
        std::ofstream file(DATA_FILE_PATH, std::ios::trunc | std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open data file for truncation.");
        }
        file.seekp(DATA_SIZE - 1);
        file.put(0);
        file.close();
        std::cout << "Data file created/truncated successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error preparing data file: " << e.what() << std::endl;
    }
}

// Function to map the file to memory
void* mapMemory() {
    int fd = open(DATA_FILE_PATH, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        throw std::system_error(errno, std::generic_category(), "Error opening data file");
    }

    void* mappedData = mmap(nullptr, DATA_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mappedData == MAP_FAILED) {
        close(fd);
        throw std::system_error(errno, std::generic_category(), "Error mapping memory");
    }

    return mappedData;
}

// Function to unmap the memory
void unmapMemory(void* mappedData) {
    if (munmap(mappedData, DATA_SIZE) == -1) {
        throw std::system_error(errno, std::generic_category(), "Error unmapping memory");
    }
}

// Function to save data to memory-mapped file
void saveDataToMemory(const void* data, size_t dataSize) {
    void* mappedData = mapMemory();
    memcpy(mappedData, data, dataSize);
    unmapMemory(mappedData);
    std::cout << "Data saved to memory-mapped file successfully." << std::endl;
}

// Function to load data from memory-mapped file
void* loadDataFromMemory() {
    void* mappedData = mapMemory();
    std::cout << "Data loaded from memory-mapped file successfully." << std::endl;
    return mappedData;
}

int main() {
    prepareDataFile();

    // Sample data to be saved
    const char* sampleData = "Hello, IoT World! This data is saved using memory mapping.";
    size_t dataSize = strlen(sampleData) + 1;

    saveDataToMemory(sampleData, dataSize);

    // Load and display the data
    void* loadedData = loadDataFromMemory();
    if (loadedData) {
        char* loadedDataChar = static_cast<char*>(loadedData);
        std::cout << "Loaded data: " << loadedDataChar << std::endl;
        unmapMemory(loadedData);
    }

    return 0;
}
