#include <iostream>
#include <ctime>
#include <thread>

// Function to simulate a real-time task
void processData() {
    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
        // Simulate work
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        
        // Assert that some condition is true
        assert(i % 1000 == 0, "Expected i to be divisible by 1000");
    }

    clock_t end = clock();
    double time_taken = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    std::cout << "Time taken: " << time_taken << " seconds" << std::endl;
}

int main() {
    std::thread dataProcessor(processData);

    // Do some other real-time tasks...

    dataProcessor.join();

    return 0;
}
