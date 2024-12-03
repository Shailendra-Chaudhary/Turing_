#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <chrono>

// Simulation of a sensor data structure
struct SensorData {
    int sensorId;
    std::vector<int> measurements;
};

// Simulating sensor data collection
SensorData gatherData(int sensorId) {
    // For simplicity, pretend each sensor returns a set of incrementing values
    return SensorData{
        sensorId,
        {sensorId * 10, sensorId * 10 + 1, sensorId * 10 + 2}
    };
}

// Process sensor data
void processData(SensorData data) {
    std::cout << "Processing data from Sensor " << data.sensorId << ": ";
    for(int val : data.measurements) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

// Managing the work pool for processing
class SensorNetworkProcessor {
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

                if(stopping && dataQueue.empty()) {
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
    SensorNetworkProcessor(size_t numThreads) {
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back(&SensorNetworkProcessor::workerThread, this);
        }
    }

    // Destructor to clean up and wait for existing tasks to finish
    ~SensorNetworkProcessor() {
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
    const int numSensors = 5;       // Assume we have 5 sensors for this example
    const int numProcessingThreads = 3; // Number of threads to use for processing

    SensorNetworkProcessor processor(numProcessingThreads);

    std::vector<std::future<SensorData>> futures; // For asynchronous data collection

    // Simulating continuous gathering of sensor data
    for(int i = 0; i < numSensors; ++i) {
        futures.push_back(std::async(std::launch::async, gatherData, i));
    }

    for (auto &future : futures) {
        SensorData data = future.get();
        processor.enqueueData(data);
    }

    // Simulate a short delay before program ends
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}
