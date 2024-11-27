
#include <cstdlib> // For malloc and free

namespace MyAllocator {

void* allocate(size_t size) {
    return malloc(size);
}

void deallocate(void* ptr) {
    free(ptr);
}

template <typename T>
T* allocate_t() {
    return reinterpret_cast<T*>(allocate(sizeof(T)));
}

template <typename T>
void deallocate_t(T* ptr) {
    deallocate(ptr);
}

} // namespace MyAllocator
