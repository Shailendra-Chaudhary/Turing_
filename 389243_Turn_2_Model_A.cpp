#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

// Task counters
int task1Counter = 0;
int task2Counter = 0;

// Static task scheduling
void staticTaskScheduler() {
    while (true) {
        task1();
        this_thread::sleep_for(chrono::milliseconds(500));  // Task 1 runs every 500 ms
        
        task2();
        this_thread::sleep_for(chrono::milliseconds(1000)); // Task 2 runs every 1000 ms
    }
}

void task1() {
    task1Counter++;
    cout << "Task1: " << task1Counter << endl;
}

void task2() {
    task2Counter++;
    cout << "Task2: " << task2Counter << endl;
}

int main() {
    // Launch the static scheduler
    thread staticThread(staticTaskScheduler);
    staticThread.detach();
    
    // Main thread runs indefinitely (in a real embedded system, this might be replaced by another task or processing loop)
    while (true) {
        this_thread::sleep_for(chrono::seconds(10));  // Keep running for 10 seconds
    }

    return 0;
}
