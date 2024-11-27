#include <iostream>
#include <memory>
#include <gtest/gtest.h>

// Simple custom memory allocator
class CustomAllocator {
public:
    static void* allocate(std::size_t size) {
        std::cout << "Allocating " << size << " bytes.\n";
        return ::operator new(size);
    }
    
    static void deallocate(void* ptr, std::size_t size) {
        std::cout << "Deallocating " << size << " bytes.\n";
        ::operator delete(ptr);
    }
};

// Helper function to allocate memory using the custom allocator
template<typename T>
T* customAllocate() {
    return reinterpret_cast<T*>(CustomAllocator::allocate(sizeof(T)));
}

// Helper function to deallocate memory using the custom allocator
template<typename T>
void customDeallocate(T* ptr) {
    CustomAllocator::deallocate(ptr, sizeof(T));
}

// Test case to demonstrate custom memory allocator usage
TEST(MemoryManagementTest, CustomAllocator) {
    // Allocate an integer using the custom allocator
    int* num = customAllocate<int>();
    *num = 42;
    
    // Check the value
    EXPECT_EQ(*num, 42);
    
    // Deallocate the memory using the custom allocator
    customDeallocate<int>(num);
}

// Main function
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
