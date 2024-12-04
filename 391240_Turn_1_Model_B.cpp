#include <iostream>
#include <new>

// Custom allocator for a simple IoT application
class IoTAllocator {
public:
    IoTAllocator(size_t size) : m_size(size), m_used(0) {
        m_memory = new(std::nothrow) char[m_size];
        if (!m_memory) {
            std::cerr << "Failed to allocate memory pool." << std::endl;
            throw std::bad_alloc();
        }
    }

    ~IoTAllocator() {
        delete[] m_memory;
    }

    void* allocate(size_t size) {
        if (m_used + size > m_size) {
            std::cerr << "Out of memory: cannot allocate " << size << " bytes." << std::endl;
            return nullptr;
        }
        
        // Align the memory to 8 bytes
        size_t alignment = 8;
        size_t padding = (alignment - (m_used % alignment)) % alignment;
        if (m_used + padding + size > m_size) {
            std::cerr << "Out of memory: cannot allocate with alignment " << padding + size << " bytes." << std::endl;
            return nullptr;
        }

        void* ptr = m_memory + m_used + padding;
        m_used += (padding + size);
        return ptr;
    }

    void deallocate(void* ptr) {
        // No-op for simplicity. Implement a deallocation strategy as needed.
    }

    void reset() {
        m_used = 0;
    }

    size_t available() const {
        return m_size - m_used;
    }

private:
    char* m_memory;
    size_t m_size;
    size_t m_used;

    // Disable copy and assignment
    IoTAllocator(const IoTAllocator&) = delete;
    IoTAllocator& operator=(const IoTAllocator&) = delete;
};

int main() {
    size_t poolSize = 1024; // 1 KB memory pool
    IoTAllocator allocator(poolSize);

    std::cout << "Available memory: " << allocator.available() << " bytes" << std::endl;

    // Simulating allocation of memory for sensors
    void* sensorData1 = allocator.allocate(256);
    if (sensorData1) std::cout << "Allocated 256 bytes for sensorData1" << std::endl;

    void* sensorData2 = allocator.allocate(512);
    if (sensorData2) std::cout << "Allocated 512 bytes for sensorData2" << std::endl;
    
    std::cout << "Available memory: " << allocator.available() << " bytes" << std::endl;

    // Reset the memory for reuse. Be cautious of dangling pointers!
    allocator.reset();
    std::cout << "Memory reset." << std::endl;

    std::cout << "Available memory: " << allocator.available() << " bytes" << std::endl;

    return 0;
}
