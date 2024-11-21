#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

const int NUM_ELEMENTS = 1000000;

// Function to initialize the vector with random integers
void initVector(std::vector<int>& vec)
{
    for (int i = 0; i < NUM_ELEMENTS; ++i)
    {
        vec.push_back(i * 101);
    }
}

// Function to sort the vector using sort algorithm from <algorithm> library
void sortVector_std(std::vector<int>& vec)
{
    std::sort(vec.begin(), vec.end());
}

// Function to sort the vector using parallel sort algorithm from <execution> library (available in C++17)
void sortVector_parallel(std::vector<int>& vec)
{
    #ifdef __cpp_lib_execution
        std::sort(std::execution::par, vec.begin(), vec.end());
    #else
        (void)vec;
        std::cout << "Parallel sort is not available in this C++ version." << std::endl;
    #endif
}

int main()
{
    {
        // Optimization 1: Use preallocation to avoid reallocations during insertion
        std::vector<int> vec;
        vec.reserve(NUM_ELEMENTS);
        initVector(vec);

        auto start = std::chrono::high_resolution_clock::now();
        sortVector_std(vec);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Sorted using std::sort: " << duration.count() << " microseconds" << std::endl;
    }

    {
        // Optimization 2: Use const references for input containers
        std::vector<int> vec;
        initVector(vec);
        
        auto start = std::chrono::high_resolution_clock::now();
        sortVector_std(const_cast<std::vector<int>&>(vec));
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Sorted using std::sort (const ref): " << duration.count() << " microseconds" << std::endl;
    }

    {
        // Optimization 3: Enable compiler optimizations 
        #pragma omp parallel
        {
            std::vector<int> vec;
            initVector(vec);
        
            auto start = std::chrono::high_resolution_clock::now();
            sortVector_parallel(vec);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

            std::cout << "Sorted using parallel_sort: " << duration.count() << " microseconds" << std::endl;
        }
    }

    return 0;
}
