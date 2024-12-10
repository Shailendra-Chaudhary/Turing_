#include <iostream>
#include <vector>
#include <xmmintrin.h>

#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

const int N = 256;

void matrixTransposeInlineAssembly(const std::vector<std::vector<float>>& A, std::vector<std::vector<float>>& AT) {
    __assume(N % 16 == 0); // Ensure N is a multiple of 16 for better SIMD performance

    for (int i = 0; i < N; i += 16) {
        for (int j = 0; j < N; j += 16) {
            __m128 a[16];
            for (int k = 0; k < 16; k++) {
                // Load 16 elements from the matrix row
                a[k] = _mm_load_ps(&A[i + k][j]);
            }

            // Transpose 16 elements using aligned store
            for (int k = 0; k < 16; k++) {
                _mm_store_ps(&AT[j + k][i], a[k]);
            }
        }
    }
}
#include "matrix_transpose.h" // Include the header with the transpose function
#include "gtest/gtest.h"

class MatrixTransposeTest : public ::testing::Test {
protected:
    std::vector<std::vector<float>> A;
    std::vector<std::vector<float>> AT;
    std::vector<std::vector<float>> reference_AT;

    void SetUp() override {
        A.resize(N);
        AT.resize(N);
        reference_AT.resize(N);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                A[i][j] = static_cast<float>(i * N + j);
                reference_AT[j][i] = A[i][j];
            }
        }
    }
};

TEST_F(MatrixTransposeTest, MatrixTranspose) {
    matrixTransposeInlineAssembly(A, AT);

    // Compare the results with the reference implementation
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            EXPECT_NEAR(AT[i][j], reference_AT[i][j], 0.0001f);
        }
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
