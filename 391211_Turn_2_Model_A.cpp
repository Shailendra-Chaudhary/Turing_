#include <iostream>
#include <cstdint>
#include <new>
#include <type_traits>

// Define a custom threshold for small objects
constexpr size_t SMALL_OBJECT_THRESHOLD = 16;

// Type trait to check if an object should be allocated on the heap
template <typename T>
struct ShouldAllocateHeap {
    static constexpr bool value = !std::is_trivial<T>::value || sizeof(T) > SMALL_OBJECT_THRESHOLD;
};

// Template-based memory allocator
template <typename T>
class Allocator {
public:
    T* allocate() {
        if (ShouldAllocateHeap<T>::value) {
            return new T(); // Heap allocation for large or non-trivial objects
        } else {
            // In-place allocation for small, trivial objects
            static_assert(std::is_trivial<T>::value, "In-place allocation requires a trivial type");
            return new (&storage_) T();
        }
    }

    void deallocate(T* ptr) {
        if (ShouldAllocateHeap<T>::value) {
            delete ptr; // Deallocate from heap
        } else {
            ptr->~T(); // Destruct in-place
        }
    }

private:
    // In-place storage for small/trivial objects
    std::aligned_storage_t<SMALL_OBJECT_THRESHOLD, std::max_align_t> storage_;
};

// Example usage
int main() {
    // Non-trivial, large object
    struct LargeObject {
        int a, b, c, d;
        LargeObject() : a(1), b(2), c(3), d(4) {}
    };

    Allocator<LargeObject> allocatorLarge;
    LargeObject* largePtr = allocatorLarge.allocate();
    std::cout << "LargeObject pointer: " << largePtr << std::endl;
    std::cout << "LargeObject values: " << largePtr->a << ", " << largePtr->b << ", " << largePtr->c << ", " << largePtr->d << std::endl;

    // Trivial, small object
    struct SmallObject {
        int value = 0;
    };

    Allocator<SmallObject> allocatorSmall;
    SmallObject* smallPtr = allocatorSmall.allocate();
    std::cout << "SmallObject pointer: " << smallPtr << std::endl;
    std::cout << "SmallObject value: " << smallPtr->value << std::endl;

    // Deallocate resources
    allocatorLarge.deallocate(largePtr);
    allocatorSmall.deallocate(smallPtr);

    return 0;
}
