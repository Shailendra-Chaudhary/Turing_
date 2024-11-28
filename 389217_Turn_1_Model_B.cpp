#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <algorithm>
#include <mutex>

// Function to count the occurrences of 5 in a subvector
void count_fives(const std::vector<int>& vec, size_t start, size_t end, std::atomic<int>& count, std::mutex& mtx) {
    int local_count = 0;
    for (size_t i = start; i < end; ++i) {
        if (vec[i] == 5) {
            local_count++;
        }
    }
    // Use mutex to protect concurrent access to count
    std::lock_guard<std::mutex> lock(mtx);
    count += local_count;
}
 
int main() {
    const int NUM_THREADS = 4;
    const int VECTOR_SIZE = 10000000;
    std::vector<int> vec(VECTOR_SIZE);
    
    // Generate random numbers in the vector
    std::generate(vec.begin(), vec.end(), std::rand);
    
    std::atomic<int> count(0);
    std::mutex mtx;
    
    size_t chunk_size = VECTOR_SIZE / NUM_THREADS;
    std::vector<std::thread> threads;
    
    // Create threads and assign each thread a subvector to process
    for (int i = 0; i < NUM_THREADS; ++i) {
        size_t start = i * chunk_size;
        size_t end = (i + 1) * chunk_size;
        if (i == NUM_THREADS - 1) {
            end = VECTOR_SIZE;
        }
        threads.push_back(std::thread(count_fives, std::cref(vec), start, end, std::ref(count), std::ref(mtx)));
    }
    
    // Join all threads
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Print the result
    std::cout << "Count of 5 in the vector: " << count << std::endl;
    return 0;
}
