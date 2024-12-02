#include <iostream>
#include <type_traits>
#include <memory>

// A simple custom allocator as an example.
template <typename T>
class CustomAllocator {
public:
    using value_type = T;

    CustomAllocator() noexcept {}
    template <typename U> CustomAllocator(const CustomAllocator<U>&) noexcept {}

    T* allocate(std::size_t n) {
        std::cout << "Allocating " << n << " elements of type " << typeid(T).name() << "\n";

        // Check if the type is trivially destructible
        if constexpr (std::is_trivially_destructible_v<T>) {
            std::cout << "Using optimized allocation for trivially destructible types.\n";
        } else {
            std::cout << "Using standard allocation.\n";
        }

        // Allocate memory for n elements of type T
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) noexcept {
        std::cout << "Deallocating " << n << " elements of type " << typeid(T).name() << "\n";
        ::operator delete(p);
    }

    // Other allocator member functions...
};

// Specialization of the CustomAllocator for different types
template <typename T, typename U>
bool operator==(const CustomAllocator<T>&, const CustomAllocator<U>&) { return true; }

template <typename T, typename U>
bool operator!=(const CustomAllocator<T>&, const CustomAllocator<U>&) { return false; }

// Test structures
struct TrivialType {
    int a;
};

struct NonTrivialType {
    int* b;
    NonTrivialType() : b(new int(42)) {}
    ~NonTrivialType() { delete b; }
};

int main() {
    {
        std::cout << "Testing with TrivialType:\n";
        std::vector<TrivialType, CustomAllocator<TrivialType>> vec(10);
    }
    {
        std::cout << "\nTesting with NonTrivialType:\n";
        std::vector<NonTrivialType, CustomAllocator<NonTrivialType>> vec(10);
    }

    return 0;
}
