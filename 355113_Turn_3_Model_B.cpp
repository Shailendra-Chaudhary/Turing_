#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <chrono>
#include <random>

using namespace std;

template<typename Container>
void insert_elements(Container& container, size_t n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, n * 1000);
    
    for (size_t i = 0; i < n; ++i) {
        container.insert(dis(gen));
    }
}

template<typename Container>
void search_elements(const Container& container, size_t n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, n * 1000);
    
    for (size_t i = 0; i < n; ++i) {
        auto key = dis(gen);
        container.find(key);
    }
}

template<typename Container>
void benchmark(const string& name, size_t n) {
    Container container;

    auto start_time = chrono::high_resolution_clock::now();
    insert_elements(container, n);
    auto end_time = chrono::high_resolution_clock::now();
    auto insert_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();

    start_time = chrono::high_resolution_clock::now();
    search_elements(container, n);
    end_time = chrono::high_resolution_clock::now();
    auto search_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();

    cout << "Container: " << name << "\n";
    cout << "  - Insert Time: " << insert_time << " ns\n";
    cout << "  - Search Time: " << search_time << " ns\n";
    cout << "  - Total Time: " << (insert_time + search_time) << " ns\n";
    cout << "-----------------\n";
}

int main() {
    const size_t num_elements = 1'000'000; // 1 million

    cout << "Benchmarking STL Containers for Simulated Trading:\n";

    benchmark("vector", num_elements);
    benchmark("deque", num_elements);
    benchmark("list", num_elements);
    benchmark("set", num_elements);
    benchmark("unordered_set", num_elements);
    benchmark("map", num_elements);
    benchmark("unordered_map", num_elements);

    return 0;
}
