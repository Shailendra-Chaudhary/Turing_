#include <iostream>
#include <cstdint>

// Custom data structure with bit-fields to optimize memory usage
struct SensorData {
    uint8_t sensorId;         // 8 bits for sensor ID

    // Bit-fields used for flags and status, compactly stored
    unsigned int isActive : 1; // 1 bit for active status
    unsigned int errorCode : 3; // 3 bits for error code (0-7)
    unsigned int dataSize : 4;  // 4 bits for data size (0-15)
    
    uint16_t reading;         // 16 bits for sensor reading
};

// Compact enum type for mode, defaults to smallest integer type that can hold all the values
enum class Mode : uint8_t {
    OFF = 0,
    ON = 1,
    SLEEP = 2
};

// Example class that uses compact structures
class Sensor {
public:
    SensorData data;
    Mode mode;

    Sensor(uint8_t id, uint16_t reading, bool active, uint8_t error, uint8_t size, Mode m)
        : mode(m) {
        data.sensorId = id;
        data.reading = reading;
        data.isActive = active;
        data.errorCode = error;
        data.dataSize = size;
    }

    void print() const {
        std::cout << "Sensor ID: " << (int)data.sensorId 
                  << ", Reading: " << data.reading
                  << ", Active: " << data.isActive 
                  << ", Error Code: " << (int)data.errorCode
                  << ", Data Size: " << (int)data.dataSize
                  << ", Mode: " << static_cast<int>(mode) << std::endl;
    }
};

int main() {
    Sensor sensor1(1, 1023, true, 2, 5, Mode::ON);
    sensor1.print();

    return 0;
}
