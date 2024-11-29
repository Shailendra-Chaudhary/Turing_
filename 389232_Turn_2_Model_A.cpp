#include <iostream>
#include <vector>
#include <future>
#include <thread>
#include <random>

// Function to simulate and count points for the Monte Carlo method
int simulatePoints(int numPoints) {
    std::mt19937 randomEngine(std::random_device{}());
    std::uniform_real_distribution<> unifDist(0.0, 1.0);

    int inCircle = 0;
    for (int i = 0; i < numPoints; ++i) {
        double x = unifDist(randomEngine);
        double y = unifDist(randomEngine);
        if (x * x + y * y <= 1.0) {
            ++inCircle;
        }
    }
    return inCircle;
}

// Function to perform a Monte Carlo simulation with a specified number of threads
double approximatePi(int totalPoints, int threads) {
    std::vector<std::future<int>> futures;
    int pointsPerThread = totalPoints / threads + (totalPoints % threads > 0);

    // Create and launch threads to perform simulations
    for (int i = 0; i < threads; ++i) {
        futures.emplace_back(std::async(std::launch::async, simulatePoints, pointsPerThread));
    }

    int totalInCircle = 0;
    for (std::future<int>& future : futures) {
        totalInCircle += future.get();
    }

    // Calculate the approximation of π
    return 4.0 * static_cast<double>(totalInCircle) / totalPoints;
}

int main() {
    const int totalPoints = 10'000'000;
    const int threads = 4; // Adjust the number of threads based on your system's capabilities

    double piApproximation = approximatePi(totalPoints, threads);
    std::cout << "Approximation of π: " << piApproximation << std::endl;

    return 0;
}
