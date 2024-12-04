#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <cstring>

// Function to process data (dummy function for demonstration)
void processData(const char* data, size_t length) {
    // Just iterate over the data without doing anything significant for the demo
    volatile size_t sum = 0;
    for (size_t i = 0; i < length; ++i) {
        sum += data[i];
    }
}

void standardFileIO(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file with standard file I/O \n";
        return;
    }

    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(fileSize);
    file.read(buffer.data(), fileSize);
    file.close();

    processData(buffer.data(), buffer.size());
}

void memoryMappedIO(const std::string& filePath) {
    int fd = open(filePath.c_str(), O_RDONLY);
    if (fd == -1) {
        std::cerr << "Error opening file with memory-mapped I/O\n";
        return;
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        std::cerr << "Error getting file size for memory-mapped I/O\n";
        close(fd);
        return;
    }
    size_t fileSize = sb.st_size;

    void* mapped = mmap(nullptr, fileSize, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED) {
        std::cerr << "Error memory-mapping the file\n";
        close(fd);
        return;
    }

    processData(static_cast<const char*>(mapped), fileSize);

    munmap(mapped, fileSize);
    close(fd);
}

int main() {
    const std::string filePath = "large_dataset.bin";

    auto start = std::chrono::high_resolution_clock::now();
    standardFileIO(filePath);
    auto end = std::chrono::high_resolution_clock::now();
    auto durationStandardIO = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Standard File I/O Time: " << durationStandardIO << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    memoryMappedIO(filePath);
    end = std::chrono::high_resolution_clock::now();
    auto durationMemoryMappedIO = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Memory-Mapped I/O Time: " << durationMemoryMappedIO << " ms\n";

    return 0;
}
