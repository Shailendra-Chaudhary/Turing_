#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

using namespace std;

// Constants
const int NUM_THREADS = 8;
const int MAX_NUM = 100000;
const int QUEUE_SIZE = 1000;

// Atomic counter to keep track of the number of processed primes
atomic<int> processedPrimes = 0;

// condition_variable to synchronize threads
condition_variable cv;
mutex mtx;

// Shared queue to store prime numbers to be processed
queue<int> primeQueue;

// Function to check if a number is prime using trial division
bool isPrime(int num) {
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

// Producer function to find and enqueue prime numbers
void findPrimes() {
    for (int num = 2; num <= MAX_NUM; num++) {
        if (isPrime(num)) {
            unique_lock<mutex> lock(mtx);
            // Wait until the queue is not full
            while (primeQueue.size() == QUEUE_SIZE) {
                cv.wait(lock);
            }
            primeQueue.push(num);
            cv.notify_one();
        }
    }
}

// Consumer function to dequeue primes and print them
void printPrimes() {
    while (true) {
        unique_lock<mutex> lock(mtx);
        // Wait until there are primes in the queue
        while (primeQueue.empty()) {
            if (processedPrimes >= MAX_NUM) {
                return;
            }
            cv.wait(lock);
        }

        int prime = primeQueue.front();
        primeQueue.pop();
        lock.unlock();

        processedPrimes++;
        cout << prime << " ";
        cv.notify_one();
    }
}
 
int32_t main() {
    vector<thread> threads;

    // Create producer threads to find and enqueue prime numbers
    threads.push_back(thread(findPrimes));

    // Create consumer threads to print dequeued primes
    for (int i = 0; i < NUM_THREADS - 1; i++) {
        threads.push_back(thread(printPrimes));
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    cout << endl;
    return 0;
}
                     
