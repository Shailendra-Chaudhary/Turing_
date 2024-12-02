#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
using namespace std;

const int NUM_THREADS = 4;
const int MAX_NUM = 10000;
const int THREAD_RANGE = MAX_NUM / NUM_THREADS + 1; // Ensure each thread covers an entire range

// Function to mark non-prime numbers in a given range
void markNonPrimes(int start, int end, int* isPrime) {
    for (int i = start; i <= end; ++i) {
        if (isPrime[i] && i * i <= end) {
            // Use atomic compare-exchange to ensure thread safety
            atomic<int> temp[i + 1];
            for (int j = i * i; j <= end; j += i) {
                if (isPrime[j]) {
                    temp[j].compare_exchange_strong(isPrime[j], false, memory_order_seq_cst);
                }
            }
        }
    }
}

// Function to find and print prime numbers
void findPrimes() {
    vector<thread> threads;
    vector<int*> ranges(NUM_THREADS);
    
    for (int i = 0; i < NUM_THREADS; ++i) {
        int start = i * THREAD_RANGE;
        int end = min((i + 1) * THREAD_RANGE - 1, MAX_NUM);
        ranges[i] = new int[end + 1];
        
        // Initialize all numbers as prime
        for (int j = start; j <= end; ++j) {
            ranges[i][j] = true;
        }
        
        threads.push_back(thread(markNonPrimes, start, end, ranges[i]));
    }
    
    for (auto& thread : threads) {
        thread.join();
    }

    // Collect and print prime numbers
    for (int i = 0; i < NUM_THREADS; ++i) {
        int start = i * THREAD_RANGE;
        int end = min((i + 1) * THREAD_RANGE - 1, MAX_NUM);
        for (int j = start; j <= end; ++j) {
            if (ranges[i][j]) {
                cout << j << " ";
            }
        }
        delete[] ranges[i];
    }
    cout << endl;
}

int main() {
    findPrimes();
    return 0;
}
