#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <random>
#include <chrono>

const int MATRIX_SIZE = 1000;

void generateRandomMatrix(std::vector<std::vector<double>>& matrix) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < MATRIX_SIZE; ++i) {
        std::vector<double> row;
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            row.push_back(dis(gen));
        }
        matrix.push_back(row);
    }
}

// Function to multiply two matrices asynchronously
std::future<std::vector<std::vector<double>>> multiplyMatricesAsync(const std::vector<std::vector<double>>& mat1, const std::vector<std::vector<double>>& mat2) {
    return std::async(std::launch::async, [=] {
        std::vector<std::vector<double>> result(MATRIX_SIZE, std::vector<double>(MATRIX_SIZE, 0.0));

        // Perform matrix multiplication using nested loops
        for (int i = 0; i < MATRIX_SIZE; ++i) {
            for (int j = 0; j < MATRIX_SIZE; ++j) {
                for (int k = 0; k < MATRIX_SIZE; ++k) {
                    result[i][j] += mat1[i][k] * mat2[k][j];
                }
            }
        }
        return result;
    });
}

int main() {
    std::vector<std::vector<double>> matrix1, matrix2, result;

    // Generate random matrices
    generateRandomMatrix(matrix1);
    generateRandomMatrix(matrix2);

    // Start asynchronous matrix multiplication
    auto start = std::chrono::high_resolution_clock::now();
    std::future<std::vector<std::vector<double>>> futureResult = multiplyMatricesAsync(matrix1, matrix2);

    // Do other work in the main thread while the matrices are being multiplied
    std::cout << "Performing other computations in the main thread...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Wait for the matrix multiplication to complete and retrieve the result
    result = futureResult.get();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Output the result
    std::cout << "Matrix multiplication completed in " << duration << " milliseconds." << std::endl;

    // Validate the result (optional)
    // ...

    return 0;
}  
