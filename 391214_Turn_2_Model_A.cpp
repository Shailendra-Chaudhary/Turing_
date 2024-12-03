#include <immintrin.h> // AVX2

void add_vectors_avx(float* a, float* b, float* c, int size) {
    for (int i = 0; i < size; i += 8) {
        __m256 va = _mm256_load_ps(a + i);
        __m256 vb = _mm256_load_ps(b + i);
        __m256 vc = _mm256_add_ps(va, vb);
        _mm256_store_ps(c + i, vc);
    }
}
