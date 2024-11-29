
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

using namespace std;

// Counter for each task
std::atomic<int> task1_counter(0);
std::atomic<int> task2_counter(0);

// Static task scheduling (Task1 is executed every 1 second, Task2 is executed every 2 seconds)
void staticTaskScheduling()
{
    while (true)
    {
        // Task 1
        task1();
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Task 2
        task2();        
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

// Dynamic task scheduling (Task1 and Task2 are executed based on their deadlines)
void dynamicTaskScheduling()
{
    constexpr std::chrono::milliseconds task1_deadline(1000);
    constexpr std::chrono::milliseconds task2_deadline(2000);

    std::chrono::time_point<std::chrono::system_clock> prev_task1_time = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> prev_task2_time = std::chrono::system_clock::now();

    while (true)
    {
        std::chrono::time_point<std::chrono::system_clock> current_time = std::chrono::system_clock::now();

        // Task 1
        if (current_time - prev_task1_time >= task1_deadline)
        {
            task1();
            prev_task1_time = current_time;
        }

        // Task 2
        if (current_time - prev_task2_time >= task2_deadline)
        { 
            task2();
            prev_task2_time = current_time;
        }

        // Sleep for a small period to prevent busy waiting
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
  
void task1() {
    task1_counter++;
    std::cout << "Task1: " << task1_counter << std::endl;
}

void task2() {
    task2_counter++;
    std::cout << "Task2: " << task2_counter << std::endl;
}
 
 int main()
{
    // Static task scheduling
    std::thread staticThread(staticTaskScheduling);
    staticThread.detach();
    
    // Dynamic task scheduling
    std::thread dynamicThread(dynamicTaskScheduling);
    dynamicThread.detach();

    // Main thread keeps the application running
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    return 0;
}
                  
