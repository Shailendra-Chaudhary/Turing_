            #include <iostream>
            #include <fstream>
            #include <unistd.h>
            #include <fcntl.h>
            #include <sys/mman.h>
            #include <sys/types.h>
            #include <sys/stat.h>
            #include <cerrno>

            #define MMAP_FILE_PATH "/tmp/mmap_data.txt"
            #define DATA_SIZE 1024  // Size of the mapped memory region (1KB)

            const char* EXAMPLE_DATA = "Hello, this is persistent data using memory mapping in IoT!";

            void writeDataToMMappedMemory(void* mappedMemory) {
                strcpy(reinterpret_cast<char*>(mappedMemory), EXAMPLE_DATA);
                std::cout << "Data written to persistent memory using memory mapping." << std::endl;
            }

            void readDataFromMMappedMemory(void* mappedMemory) {
                const char* readData = reinterpret_cast<const char*>(mappedMemory);
                std::cout << "Data read from persistent memory using memory mapping: " << readData << std::endl;
            }

            int main() {
                // Create or truncate the file to the desired data size
                int fd = open(MMAP_FILE_PATH, O_RDWR | O_CREAT | O_TRUNC, 0644);
                if (fd == -1) {
                    perror("Failed to open the file");
                    return 1;
                }

                try {
                    // Map the file into memory
                    void* mappedMemory = mmap(nullptr, DATA_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
                    if (mappedMemory == MAP_FAILED) {
                        throw std::runtime_error("Failed to map memory: " + std::string(strerror(errno)));
                    }

                    // Write data to the mapped memory
                    writeDataToMMappedMemory(mappedMemory);

                    // Close the file descriptor (mapping is still alive)
                    close(fd);

                    // Uncomment this line to read data from mapped memory after writing
                    //readDataFromMMappedMemory(mappedMemory);

                    // Unmap the memory
                    if (munmap(mappedMemory, DATA_SIZE) == -1) {
                        throw std::runtime_error("Failed to unmap memory: " + std::string(strerror(errno)));
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                    if (fd != -1) {
                        close(fd);
                    }
                    return 1;
                }

                return 0;
            }
