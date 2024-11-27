
#include <gtest/gtest.h>

class CustomAllocator {
public:
    void* allocate(size_t bytes) {
        return new (std::nothrow) char[bytes];
    }
    void deallocate(void* ptr) {
        delete[] static_cast<char*>(ptr);
    }
};

void* operator new(size_t bytes, const CustomAllocator& allocator) {
    return allocator.allocate(bytes);
}
void operator delete(void* ptr, const CustomAllocator& allocator) {
    allocator.deallocate(ptr);
}

class ExampleTest : public testing::Test {
protected:
    CustomAllocator customAllocator;
    void* dataPtr = nullptr;

    virtual void SetUp() {
        dataPtr = new (customAllocator) char[100];
    }

    virtual void TearDown() {
        delete static_cast<char*>(dataPtr);
    }
};

TEST_F(ExampleTest, ExampleTestCase) {
    // Use dataPtr here
    ASSERT_NE(dataPtr, nullptr);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
