#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

void squareElements(std::vector<int>& data, size_t startIndex, size_t endIndex, std::mutex& dataMutex) {
    for (size_t i = startIndex; i < endIndex; ++i) {
        { // Lock the mutex while modifying the vector element
            std::lock_guard<std::mutex> lock(dataMutex);
            data[i] *= data[i];
        }
    }
}

int main() {
    // Sample data
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const size_t numThreads = 4;

    // Calculate the range for each thread
    size_t threadCount = numThreads;
    size_t threadRangeSize = data.size() / threadCount;

    // Create threads
    std::mutex dataMutex; // Mutex to ensure thread safety
    std::thread threads[numThreads];

    // Launch threads
    for (size_t threadIndex = 0; threadIndex < numThreads; ++threadIndex) {
        size_t startIndex = threadIndex * threadRangeSize;
        size_t endIndex = (threadIndex + 1) * threadRangeSize;

        // Handle the case where the last thread might need to process more elements
        if (threadIndex == threadCount - 1) {
            endIndex = data.size();
        }

        threads[threadIndex] = std::thread(squareElements, std::ref(data), startIndex, endIndex, std::ref(dataMutex));
    }

    // Join threads
    for (size_t threadIndex = 0; threadIndex < numThreads; ++threadIndex) {
        threads[threadIndex].join();
    }

    // Output the results
    std::cout << "Squared values: ";
    for (int value : data) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
