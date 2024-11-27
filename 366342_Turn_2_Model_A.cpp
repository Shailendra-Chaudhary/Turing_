#include <iostream>
#include <vector>
#include <cmath>

// Function to calculate the mean of a vector
double calculateMean(const std::vector<double>& data) {
    return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}

// Function to calculate the covariance between two vectors
double calculateCovariance(const std::vector<double>& x, const std::vector<double>& y) {
    double meanX = calculateMean(x);
    double meanY = calculateMean(y);
    double covariance = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
        covariance += (x[i] - meanX) * (y[i] - meanY);
    }
    return covariance / (x.size() - 1);
}

// Function to calculate the slope (m)
double calculateSlope(const std::vector<double>& x, const std::vector<double>& y) {
    double covariance = calculateCovariance(x, y);
    double varianceX = calculateCovariance(x, x);
    return covariance / varianceX;
}

// Function to calculate the intercept (b)
double calculateIntercept(const std::vector<double>& x, const std::vector<double>& y, double slope) {
    double meanX = calculateMean(x);
    double meanY = calculateMean(y);
    return meanY - slope * meanX;
}

// Function to predict using linear regression
double predict(double x, double slope, double intercept) {
    return slope * x + intercept;
}

int main() {
    // Example sensor data (time series)
    const std::vector<double> sensorData = {1.0, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0};

    // Create vectors for x and y
    std::vector<double> x; // Time (index)
    std::vector<double> y; // Sensor values

    // Fill x and y vectors
    for (size_t i = 0; i < sensorData.size(); ++i) {
        x.push_back(i);
        y.push_back(sensorData[i]);
    }

    // Calculate slope and intercept
    double slope = calculateSlope(x, y);
    double intercept = calculateIntercept(x, y, slope);

    std::cout << "Slope (m): " << slope << std::endl;
    std::cout << "Intercept (b): " << intercept << std::endl;

    // Predict the next sensor value
    int nextIndex = sensorData.size();
    double nextSensorValue = predict(nextIndex, slope, intercept);

    std::cout << "Predicted sensor value at time " << nextIndex << ": " << nextSensorValue << std::endl;

    return 0;
}
