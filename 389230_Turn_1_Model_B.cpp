#include <vector>

class Model {

private:
    std::vector<float> m_xData;
    std::vector<float> m_yData;

public:
    // Add data points to the model
    void addDataPoint(float x, float y) {
        m_xData.push_back(x);
        m_yData.push_back(y);
    }
    
    // Clear all data points
    void clearData() {
        m_xData.clear();
        m_yData.clear();
    }

    // Getters for data points
    const std::vector<float>& getXData() const { return m_xData; }
    const std::vector<float>& getYData() const { return m_yData; }
};
