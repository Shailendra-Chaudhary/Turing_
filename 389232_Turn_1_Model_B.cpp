#include <iostream>
#include <vector>
#include <future>
#include <chrono>

// A computationally intensive task
int computationallyIntensiveTask(int input) {
    int result = 0;
    for (int i = 0; i < 100000000; ++i) {
        result += input * i;
    }
    return result;
}

int main() {
    const int num_tasks = 10;
    std::vector<std::future<int>> results;

    // Launch tasks asynchronously using std::async
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_tasks; ++i) {
        results.push_back(std::async(std::launch::async, computationallyIntensiveTask, i));
    }

    // Wait for all tasks to complete and retrieve results
    int total_result = 0;
    for (int i = 0; i < num_tasks; ++i) {
        total_result += results[i].get();
    }
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the execution time
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Total result: " << total_result << std::endl;
    std::cout << "Execution time: " << duration << " microseconds" << std::endl;
    return 0;
}
