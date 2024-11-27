#include <iostream>
#include <vector>
#include <cmath>

// Function to calculate the mean of a vector
float mean(const std::vector<float>& data) {
    float sum = 0;
    for (float value : data) {
        sum += value;
    }
    return sum / data.size();
}

// Function to calculate the covariance of two vectors
float covariance(const std::vector<float>& x, const std::vector<float>& y) {
    float x_mean = mean(x);
    float y_mean = mean(y);
    float cov = 0;
    for (size_t i = 0; i < x.size(); ++i) {
        cov += (x[i] - x_mean) * (y[i] - y_mean);
    }
    return cov / x.size();
}

// Function to calculate the correlation of two vectors
float correlation(const std::vector<float>& x, const std::vector<float>& y) {
    float x_std = std::sqrt(covariance(x, x));
    float y_std = std::sqrt(covariance(y, y));
    if (x_std == 0 || y_std == 0) {
        return 0;
    }
    return covariance(x, y) / (x_std * y_std);
}

// Function to calculate linear regression coefficients
std::pair<float, float> linear_regression_fit(const std::vector<float>& x, const std::vector<float>& y) {
    float slope = correlation(x, y) * std::sqrt(covariance(x, x) / covariance(y, y));
    float intercept = mean(y) - slope * mean(x);
    return {slope, intercept};
}

// Function to predict using the linear regression model
float linear_regression_predict(float x, const std::pair<float, float>& model) {
    return model.first * x + model.second;
}

int main() {
    // Example dataset: time and sensor values
    std::vector<float> time = {1, 2, 3, 4, 5};
    std::vector<float> sensor_values = {2.0, 3.5, 4.0, 4.5, 5.0};

    // Fit the linear regression model
    std::pair<float, float> model = linear_regression_fit(time, sensor_values);

    // Output the model coefficients
    std::cout << "Slope: " << model.first << std::endl;
    std::cout << "Intercept: " << model.second << std::endl;

    // Example prediction for a new time value
    float new_time = 6;
    float prediction = linear_regression_predict(new_time, model);
    std::cout << "Predicted sensor value for time " << new_time << ": " << prediction << std::endl;

    return 0;
}
