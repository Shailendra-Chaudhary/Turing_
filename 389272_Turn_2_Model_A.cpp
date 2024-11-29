#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <unordered_set>
#include <list>
#include <chrono>
#include <cstdlib>
#include <iomanip>

void measurePerformance(const std::string& containerName, const int n) {
    auto generateRandom = [n]() -> int {
        return std::rand() % n;
    };

    auto measureTime = [&]() -> std::chrono::duration<double> {
        auto start = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::high_resolution_clock::now();
        return end - start;
    };

    auto measureMemory = [&]() -> double {
        auto ptr = &container;
        return static_cast<double>(std::get_size_of<decltype(container)>()) + (sizeof(int) * container.size());
    };

    if (containerName == "vector") {
        std::vector<int> container;
        for (int i = 0; i < n; ++i) {
            container.push_back(generateRandom());
        }
    } else if (containerName == "deque") {
        std::deque<int> container;
        for (int i = 0; i < n; ++i) {
            container.push_back(generateRandom());
        }
    } else if (containerName == "set") {
        std::set<int> container;
        for (int i = 0; i < n; ++i) {
            container.insert(generateRandom());
        }
    } else if (containerName == "unordered_set") {
        std::unordered_set<int> container;
        for (int i = 0; i < n; ++i) {
            container.insert(generateRandom());
        }
    } else if (containerName == "list") {
        std::list<int> container;
        for (int i = 0; i < n; ++i) {
            container.push_back(generateRandom());
        }
    } else {
        std::cerr << "Unrecognized container name: " << containerName << std::endl;
        return;
    }

    auto insertionTime = measureTime();
    double memoryUsage = measureMemory();

    std::cout << "Container: " << containerName << std::endl;
    std::cout << "Insertion time: " << insertionTime.count() << " seconds" << std::endl;
    std::cout << "Memory usage: " << memoryUsage << " bytes" << std::endl;
    std::cout << std::endl;
}

int main() {
    std::srand(std::time(0));
    const int n = 1000000; // Number of elements to insert

    measurePerformance("vector", n);
    measurePerformance("deque", n);
    measurePerformance("set", n);
    measurePerformance("unordered_set", n);
    measurePerformance("list", n);

    return 0;
}
