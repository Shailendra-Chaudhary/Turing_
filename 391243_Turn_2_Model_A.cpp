#include <iostream>
#include <cstdint>
#include <cstring>
#include <cassert>

// Static array size
#define POOL_SIZE 10
#define SIZE_OF_ITEM 20

// Memory pool structure
struct MemoryPool {
    char memory[POOL_SIZE * SIZE_OF_ITEM];
    int nextAvailableIndex = 0;

    // Allocate memory from the pool
    void* allocate(size_t size) {
        assert(size <= SIZE_OF_ITEM);
        assert(nextAvailableIndex < POOL_SIZE);

        void* ptr = &memory[nextAvailableIndex * SIZE_OF_ITEM];
        nextAvailableIndex++;
        return ptr;
    }

    // Free memory back to the pool
    void free(void* ptr) {
        assert(ptr >= memory && ptr < memory + POOL_SIZE * SIZE_OF_ITEM);
        int index = (ptr - memory) / SIZE_OF_ITEM;
        nextAvailableIndex = index + 1; // Reinsert at the first position
    }
};

// Example class using a memory pool
class SensorData {
public:
    uint8_t sensorId;
    uint16_t reading;
    char description[10];

    SensorData(uint8_t id, uint16_t reading, const char* desc)
        : sensorId(id), reading(reading) {
        strncpy(description, desc, sizeof(description));
    }

    static SensorData* create(MemoryPool& pool, uint8_t id, uint16_t reading, const char* desc) {
        SensorData* data = (SensorData*)pool.allocate(sizeof(SensorData));
        new (data) SensorData(id, reading, desc);
        return data;
    }

    void destroy(MemoryPool& pool) {
        this->~SensorData();
        pool.free(this);
    }

    void print() const {
        std::cout << "Sensor ID: " << (int)sensorId
                  << ", Reading: " << reading
                  << ", Description: " << description << std::endl;
    }
};

int main() {
    MemoryPool memoryPool;

    // Create some SensorData objects using the memory pool
    SensorData* sensor1 = SensorData::create(memoryPool, 1, 1023, "Temperature Sensor");
    SensorData* sensor2 = SensorData::create(memoryPool, 2, 512, "Humidity Sensor");

    sensor1->print();
    sensor2->print();

    // Destroy the objects to free memory back to the pool
    sensor1->destroy(memoryPool);
    sensor2->destroy(memoryPool);

    return 0;
}
