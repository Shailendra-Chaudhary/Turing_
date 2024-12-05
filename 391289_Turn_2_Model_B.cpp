#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

// Function to perform the partition operation used in QuickSort
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Parallel QuickSort implementation
void parallelQuickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        
        // Parallel sections using OpenMP
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelQuickSort(arr, low, pivot - 1);
            }
            #pragma omp section
            {
                parallelQuickSort(arr, pivot + 1, high);
            }
        }
    }
}

int main() {
    std::vector<int> arr = {45, 23, 76, 12, 67, 89, 33, 55, 29, 91};

    // Parallel QuickSort execution
    parallelQuickSort(arr, 0, arr.size() - 1);

    std::cout << "Sorted array using OpenMP: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
