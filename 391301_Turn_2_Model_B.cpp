#include <iostream>
#include <vector>
#include <chrono>

using Matrix = std::vector<std::vector<int>>;

Matrix traditionalMatrixMultiplication(const Matrix& A, const Matrix& B) {
    size_t n = A.size();
    Matrix C(n, std::vector<int>(n, 0));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            for (size_t k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}
Matrix cacheOptimizedMatrixMultiplication(const Matrix& A, const Matrix& B, size_t blockSize) {
    size_t n = A.size();
    Matrix C(n, std::vector<int>(n, 0));

    for (size_t ii = 0; ii < n; ii += blockSize) {
        for (size_t jj = 0; jj < n; jj += blockSize) {
            for (size_t kk = 0; kk < n; kk += blockSize) {
                for (size_t i = ii; i < std::min(ii + blockSize, n); ++i) {
                    for (size_t j = jj; j < std::min(jj + blockSize, n); ++j) {
                        for (size_t k = kk; k < std::min(kk + blockSize, n); ++k) {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }

    return C;
}
int main() {
    const size_t n = 512; // Example size
    const size_t blockSize = 16; // Block size chosen to fit cache lines

    Matrix A(n, std::vector<int>(n, 1));
    Matrix B(n, std::vector<int>(n, 1));

    auto start = std::chrono::high_resolution_clock::now();
    Matrix C1 = traditionalMatrixMultiplication(A, B);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> traditionalDuration = end - start;
    std::cout << "Traditional Duration: " << traditionalDuration.count() << "s\n";

    start = std::chrono::high_resolution_clock::now();
    Matrix C2 = cacheOptimizedMatrixMultiplication(A, B, blockSize);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> optimizedDuration = end - start;
    std::cout << "Optimized Duration: " << optimizedDuration.count() << "s\n";

    return 0;
}
