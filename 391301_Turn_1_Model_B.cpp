#include <vector>
#include <functional>
#include <string>
#include <bitset>

class CacheEfficientBloomFilter {
public:
    CacheEfficientBloomFilter(size_t size, size_t numHashes)
        : byteArray((size + 7) / 8, 0), numHashes(numHashes) {}

    void add(const std::string &item) {
        for (size_t i = 0; i < numHashes; ++i) {
            size_t hashValue = hash(item, i) % (8 * byteArray.size());
            byteArray[hashValue / 8] |= (1 << (hashValue % 8));
        }
    }

    bool contains(const std::string &item) const {
        for (size_t i = 0; i < numHashes; ++i) {
            size_t hashValue = hash(item, i) % (8 * byteArray.size());
            if (!(byteArray[hashValue / 8] & (1 << (hashValue % 8)))) {
                return false;
            }
        }
        return true;
    }

private:
    std::vector<uint8_t> byteArray;
    size_t numHashes;

    size_t hash(const std::string &item, size_t i) const {
        std::hash<std::string> hasher;
        return hasher(item) ^ (i * 0x5bd1e995);
    }
};
