
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <vector>

using namespace std;

// Constants for task execution periods (in milliseconds)
constexpr int TASK1_PERIOD = 1000;  // Task 1: Execute every second
constexpr int TASK2_PERIOD = 500;   // Task 2: Execute every half second
constexpr int TASK3_PERIOD = 2000;  // Task 3: Execute every two seconds

// Counter for each task
std::atomic<int> task1_counter(0);
std::atomic<int> task2_counter(0);
std::atomic<int> task3_counter(0);

// Function prototypes for tasks
void task1();
void task2();
void task3();

// Static task scheduling: Task functions are called based on their fixed periods
void staticTaskScheduling()
{
    while (true)
    {
        task1();
        std::this_thread::sleep_for(std::chrono::milliseconds(TASK1_PERIOD));

        task2();
        std::this_thread::sleep_for(std::chrono::milliseconds(TASK2_PERIOD));

        task3();
        std::this_thread::sleep_for(std::chrono::milliseconds(TASK3_PERIOD));
    }
}

// Task data structure for dynamic task scheduling
struct Task {
    std::function<void()> taskFunction;
    std::chrono::milliseconds period;
    std::chrono::time_point<std::chrono::system_clock> nextDeadline;
};

// Dynamic task scheduling: Tasks are executed based on their deadlines
void dynamicTaskScheduling()
{
    // Vector to store task data
    std::vector<Task> tasks = {
        {task1, std::chrono::milliseconds(TASK1_PERIOD), std::chrono::system_clock::now()},
        {task2, std::chrono::milliseconds(TASK2_PERIOD), std::chrono::system_clock::now()},
        {task3, std::chrono::milliseconds(TASK3_PERIOD), std::chrono::system_clock::now()}
    };

    while (true)
    {
        // Check for tasks with deadlines passed
        for (auto& task : tasks)
        {
            if (std::chrono::system_clock::now() >= task.nextDeadline)
            {
                // Execute the task and update its next deadline
                task.taskFunction();
                task.nextDeadline += task.period;
            }
        }

        // Sleep for a small period to prevent busy waiting
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

// Task functions
void task1() {
    task1_counter++;
    std::cout << "Task1: " << task1_counter << std::endl;
}

void task2() {
    task2_counter++;
    std::cout << "Task2: " << task2_counter << std::endl;
}

void task3() {
    task3_counter++;
    std::cout << "Task3: " << task3_counter << std::endl;
}
 
 int main()
{
    // Start static task scheduling thread
    std::thread staticThread(staticTaskScheduling);
    staticThread.detach();

    // Start dynamic task scheduling thread
    std::thread dynamicThread(dynamicTaskScheduling);
    dynamicThread.detach();

    // Main thread keeps the application running
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    return 0;
