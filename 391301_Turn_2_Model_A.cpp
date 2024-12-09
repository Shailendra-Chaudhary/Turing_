#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

// Helper function to generate a random matrix
void generateRandomMatrix(std::vector<std::vector<double>>& matrix, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        matrix[i].resize(n);
        for (size_t j = 0; j < n; ++j) {
            matrix[i][j] = rand() / (double)RAND_MAX;
        }
    }
}

void transposeNaive(std::vector<std::vector<double>>& matrix) {
    size_t n = matrix.size();
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            double temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
}

int main() {
    const size_t n = 2048; // Change to a larger size to see the effect more clearly

    std::vector<std::vector<double>> matrix;
    generateRandomMatrix(matrix, n);

    // Measure naive transpose time
    auto start = std::chrono::high_resolution_clock::now();
    transposeNaive(matrix);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Naive Transpose Time: " << duration.count() << " ms" << std::endl;

    return 0;
}
