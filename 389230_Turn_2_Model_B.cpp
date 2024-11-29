
// data_model.h
#ifndef DATA_MODEL_H
#define DATA_MODEL_H

#include <vector>
#include <cmath>

class DataModel {
public:
    // Data structure for a point on the scatter plot
    struct Point {
        double x;
        double y;
    };

    DataModel();

    // Calculates the random scatter data with a given number of points
    void generateRandomData(int numPoints);

    // Retrieve the vector of points from the model
    const std::vector<Point>& getPoints() const;

    // Setters for xMin, xMax, yMin, yMax ranges to adjust the plot axes
    void setXRange(double min, double max);
    void setYRange(double min, double max);
    double getXMin() const;
    double getXMax() const;
    double getYMin() const;
    double getYMax() const;

private:
    std::vector<Point> m_points;
    double m_xMin, m_xMax, m_yMin, m_yMax;
};
#endif  // DATA_MODEL_H 
 
 
 // data_model.cpp
 #include "data_model.h"
 #include <cstdlib>  // For rand()
 #include <ctime>    // For seeding rand()

 DataModel::DataModel() {
     // Seed rand() for better random distribution
     std::srand(static_cast<unsigned>(std::time(0)));

     // Initialize the plot range
     setXRange(-10.0, 10.0);
     setYRange(-10.0, 10.0);
 }
 
 void DataModel::generateRandomData(int numPoints) {
     m_points.clear();
     for (int i = 0; i < numPoints; ++i) {
         Point p;
         p.x = static_cast<double>(rand()) / RAND_MAX * (m_xMax - m_xMin) + m_xMin;
         p.y = static_cast<double>(rand()) / RAND_MAX * (m_yMax - m_yMin) + m_yMin;
         m_points.push_back(p);
     }
 }

 // Getters and Setters implementations
 ...
 
