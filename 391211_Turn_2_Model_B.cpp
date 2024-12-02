#include <iostream>
#include <type_traits>
#include <new>

// Type trait to determine allocation strategy
template <typename T>
struct UseHeap {
    static constexpr bool value = !std::is_trivial<T>::value || sizeof(T) > 32;
};

// Template-based memory allocator
template <typename T>
class CustomAllocator {
public:
    // Allocate memory for a single object
    T* allocate() {
        if constexpr (UseHeap<T>::value) {
            std::cout << "Allocating on heap for type: " << typeid(T).name() << "\n";
            return new T();
        } else {
            std::cout << "Allocating on stack for type: " << typeid(T).name() << "\n";
            return reinterpret_cast<T*>(&stackStorage);
        }
    }

    // Deallocate memory for a single object
    void deallocate(T* ptr) {
        if constexpr (UseHeap<T>::value) {
            delete ptr;
        } else {
            ptr->~T();
        }
    }

private:
    // Memory buffer for stack allocation
    typename std::aligned_storage<sizeof(T), alignof(T)>::type stackStorage;
};

// Example structure
struct LargeType {
    int data[20];  // 80 bytes on typical systems
};

// A smaller trivial structure
struct SmallType {
    int data;
};

int main() {
    CustomAllocator<LargeType> largeAllocator;
    LargeType* largeObject = largeAllocator.allocate();
    largeAllocator.deallocate(largeObject);

    CustomAllocator<SmallType> smallAllocator;
    SmallType* smallObject = smallAllocator.allocate();
    smallAllocator.deallocate(smallObject);

    return 0;
}
