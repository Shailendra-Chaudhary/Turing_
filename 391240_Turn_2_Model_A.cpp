#include <iostream>
#include <cstdlib>
#include <cstring>

// Simulated fixed-size memory pool for IoT device
const size_t IoT_MEMORY_SIZE = 4096; // 4 KB
char* IoTMemoryPool = (char*)std::malloc(IoT_MEMORY_SIZE);
if (!IoTMemoryPool) {
    std::cerr << "Failed to allocate memory pool." << std::endl;
    return 1;
}

// Function to allocate memory from the IoT memory pool
void* allocateMemory(size_t size) {
    size_t alignment = 8;
    size_t availableSpace = IoT_MEMORY_SIZE;
    char* current = IoTMemoryPool;

    while (availableSpace >= size + alignment) {
        size_t padding = (alignment - (availableSpace % alignment)) % alignment;
        if (availableSpace - size - padding >= 0) {
            char* allocatedPtr = current + padding;
            availableSpace -= (size + padding);
            memset(allocatedPtr, 0, size);
            return allocatedPtr;
        }
        current += availableSpace;
        availableSpace = IoT_MEMORY_SIZE - (current - IoTMemoryPool);
    }

    std::cerr << "Out of memory: Cannot allocate " << size << " bytes." << std::endl;
    return nullptr;
}

// Function to deallocate memory from the IoT memory pool
void deallocateMemory(void* ptr) {
    // Simple no-op for demonstration; implement a strategy to reuse memory
}

int main() {
    // Simulating memory usage for IoT application
    size_t sensorDataSize = 256;
    void* sensorData1 = allocateMemory(sensorDataSize);
    if (sensorData1) {
        std::cout << "Allocated " << sensorDataSize << " bytes for sensorData1" << std::endl;
    }

    size_t sensorDataSize2 = 512;
    void* sensorData2 = allocateMemory(sensorDataSize2);
    if (sensorData2) {
        std::cout << "Allocated " << sensorDataSize2 << " bytes for sensorData2" << std::endl;
    }

    size_t sensorDataSize3 = 2048;
    void* sensorData3 = allocateMemory(sensorDataSize3);
    if (sensorData3) {
        std::cout << "Allocated " << sensorDataSize3 << " bytes for sensorData3" << std::endl;
    } else {
        std::cerr << "Failed to allocate memory for sensorData3" << std::endl;
    }

    // Simulating data processing
    // ...

    // Deallocate memory (simulated)
    deallocateMemory(sensorData1);
    deallocateMemory(sensorData2);

    return 0;
}
