// Header file to define the model and helper functions
#ifndef LINEAR_REGRESSION_MODEL_H
#define LINEAR_REGRESSION_MODEL_H

#include <cstddef>
#include <array>

// Define the model coefficients
constexpr float slope = 0.5f;
constexpr float intercept = 2.0f;

// Linear regression model class
class LinearRegressionModel {
public:
    // Constructor with optional model coefficients
    LinearRegressionModel(float slope = 0.0f, float intercept = 0.0f) : m_slope(slope), m_intercept(intercept) {}

    // Function to perform linear regression prediction
    float predict(float input) const {
        return m_slope * input + m_intercept;
    }

    // Accessors for model coefficients
    float slope() const { return m_slope; }
    float intercept() const { return m_intercept; }

private:
    float m_slope;
    float m_intercept;
};

// Function to train the linear regression model on historical data
// Returns the trained model coefficients
std::array<float, 2> trainLinearRegressionModel(const float* inputs, const float* outputs, size_t dataSize);

#endif  // LINEAR_REGRESSION_MODEL_H
