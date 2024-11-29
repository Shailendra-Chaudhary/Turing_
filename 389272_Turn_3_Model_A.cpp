#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <unordered_set>
#include <chrono>
#include <cstdlib>
#include <iomanip>

template <typename Container>
void testContainer(const std::string& name, Container& container, const int n) {
    auto start = std::chrono::high_resolution_clock::now();

    auto generateRandom = [n]() -> int {
        return std::rand() % n;
    };

    for (int i = 0; i < n; ++i) {
        container.insert(generateRandom());
    }

    auto insertTime = std::chrono::high_resolution_clock::now() - start;

    start = std::chrono::high_resolution_clock::now();
    int numElementsFound = 0;
    for (int i = 0; i < n; ++i) {
        if (container.find(i) != container.end()) {
            ++numElementsFound;
        }
    }
    auto lookupTime = std::chrono::high_resolution_clock::now() - start;

    double memoryUsage = static_cast<double>(std::get_size_of<Container>()) + (sizeof(int) * container.size());

    std::cout << name << " (n = " << n << "):" << std::endl;
    std::cout << "  Insertion time: " << insertTime.count() << " seconds" << std::endl;
    std::cout << "  Lookup time: " << lookupTime.count() << " seconds" << std::endl;
    std::cout << "  Memory usage: " << memoryUsage << " bytes" << std::endl;
    std::cout << "  Elements found: " << numElementsFound << std::endl;
    std::cout << std::endl;
}

int main() {
    std::srand(std::time(0));
    const int n = 1000000;

    testContainer<std::vector<int>>("Vector", {}, n);
    testContainer<std::deque<int>>("Deque", {}, n);
    testContainer<std::set<int>>("Set", {}, n);
    testContainer<std::unordered_set<int>>("Unordered set", {}, n);

    return 0;
}
