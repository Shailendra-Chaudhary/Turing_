#include <iostream>

// Define the model coefficients
const float slope = 0.5;
const float intercept = 2.0;

// Function to perform linear regression prediction
float linear_regression_predict(float input) {
    return slope * input + intercept;
}

int main() {
    // Example sensor data
    const float sensor_data[] = {1.0, 3.0, 5.0, 7.0, 9.0};
    
    // Perform predictions
    for (int i = 0; i < sizeof(sensor_data) / sizeof(sensor_data[0]); i++) {
        float prediction = linear_regression_predict(sensor_data[i]);
        std::cout << "Prediction for sensor value " << sensor_data[i] << ": " << prediction << std::endl;
    }

    return 0;
}
