#include <iostream>
#include <cstdint>

#pragma pack(push, 1) // Disable padding to minimize memory usage

// Struct with bit-fields and exact-width types
struct DeviceStatus {
    uint8_t deviceID; // 8 bits for ID
    unsigned int active: 1;  // 1 bit for active status
    unsigned int errorLevel: 3;  // 3 bits for error level (0-7)
    unsigned int signalStrength: 4;  // 4 bits for signal strength (0-15)

    int16_t temperature; // 16 bits for temperature data
    int16_t pressure;    // 16 bits for pressure data
};

// Functionality to manage DeviceStatus
void printDeviceStatus(const DeviceStatus& status) {
    std::cout << "Device ID: " << static_cast<int>(status.deviceID)
              << ", Active: " << status.active
              << ", Error Level: " << static_cast<int>(status.errorLevel)
              << ", Signal Strength: " << static_cast<int>(status.signalStrength)
              << ", Temperature: " << status.temperature
              << ", Pressure: " << status.pressure << std::endl;
}

#pragma pack(pop) // Reset to default structure packing

int main() {
    DeviceStatus devices[10]; // Array of DeviceStatus for 10 devices
    
    for (uint8_t i = 0; i < 10; ++i) {
        devices[i].deviceID = i;
        devices[i].active = 1;
        devices[i].errorLevel = i % 8;
        devices[i].signalStrength = i % 16;
        devices[i].temperature = 25 + i;  // Example temperature
        devices[i].pressure = 1000 + i;   // Example pressure
    }

    for (auto& device : devices) {
        printDeviceStatus(device);
    }

    return 0;
}
