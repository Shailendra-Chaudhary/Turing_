#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

void processData(const char* data, size_t length) {
    // Simple example of processing data
    for (size_t i = 0; i < length; ++i) {
        std::cout << data[i]; // For example, just print characters
    }
    std::cout << std::endl;
}

int main() {
    const char* filePath = "large_dataset.bin";

    // Open the file
    int fd = open(filePath, O_RDONLY);
    if (fd == -1) {
        std::cerr << "Error opening file: " << std::strerror(errno) << std::endl;
        return 1;
    }

    // Get the file size
    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        std::cerr << "Error getting file size: " << std::strerror(errno) << std::endl;
        close(fd);
        return 1;
    }
    size_t fileSize = sb.st_size;

    // Memory-map the file
    void* mapped = mmap(nullptr, fileSize, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED) {
        std::cerr << "Error memory-mapping the file: " << std::strerror(errno) << std::endl;
        close(fd);
        return 1;
    }

    // Process the data
    processData(static_cast<const char*>(mapped), fileSize);

    // Unmap the file
    if (munmap(mapped, fileSize) == -1) {
        std::cerr << "Error un-mapping the file: " << std::strerror(errno) << std::endl;
    }

    // Close the file
    close(fd);

    return 0;
}
