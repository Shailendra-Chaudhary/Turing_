#include <iostream>
#include <cstring>

// Mock functions for output (LED, buzzer, display) to simulate feedback mechanisms
void turnOnLED(int errorCode) {
    std::cout << "LED ON for error code: " << errorCode << std::endl;
}

void soundBuzzer() {
    std::cout << "Buzzer Sound!" << std::endl;
}

void displayMessage(const char* message) {
    std::cout << "Display: " << message << std::endl;
}

// Error codes
enum ErrorCode {
    SUCCESS = 0,
    ERROR_SENSOR_FAILURE = 1,
    ERROR_COMMUNICATION_FAILURE = 2,
    ERROR_OUT_OF_RANGE = 3
};

// Error handling function
void handleError(ErrorCode errorCode) {
    switch (errorCode) {
        case ERROR_SENSOR_FAILURE:
            turnOnLED(errorCode);
            displayMessage("Sensor Failure");
            break;
        case ERROR_COMMUNICATION_FAILURE:
            turnOnLED(errorCode);
            soundBuzzer();
            displayMessage("Communication Failure");
            break;
        case ERROR_OUT_OF_RANGE:
            displayMessage("Value Out of Range");
            break;
        case SUCCESS:
            // No action needed for success state
            break;
    }
}

// Mock sensor reading function for simulation
ErrorCode readSensor(int& value) {
    // Simulate sensor read failure
    value = -1;
    return ERROR_SENSOR_FAILURE;
}

// Mock communication function for simulation
ErrorCode sendDataOverNetwork(const char* data) {
    // Simulate communication failure
    return ERROR_COMMUNICATION_FAILURE;
}

int main() {
    int sensorValue;
    ErrorCode error = readSensor(sensorValue);
    
    if (error != SUCCESS) {
        handleError(error);
    } else {
        // Normal operation on successful sensor read
        std::cout << "Sensor Value: " << sensorValue << std::endl;
    }

    // Attempt to send data over the network
    error = sendDataOverNetwork("Test Data");
    
    if (error != SUCCESS) {
        handleError(error);
    } else {
        std::cout << "Data sent successfully." << std::endl;
    }

    return 0;
}
