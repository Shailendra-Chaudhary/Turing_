#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>
#include <map>

// Function to generate random integers within the specified range
auto generate_random_data(size_t count, int min, int max) -> std::vector<int> {
    std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<> distribution(min, max);
    std::vector<int> data(count);
    std::generate(data.begin(), data.end(), [&]() { return distribution(engine); });
    return data;
}

// Time the insertion operation for a given STL container
template<typename Container>
auto benchmark_insertion(size_t num_elements) -> double {
    Container container;
    auto data = generate_random_data(num_elements, 0, num_elements);
    
    auto start = std::chrono::high_resolution_clock::now();

    for (const auto& element : data) {
        container.insert(element);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

// Time the search operation for a given STL container
template<typename Container>
auto benchmark_search(size_t num_elements) -> double {
    Container container;
    auto data = generate_random_data(num_elements, 0, num_elements);

    // Create a copy for searching
    auto search_data = data;
    std::sort(search_data.begin(), search_data.end());

    auto start = std::chrono::high_resolution_clock::now();

    for (const auto& element : search_data) {
        container.find(element);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

int main() {
    const size_t num_elements = 1'000'000; // One million elements for benchmarking

    std::cout << "Benchmarking STL Containers for HFT Systems:\n";
    std::cout << "----------------------------------------\n";

    std::cout << "Vector Insertion: ";
    auto vector_insert_time = benchmark_insertion<std::vector<int>>(num_elements);
    std::cout << std::fixed << std::setprecision(6) << vector_insert_time << " seconds\n";

    std::cout << "Vector Search: ";
    auto vector_search_time = benchmark_search<std::vector<int>>(num_elements);
    std::cout << std::fixed << std::setprecision(6) << vector_search_time << " seconds\n";

    std::cout << "Unordered_map Insertion: ";
    auto unordered_map_insert_time = benchmark_insertion<std::unordered_map<int, int>>(num_elements);
    std::cout << std::fixed << std::setprecision(6) << unordered_map_insert_time << " seconds\n";

    std::cout << "Unordered_map Search: ";
    auto unordered_map_search_time = benchmark_search<std::unordered_map<int, int>>(num_elements);
    std::cout << std::fixed << std::setprecision(6) << unordered_map_search_time << " seconds\n";

    std::cout << "Map Insertion: ";
    auto map_insert_time = benchmark_insertion<std::map<int, int>>(num_elements);
    std::cout << std::fixed << std::setprecision(6) << map_insert_time << " seconds\n";

    std::cout << "Map Search: ";
    auto map_search_time = benchmark_search<std::map<int, int>>(num_elements);
    std::cout << std::fixed << std::setprecision(6) << map_search_time << " seconds\n";

    return 0;
}
