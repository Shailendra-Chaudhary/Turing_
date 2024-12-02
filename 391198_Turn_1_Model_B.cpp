 
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

atomic<int> nextPrime{2}; // Global atomic variable to store the next prime number

const int NUM_THREADS = 8;
const int MAX_NUM = 1000;

// Function to check if a number is prime using trial division
bool isPrime(int num) {
   for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

// Function to calculate prime numbers using atomic operations
void calculatePrimes() {
    while (true) {
        // Read the next prime number using fetch_add (thread-safe)
        int currentPrime = nextPrime.fetch_add(1, memory_order_release);

        // Check if the number is greater than the maximum number to be calculated
        if (currentPrime > MAX_NUM) {
            break;
        }

        // Check if the number is prime
        if (isPrime(currentPrime)) {
                 // Print the prime number using atomic_thread_fence to ensure sequencing
            atomic_thread_fence(memory_order_acquire);
            cout << currentPrime << " ";
        }
    }
}
 
int32_t main() {
    vector<thread> threads;
    // Create worker threads
    for (int i = 0; i < NUM_THREADS; i++) {
        threads.push_back(thread(calculatePrimes));
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }
    cout << endl;
    return 0;
}
  
