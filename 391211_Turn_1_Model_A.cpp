#include <iostream>
#include <vector>
#include <cstdlib>
#include <new>

// Custom type trait to determine if a type should be allocated on the heap or in-place
template <typename T>
struct ShouldAllocateHeap {
    static constexpr bool value = !std::is_trivial<T>::value || sizeof(T) > 16; // Assume threshold of 16 bytes
};

template <typename T>
class TemplateAllocator {
public:
    T* allocate() {
        return ShouldAllocateHeap<T>::value 
                ? new T()                  // Heap allocation for non-trivial or large objects
                : std::allocate_aligned<T>(alignof(T), sizeof(T), &storage_); // In-place allocation for trivial or small objects
    }

    void deallocate(T* ptr) {
        if (ShouldAllocateHeap<T>::value) {
            delete ptr;
        } else {
            std::deallocate_aligned(ptr, sizeof(T), alignof(T));
        }
    }

private:
    // In-place storage for small/trivial objects
    std::aligned_storage_t<16, alignof(std::max_align_t)> storage_;
};

int main() {
    // Example usage with a non-trivial and large object
    struct LargeStruct {
        char data[1000];
    };

    TemplateAllocator<LargeStruct> allocatorLarge;
    LargeStruct* largePtr = allocatorLarge.allocate();
    std::cout << "LargeStruct pointer: " << largePtr << std::endl;

    // Example usage with a trivial and small object
    struct SmallStruct {
        int data = 0;
    };

    TemplateAllocator<SmallStruct> allocatorSmall;
    SmallStruct* smallPtr = allocatorSmall.allocate();
    std::cout << "SmallStruct pointer: " << smallPtr << std::endl;

    // Deallocate resources
    allocatorLarge.deallocate(largePtr);
    allocatorSmall.deallocate(smallPtr);

    return 0;
}
