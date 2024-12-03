#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <future>
#include <atomic>

// Simulates sensor data
struct SensorData {
    int sensorId;
    std::vector<int> measurements;
};

// Function to gather data
SensorData gatherData(int sensorId) {
    return SensorData{
        sensorId,
        {sensorId * 10, sensorId * 10 + 1, sensorId * 10 + 2}
    };
}

// Function for processing sensor data
void processSensorData(SensorData data) {
    std::cout << "Processing data from Sensor " << data.sensorId << ": ";
    for (int measure : data.measurements) {
        std::cout << measure << " ";
    }
    std::cout << std::endl;
}

// Manages the dynamic resource allocation
class DynamicResourceManager {
private:
    std::mutex mu;
    std::condition_variable cond;
    std::vector<std::thread> workers;
    std::deque<SensorData> dataQueue;
    std::atomic<bool> stopping;
    
    void workerFunction() {
        while (true) {
            SensorData dataTask;
            {
                std::unique_lock<std::mutex> lock(mu);
                cond.wait(lock, [&] { return stopping.load() || !dataQueue.empty(); });
                
                if (stopping.load() && dataQueue.empty()) {
                    return;
                }

                dataTask = dataQueue.front();
                dataQueue.pop_front();
            }
            processSensorData(dataTask);
        }
    }

public:
    DynamicResourceManager() : stopping(false) {}

    void startWorkers(size_t numberOfThreads) {
        for (size_t i = 0; i < numberOfThreads; ++i) {
            workers.push_back(std::thread(&DynamicResourceManager::workerFunction, this));
        }
    }

    // Shut down all workers and clean up
    void shutdown() {
        {
            std::lock_guard<std::mutex> lock(mu);
            stopping = true;
        }
        cond.notify_all();

        for (std::thread &worker : workers) {
            worker.join();
        }
    }

    // Adjust the pool of worker threads based on load
    void adjustWorkers(size_t numberOfThreads) {
        if (numberOfThreads != workers.size()) {
            shutdown();
            workers.clear();
            stopping = false;
            startWorkers(numberOfThreads);
        }
    }

    // Enqueue new data to process
    void enqueueData(SensorData data) {
        {
            std::lock_guard<std::mutex> lock(mu);
            dataQueue.push_back(data);
        }
        cond.notify_one();
    }
};

int main() {
    DynamicResourceManager manager;
    size_t initialNumberOfThreads = 2;
    manager.startWorkers(initialNumberOfThreads);

    const int numSensors = 5;
    std::vector<std::future<SensorData>> futures;
    
    for (int i = 0; i < numSensors; ++i) {
        futures.push_back(std::async(std::launch::async, gatherData, i));
    }

    // Fetch and queue each sensor's data for processing
    for (auto &future : futures) {
        SensorData data = future.get();
        manager.enqueueData(data);
    }

    // Monitoring workload and adjusting worker count as needed (e.g., based on mock conditions)
    size_t dynamicThreads = 3; // Simulated new workload decision
    manager.adjustWorkers(dynamicThreads);

    // Fixed delay to simulate continued execution
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // After processing, ensure shutdown is properly called before exiting
    manager.shutdown();

    return 0;
}
