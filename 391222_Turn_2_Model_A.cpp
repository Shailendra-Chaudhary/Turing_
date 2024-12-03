#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <chrono>
#include <cstdlib>  // For rand() and srand()

// Simulation of a sensor data structure
struct SensorData {
    int sensorId;
    std::vector<double> measurements;
};

// Simulating sensor data collection
SensorData generateRandomData(int sensorId) {
    SensorData data;
    data.sensorId = sensorId;
    const int measurementCount = rand() % 10 + 1;  // Random number of measurements
    data.measurements.reserve(measurementCount);
    for (int i = 0; i < measurementCount; ++i) {
        data.measurements.push_back(static_cast<double>(rand()) / RAND_MAX);
    }
    return data;
}

// Process sensor data
void processData(const SensorData& data) {
    std::cout << "Processing data from Sensor " << data.sensorId << ": ";
    for (const double& val : data.measurements) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

// Managing the work pool for processing
class ResourceManager {
private:
    std::mutex mu;
    std::condition_variable cond;
    bool stopping = false;
    std::vector<std::thread> workers; // Manage worker threads
    std::queue<SensorData> dataQueue; // Queue for sensor data tasks

    void workerThread() {
        while (true) {
            SensorData dataTask;
            {
                std::unique_lock<std::mutex> lock(mu);
                cond.wait(lock, [&]{ return stopping || !dataQueue.empty(); });

                if (stopping && dataQueue.empty()) {
                    return; // If we're stopping and no work left, exit
                }

                dataTask = dataQueue.front();
                dataQueue.pop();
            }
            processData(dataTask); // Execute task outside of lock
        }
    }

public:
    // Constructor that initializes a pool of worker threads
    ResourceManager(size_t numThreads) {
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back(&ResourceManager::workerThread, this);
        }
    }

    // Destructor to clean up and wait for existing tasks to finish
    ~ResourceManager() {
        {
            std::unique_lock<std::mutex> lock(mu);
            stopping = true;
        }
        cond.notify_all();

        for (std::thread &worker : workers) {
            worker.join();
        }
    }

    // Add new data to the processing queue
    void enqueueData(SensorData data) {
        {
            std::unique_lock<std::mutex> lock(mu);
            dataQueue.push(data);
        }
        cond.notify_one();
    }
};

int main() {
    srand(static_cast<unsigned int>(std::time(0)));  // Seed the random number generator
    const int numSensors = 10;        // Assume we have 10 sensors
    const int numProcessingThreads = 3; // Number of threads for processing
    const int dataCollectionFrequency = 2; // In seconds

    ResourceManager resourceManager(numProcessingThreads);

    // Simulating continuous gathering of sensor data at specified frequency
    while (true) {
        for (int i = 0; i < numSensors; ++i) {
            SensorData data = generateRandomData(i);
            resourceManager.enqueueData(data);
        }

        // Simulate a delay between sensor data collections
        std::this_thread::sleep_for(std::chrono::seconds(dataCollectionFrequency));
    }

    return 0;
}
