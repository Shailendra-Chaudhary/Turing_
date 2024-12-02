#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <cmath>

// Function to check if a number is prime using a shared is_prime variable
bool isPrime(int number, std::atomic<bool>* is_prime) {
    if (number <= 1) {
        return false;
    }
    if (number <= 3) {
        return true;
    }
    if (number % 2 == 0 || number % 3 == 0) {
        return false;
    }

    // Use 6k +/- 1 optimization to reduce the number of checks
    for (int i = 5; i * i <= number; i += 6) {
        if (number % i == 0 || number % (i + 2) == 0) {
            *is_prime = false;
            return false;
        }
    }

    *is_prime = true;
    return true;
}

// Function to compute prime numbers in a range using multiple threads
void computePrimes(int start, int end, std::vector<int>& primes) {
    for (int i = start; i <= end; ++i) {
        std::atomic<bool> is_prime(true);
        if (isPrime(i, &is_prime)) {
            primes.push_back(i);
        }
    }
}

int main() {
    int start = 1;
    int end = 1000;
    int numThreads = std::thread::hardware_concurrency();
    std::vector<int> primes;
    std::vector<std::thread> threads;

    int chunkSize = (end - start + 1) / numThreads + 1;

    // Create and start threads
    for (int threadId = 0; threadId < numThreads; ++threadId) {
        int threadStart = start + threadId * chunkSize;
        int threadEnd = std::min(threadStart + chunkSize - 1, end);
        threads.emplace_back(computePrimes, threadStart, threadEnd, std::ref(primes));
    }

    // Wait for all threads to complete
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    std::cout << "Prime numbers from " << start << " to " << end << ":\n";
    for (int prime : primes) {
        std::cout << prime << " ";
    }
    std::cout << std::endl;

    return 0;
}
