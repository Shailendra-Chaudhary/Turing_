#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cstdint>
#include <random>
#include <algorithm>

class CacheOptimizedBloomFilter {
public:
    CacheOptimizedBloomFilter(size_t capacity, double falsePositiveRate) {
        if (falsePositiveRate <= 0 || falsePositiveRate >= 1) {
            throw std::invalid_argument("False positive rate must be between 0 and 1");
        }

        // Number of bits in the Bloom filter
        m = -static_cast<size_t>(capacity * std::log(falsePositiveRate) / std::log(2.0 * std::log(2.0)));

        // Number of hash functions
        k = static_cast<size_t>(m / capacity);
        if (k < 1) k = 1;

        // Initialize the bit array
        bitArray.resize(m, false);
    }

    void add(const std::string& item) {
        for (size_t i = 0; i < k; ++i) {
            bitArray[hashFunction(item, i)] = true;
        }
    }

    bool contains(const std::string& item) const {
        for (size_t i = 0; i < k; ++i) {
            if (!bitArray[hashFunction(item, i)]) {
                return false;
            }
        }
        return true;
    }

private:
    size_t m; // Number of bits in the Bloom filter
    size_t k; // Number of hash functions
    std::vector<bool> bitArray; // The bit array

    // A simple hash function
    size_t hashFunction(const std::string& item, size_t i) const {
        using namespace std;
        static const auto seed = default_random_engine{chrono::high_resolution_clock::now().time_since_epoch().count()};
        auto hash = hasher<string>{};

        auto randomize = [&seed, i](size_t h) {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, m - 1);
            h = dis(gen) ^ h;
            return h;
        };

        return randomize(hash(item) + i);
    }
};

int main() {
    CacheOptimizedBloomFilter bloomFilter(10000, 0.01);
    bloomFilter.add("apple");
    bloomFilter.add("banana");

    cout << "Contains 'apple': " << bloomFilter.contains("apple") << endl;
    cout << "Contains 'banana': " << bloomFilter.contains("banana") << endl;
    cout << "Contains 'orange': " << bloomFilter.contains("orange") << endl;

    return 0;
}
