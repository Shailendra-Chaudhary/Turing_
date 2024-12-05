#include <iostream>
#include <vector>
#include <bitset>
#include <functional>
#include <array>

const size_t BITSET_SIZE = 1024*1024;  // Example for 1 million bits
const size_t CACHE_LINE_SIZE = 64;     // Typical cache line size in bytes

class BloomFilter {
public:
    BloomFilter(size_t nHashFunctions)
        : mBits(), mHashFunctions(nHashFunctions) {
        // Ensure that the bit array is aligned to the cache line size
        mBits.assign((BITSET_SIZE + 63) / 64, 0);
    }
    
    // Adds an element to the Bloom filter
    void add(const std::string& element) {
        for (size_t i = 0; i < mHashFunctions; ++i) {
            size_t hash = hash_mod(element, i);
            mBits[hash / 64] |= (1ULL << (hash % 64));
        }
    }
    
    // Checks if an element may be in the Bloom filter
    bool mayContain(const std::string& element) const {
        for (size_t i = 0; i < mHashFunctions; ++i) {
            size_t hash = hash_mod(element, i);
            if ((mBits[hash / 64] & (1ULL << (hash % 64))) == 0) {
                return false;
            }
        }
        return true;
    }
    
private:
    std::vector<uint64_t> mBits;
    size_t mHashFunctions;
    
    // Simple hash function modulated over the bitset size
    // Using std::hash combined with salt for simplicity    
    size_t hash_mod(const std::string& data, size_t salt) const {
        return (std::hash<std::string>{}(data) + salt) % BITSET_SIZE;
    }
};

int main() {
    // Create a Bloom filter with 3 hash functions
    BloomFilter bf(3);
    
    bf.add("hello");
    bf.add("world");
    
    std::cout << "May contain 'hello': " << bf.mayContain("hello") << "\n";
    std::cout << "May contain 'unknown': " << bf.mayContain("unknown") << "\n";
    return 0;
}
