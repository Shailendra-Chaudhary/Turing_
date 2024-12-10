#include <iostream>
#include <vector>
#include <chrono>
#include <xmmintrin.h> // Header for SSE (Streaming SIMD Extensions)

const int N = 256;  // Matrix dimension

// Function to multiply two matrices
void matrixMultiplyUsingSSE(const std::vector<std::vector<float>> &A,
                            const std::vector<std::vector<float>> &B,
                            std::vector<std::vector<float>> &C) {
    // Initialize the resulting matrix with zeros
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            C[i][j] = 0.0f;

    // Matrix multiplication, unrolling the innermost loop for optimization
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            __m128 res = _mm_setzero_ps(); // Set res to zero

            for (int k = 0; k < N; k += 4) { // Process 4 elements at once (SIMD)
                __m128 a_vals = _mm_load_ps(&A[i][k]);
                __m128 b_vals = _mm_load_ps(&B[k][j]);
                res = _mm_add_ps(res, _mm_mul_ps(a_vals, b_vals));
            }

            // Horizontal addition of the vector res to get the final sum
            float temp[4];
            _mm_store_ps(temp, res);
            C[i][j] = temp[0] + temp[1] + temp[2] + temp[3];
        }
    }
}

// Helper function to fill the matrix with values
void fillMatrix(std::vector<std::vector<float>> &matrix) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = static_cast<float>(i + j);
        }
    }
}

// Entry point of the program
int main() {
    std::vector<std::vector<float>> A(N, std::vector<float>(N));
    std::vector<std::vector<float>> B(N, std::vector<float>(N));
    std::vector<std::vector<float>> C(N, std::vector<float>(N));

    fillMatrix(A);
    fillMatrix(B);

    auto start = std::chrono::high_resolution_clock::now();
    matrixMultiplyUsingSSE(A, B, C);
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> diff = end - start;

    std::cout << "Time taken: " << diff.count() << " seconds\n";

    // Uncomment for debugging: Print part of the result
    /*
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }
    */

    return 0;
}
