#include <iostream>
#include <fstream>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <chrono>
#include <cerrno>
#include <cstring>

// Replace 'large_dataset.bin' with your large data file name
const std::string filePath = "large_dataset.bin";

// Helper function to count characters in a file using standard file I/O
void countCharsStandardIO() {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file with standard I/O: " << file.str() << std::endl;
        return;
    }

    char c;
    long long int count = 0;

    std::cout << "Counting characters using standard I/O..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    while (file >> c) {
        ++count;
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Number of characters: " << count << std::endl;
    std::cout << "Standard I/O Duration: " << duration.count() << " seconds" << std::endl;
}

// Helper function to count characters using memory-mapped files
void countCharsMemoryMappedIO() {
    int fd = open(filePath, O_RDONLY);
    if (fd == -1) {
        std::cerr << "Error opening file with memory-mapped I/O: " << std::strerror(errno) << std::endl;
        return;
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        std::cerr << "Error getting file size: " << std::strerror(errno) << std::endl;
        close(fd);
        return;
    }

    long long int fileSize = sb.st_size;
    void* mapped = mmap(nullptr, fileSize, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED) {
        std::cerr << "Error memory-mapping the file: " << std::strerror(errno) << std::endl;
        close(fd);
        return;
    }

    long long int count = 0;
    std::cout << "Counting characters using memory-mapped I/O..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    for (char* c = static_cast<char*>(mapped); c < static_cast<char*>(mapped) + fileSize; ++c) {
        ++count;
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Number of characters: " << count << std::endl;
    std::cout << "Memory-Mapped I/O Duration: " << duration.count() << " seconds" << std::endl;

    munmap(mapped, fileSize);
    close(fd);
}

int main() {
    std::cout << "Performance Comparison: Memory-Mapped Files vs Standard I/O" << std::endl;
    countCharsStandardIO();
    countCharsMemoryMappedIO();

    return 0;
}
