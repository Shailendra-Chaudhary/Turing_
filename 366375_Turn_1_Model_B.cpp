

#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

using namespace std;

atomic<int> shared_counter = 0;
const int num_threads = 5;

void increment_counter() {
    for (int i = 0; i < 10000; ++i) {
        shared_counter++;
    }
}

int main() {
    vector<thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(increment_counter);
    }
    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
    cout << "Final value of shared_counter: " << shared_counter << endl;
    return 0;
}

