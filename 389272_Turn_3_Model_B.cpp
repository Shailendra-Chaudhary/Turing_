#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <unordered_set>
#include <list>
#include <algorithm>
#include <chrono>

int main() {
    const int size = 1000000;

    std::vector<int> vec;
    std::deque<int> deq;
    std::set<int> set;
    std::unordered_set<int> uset;
    std::list<int> list;

    // Generate random data
    for (int i = 0; i < size; ++i) {
        int random = rand() % size;
        vec.push_back(random);
        deq.push_back(random);
        set.insert(random);
        uset.insert(random);
        list.push_back(random);
    }

    // Measure time for finding the maximum element using different containers
    auto start = std::chrono::high_resolution_clock::now();
    int max_vec = *std::max_element(vec.begin(), vec.end());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "std::vector: " << (end - start).count() << " seconds. Max element: " << max_vec << std::endl;

    start = std::chrono::high_resolution_clock::now();
    int max_deq = *std::max_element(deq.begin(), deq.end());
    end = std::chrono::high_resolution_clock::now();
    std::cout << "std::deque: " << (end - start).count() << " seconds. Max element: " << max_deq << std::endl;
    
    start = std::chrono::high_resolution_clock::now();
    int max_set = *set.rbegin();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "std::set: " << (end - start).count() << " seconds. Max element: " << max_set << std::endl;

    start = std::chrono::high_resolution_clock::now();
    int max_uset = *uset.rbegin();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "std::unordered_set: " << (end - start).count() << " seconds. Max element: " << max_uset << std::endl;
