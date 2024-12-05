#include <iostream>
#include <omp.h>

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Partition the array
        int pi = partition(arr, low, high);

        // Parallelize the sorting of the left and right subarrays
        #pragma omp parallel
        {
            #pragma omp sections
            {
                #pragma omp section
                quickSort(arr, low, pi - 1);
                #pragma omp section
                quickSort(arr, pi + 1, high);
            }
        }
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

int main() {
    const int arraySize = 100000;
    int* arr = new int[arraySize];

    // Initialize the array
    for (int i = 0; i < arraySize; ++i) {
        arr[i] = rand() % 1000;
    }

    std::cout << "Original array: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Parallel QuickSort
    quickSort(arr, 0, arraySize - 1);

    std::cout << "Sorted array: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    delete[] arr;

    return 0;
}
