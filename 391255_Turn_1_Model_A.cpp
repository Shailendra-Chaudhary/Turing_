#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>
#include <cerrno>

// Function to create a memory-mapped file
void* createMemoryMappedFile(const char* filename, size_t fileSize) {
    int fd = open(filename, O_RDONLY | O_CREAT | O_EXCL, 0644);
    if (fd == -1) {
        std::cerr << "Error opening file: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    if (ftruncate(fd, fileSize) == -1) {
        std::cerr << "Error truncating file: " << strerror(errno) << std::endl;
        close(fd);
        exit(EXIT_FAILURE);
    }

    void* map = mmap(nullptr, fileSize, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (map == MAP_FAILED) {
        std::cerr << "Error mapping file: " << strerror(errno) << std::endl;
        close(fd);
        exit(EXIT_FAILURE);
    }

    return map;
}

// Function to unmap the memory-mapped file
void unmapMemoryMappedFile(void* map, size_t fileSize) {
    munmap(map, fileSize);
    close(fd); // Assuming `fd` is a global variable or accessible in this scope
}

int main() {
    const char* filename = "memory_mapped_file.txt";
    const size_t fileSize = 1024 * 1024; // 1MB for example

    void* map = createMemoryMappedFile(filename, fileSize);
    if (!map) {
        std::cerr << "Unable to create memory-mapped file" << std::endl;
        return EXIT_FAILURE;
    }

    // Example of writing to the memory-mapped file
    char* data = static_cast<char*>(map);
    strcpy(data, "Hello, this is a memory-mapped file!");

    // Example of reading from the memory-mapped file
    std::cout << "Read from memory-mapped file: " << data << std::endl;

    unmapMemoryMappedFile(map, fileSize);

    return EXIT_SUCCESS;
}
