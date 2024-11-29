#include <iostream>
#include <ctime>

// Function to simulate a real-time operation
int processData(int input) {
    // Simulate work by sleeping for a short time
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    // Assert that the input is non-negative
    assert(input >= 0, "Input must be non-negative");
    
    // Simulate processing
    return input + 1;
}

int main() {
    clock_t start = clock();
    
    for (int i = 0; i < 1000; ++i) {
        processData(i);
    }
    
    clock_t end = clock();
    double time_taken = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    
    std::cout << "Time taken: " << time_taken << " seconds" << std::endl;
    
    return 0;
}
