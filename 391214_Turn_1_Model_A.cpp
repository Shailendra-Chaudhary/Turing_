#include <iostream>
#include <immintrin.h>  // For AVX intrinsics

void add_vectors_avx(float *a, float *b, float *c, int size) {
    for (int i = 0; i < size; i += 8) {
        __m256 va = _mm256_load_ps(a + i);
        __m256 vb = _mm256_load_ps(b + i);
        __m256 vc = _mm256_add_ps(va, vb);
        _mm256_store_ps(c + i, vc);
    }
}

int main() {
    float a[8] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
    float b[8] = {9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
    float c[8] = {0.0f};

    add_vectors_avx(a, b, c, 8);

    for (int value : c) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    return 0;
}
