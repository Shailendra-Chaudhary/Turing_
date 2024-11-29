#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <unordered_set>
#include <chrono>
#include <cstdlib>
#include <cstring>

// A custom class with multiple fields
class MyData {
public:
    int id;
    std::string name;
    float score;

    MyData(int id, const char* name, float score) : id(id), score(score) {
        this->name.assign(name);
    }

    bool operator<(const MyData& other) const {
        return id < other.id;
    }
};

// Function to generate random data
MyData generateRandomData() {
    const char* names[] = {"Alice", "Bob", "Charlie", "David", "Emma"};
    int id = std::rand() % 100000;
    const char* name = names[std::rand() % 5];
    float score = static_cast<float>(std::rand()) / RAND_MAX;
    return MyData(id, name, score);
}

// Function to measure time
template <typename Container>
std::chrono::duration<double> measureTime(Container& container, int n, bool isInsert) {
    auto start = std::chrono::high_resolution_clock::now();

    if (isInsert) {
        for (int i = 0; i < n; ++i) {
            container.insert(generateRandomData());
        }
    } else {
        auto it = container.begin();
        for (int i = 0; i < n; ++i) {
            if (it == container.end()) {
                it = container.begin();
            }
            std::next(it);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    return end - start;
}

int main() {
    std::srand(std::time(0));
    const int n = 1000000;  // Number of elements to insert and search

    // Insertion performance comparison
    std::cout << "Insertion Performance Comparison:\n";
    std::vector<MyData> vec;
    vec.reserve(n);  // Optimize memory allocation
    auto vecInsertTime = measureTime(vec, n, true);
    std::cout << "std::vector: " << vecInsertTime.count() << " seconds\n";

    std::list<MyData> lst;
