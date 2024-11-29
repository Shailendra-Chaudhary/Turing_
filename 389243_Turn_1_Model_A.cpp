#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

// Functions representing tasks
void task1() {
    std::cout << "Task 1 running...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Task 1 finished.\n";
}

void task2() {
    std::cout << "Task 2 running...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    std::cout << "Task 2 finished.\n";
}

void task3() {
    std::cout << "Task 3 running...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Task 3 finished.\n";
}

// Main function
int main() {
    // Static Scheduling
    std::cout << "Static Scheduling:\n";
    std::vector<std::thread> tasks;
    
    // Run tasks in a fixed order
    tasks.emplace_back(task1);
    tasks[0].join();
    
    tasks.emplace_back(task2);
    tasks[1].join();
    
    tasks.emplace_back(task3);
    tasks[2].join();

    std::cout << "Static Scheduling completed.\n\n";
    
    // Dynamic Scheduling (using a priority queue and task priorities)
    std::cout << "Dynamic Scheduling:\n";
    std::priority_queue<std::pair<int, std::function<void()>>, std::vector<std::pair<int, std::function<void()>>>, std::greater<>> priorityQueue;
    
    // Add tasks with their respective priorities
    priorityQueue.push({2, task3}); // Task 3 is highest priority (value is inversely proportional)
    priorityQueue.push({1, task2}); // Task 2 is medium priority
    priorityQueue.push({0, task1}); // Task 1 is lowest priority
    
    while (!priorityQueue.empty()) {
        std::pair<int, std::function<void()>> nextTask = priorityQueue.top();
        priorityQueue.pop();
        
        std::cout << "Running task with priority " << nextTask.first << "\n";
        nextTask.second();
        std::cout << "Task completed.\n";
    }
    
    std::cout << "Dynamic Scheduling completed.\n";

    return 0;
}
