#include <emmintrin.h> // Header for SSE2 intrinsics

void add_arrays(const float* a, const float* b, float* result, int size) {
    int i = 0;
    for (; i <= size - 4; i += 4) {
        // Load 4 floats from each array into SSE registers
        __m128 va = _mm_loadu_ps(&a[i]);
        __m128 vb = _mm_loadu_ps(&b[i]);
        
        // Perform addition
        __m128 vresult = _mm_add_ps(va, vb);
        
        // Store the result back
        _mm_storeu_ps(&result[i], vresult);
    }
    
    // Handle remaining elements
    for (; i < size; ++i) {
        result[i] = a[i] + b[i];
    }
}
template<int N>
struct Factorial {
    enum { value = N * Factorial<N - 1>::value };
};

template<>
struct Factorial<0> {
    enum { value = 1 };
};


void sum_array(const int* array, int size, int& result) {
    result = 0;
    int i = 0;
    for (; i <= size - 4; i += 4) {
        result += array[i] + array[i + 1] + array[i + 2] + array[i + 3];
    }
    
    // Handle remaining elements
    for (; i < size; ++i) {
        result += array[i];
    }
}
inline int add(int a, int b) {
    return a + b;
}

int main() {
    int sum = add(5, 3);
    return 0;
}
