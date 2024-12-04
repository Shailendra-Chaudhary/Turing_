#include <iostream>
#include <vector>
#include <cstring>

// Emulate a small memory buffer typical of an IoT device
constexpr size_t MEMORY_POOL_SIZE = 512; // 512 bytes

class IoTMemoryManager {
public:
    IoTMemoryManager() : used_memory(0) {
        std::memset(memory_pool, 0, MEMORY_POOL_SIZE);
    }

    void* allocate(size_t size) {
        if (used_memory + size > MEMORY_POOL_SIZE) {
            std::cerr << "Error: Not enough memory to allocate " << size << " bytes." << std::endl;
            return nullptr;
        }

        void* ptr = memory_pool + used_memory;
        used_memory += size;
        return ptr;
    }

    void deallocate(void* ptr) {
        // No complicated memory management; assuming simple scenarios
        // Actual deallocation logic would be necessary for real use cases
    }

    size_t availableMemory() const {
        return MEMORY_POOL_SIZE - used_memory;
    }

private:
    char memory_pool[MEMORY_POOL_SIZE];
    size_t used_memory;
};

void exampleIoTDeviceOperation() {
    IoTMemoryManager memoryManager;

    std::cout << "Initial available memory: " << memoryManager.availableMemory() << " bytes" << std::endl;

    struct SensorData {
        int id;
        float value;
    };

    // Simulate data from a sensor with constrained memory resources
    SensorData* sensorBuffer = static_cast<SensorData*>(memoryManager.allocate(sizeof(SensorData) * 5));
    if (!sensorBuffer) {
        std::cerr << "Failed to allocate memory for sensor data." << std::endl;
        return;
    }

    // Initialize sensor data with dummy values
    for (int i = 0; i < 5; ++i) {
        sensorBuffer[i].id = i + 1;
        sensorBuffer[i].value = i * 1.1f;
    }

    std::cout << "After allocating sensor data, available memory: " << memoryManager.availableMemory() << " bytes" << std::endl;

    // Print out sensor data to ensure everything is correctly stored
    for (int i = 0; i < 5; ++i) {
        std::cout << "Sensor ID: " << sensorBuffer[i].id << ", Value: " << sensorBuffer[i].value << std::endl;
    }

    // Here we assume deallocation happens when the data is no longer needed
    memoryManager.deallocate(sensorBuffer);

    std::cout << "Simulation complete." << std::endl;
}

int main() {
    exampleIoTDeviceOperation();
    return 0;
}
