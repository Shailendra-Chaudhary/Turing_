#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <cmath>
#include <bitset>

class CacheAwareBloomFilter {
public:
    CacheAwareBloomFilter(size_t capacity, double falsePositiveRate) {
        if (falsePositiveRate <= 0 || falsePositiveRate >= 1) {
            throw std::invalid_argument("False positive rate must be between 0 and 1");
        }

        // Number of bits in the Bloom filter
        m = -static_cast<size_t>(capacity * std::log(falsePositiveRate) / (std::log(2) * std::log(2)));

        // Number of hash functions
        k = static_cast<size_t>(m / capacity);
        if (k < 1) k = 1;

        // Align the bit array with cache lines
        size_t cacheLineSize = 64; // Typical cache line size
        size_t bitArraySize = (m + cacheLineSize * 8 - 1) / (cacheLineSize * 8) * cacheLineSize * 8;
        bitArray.resize(bitArraySize, false);
    }

    void add(const std::string& item) {
        for (size_t i = 0; i < k; ++i) {
            bitArray[hashFunction(item, i) % m] = true;
        }
    }

    bool contains(const std::string& item) const {
        for (size_t i = 0; i < k; ++i) {
            if (!bitArray[hashFunction(item, i) % m]) {
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
        return std::hash<std::string>{}(item) + i * 0x9e3779b1;
    }
};

int main() {
    CacheAwareBloomFilter bloomFilter(10000, 0.01);
    bloomFilter.add("apple");
    bloomFilter.add("banana");

    std::cout << "Contains 'apple': " << bloomFilter.contains("apple") << std::endl;
    std::cout << "Contains 'banana': " << bloomFilter.contains("banana") << std::endl;
    std::cout << "Contains 'orange': " << bloomFilter.contains("orange") << std::endl;

    return 0;
}
