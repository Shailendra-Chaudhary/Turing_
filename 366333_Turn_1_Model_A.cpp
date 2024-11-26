#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

class Task {
public:
    std::function<void()> task;
    std::chrono::time_point<std::chrono::system_clock> deadline;
};

class Timer {
private:
    std::mutex mu;
    std::condition_variable cv;
    std::vector<Task> tasks;
    bool running = true;
    std::thread timerThread;

public:
    Timer() : timerThread([this]() {
        while (running) {
            std::this_thread::sleep_until(tasks.front().deadline);
            
            // Lock to ensure exclusive access
            std::lock_guard<std::mutex> lock(mu);
            
            // Remove the first task
            Task currentTask = tasks.front();
            tasks.erase(tasks.begin());

            // Execute the task
            currentTask.task();

            // Notify the main thread that a task is complete
            cv.notify_one();
        }
    }) {}

    void addTask(const std::function<void()>& task, std::chrono::milliseconds delay) {
        std::lock_guard<std::mutex> lock(mu);
        Task newTask;
        newTask.task = task;
        newTask.deadline = std::chrono::system_clock::now() + delay;
        
        // Insert task into the vector while maintaining order
        auto it = std::lower_bound(tasks.begin(), tasks.end(), newTask,
            [](const Task& a, const Task& b) { return a.deadline < b.deadline; });
        tasks.insert(it, newTask);
    }

    ~Timer() {
        running = false;
        {
            std::lock_guard<std::mutex> lock(mu);
            cv.notify_one();
        }
        timerThread.join();
    }

    bool hasTasks() const {
        std::lock_guard<std::mutex> lock(mu);
        return !tasks.empty();
    }
};

int main() {
    Timer timer;

    // Add some tasks with specific delays
    timer.addTask([]{ std::cout << "Task 1 executed at " << std::chrono::system_clock::now() << std::endl; }, 2s);
    timer.addTask([]{ std::cout << "Task 2 executed at " << std::chrono::system_clock::now() << std::endl; }, 1s);
    timer.addTask([]{ std::cout << "Task 3 executed at " << std::chrono::system_clock::now() << std::endl; }, 3s);

    // Wait until all tasks are complete
    while (timer.hasTasks()) {
        std::this_thread::sleep_for(1s);
        std::cout << "Waiting for tasks to complete..." << std::endl;
    }

    return 0;
}
