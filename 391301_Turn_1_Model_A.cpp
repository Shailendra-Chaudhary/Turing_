#include <iostream>
#include <vector>
#include <cstdint>
#include <functional>
#include <random>

class BloomFilterCacheEfficient {
public:
    BloomFilterCacheEfficient(size_t size, size_t hashCount, size_t bucketSize)
        : size_(size), hashCount_(hashCount), bucketSize_(bucketSize) {
        bits_.resize(size / bucketSize, std::vector<uint8_t>(bucketSize, 0));
        std::random_device rd;
        std::mt19937 gen(rd());
        for (size_t i = 0; i < hashCount_; ++i) {
            hashes_.push_back(std::bind(&BloomFilterCacheEfficient::hashFunction, this, std::placeholders::_1, i, gen));
        }
    }

    void insert(const std::string& element) {
        for (const auto& hash : hashes_) {
            size_t bucketIndex = hash(element) / bucketSize_;
            size_t bitIndex = hash(element) % bucketSize_;
            bits_[bucketIndex][bitIndex] = 1;
        }
    }

    bool contains(const std::string& element) const {
        for (const auto& hash : hashes_) {
            size_t bucketIndex = hash(element) / bucketSize_;
            size_t bitIndex = hash(element) % bucketSize_;
            if (bits_[bucketIndex][bitIndex] == 0) {
                return false;
            }
        }
        return true;
    }

private:
    std::vector<std::vector<uint8_t>> bits_;
    size_t size_;
    size_t hashCount_;
    size_t bucketSize_;
    std::vector<std::function<size_t(const std::string&)>> hashes_;

    size_t hashFunction(const std::string& element, size_t hashIndex, std::mt19937& gen) const {
        std::uniform_int_distribution<size_t> dist(0, size_ - 1);
        return dist(gen);
    }
};
