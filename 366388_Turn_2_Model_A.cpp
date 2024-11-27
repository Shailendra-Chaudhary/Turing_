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

// Test fixture with custom memory management in SetUp and TearDown
class MemoryManagementTestFixture : public ::testing::Test {
public:
    void SetUp() override {
        // Allocate resources using the custom allocator
        int_ptr = customAllocate<int>();
        *int_ptr = 42;
    }

    void TearDown() override {
        // Deallocate resources using the custom allocator
        customDeallocate<int>(int_ptr);
        int_ptr = nullptr;
    }

    // Pointer allocated using the custom allocator
    int* int_ptr = nullptr;
};

// Test cases using the fixture
TEST_F(MemoryManagementTestFixture, TestCustomAllocation) {
    EXPECT_EQ(*int_ptr, 42);
}

TEST_F(MemoryManagementTestFixture, TestAccessAfterDeallocation) {
    // Attempting to access the pointer after deallocation in a test would result in undefined behavior
    // This test serves as an example of how memory is managed within the fixture
    EXPECT_NE(int_ptr, nullptr); // Expected to pass, since TearDown hasn't been called yet
}

// Main function
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
