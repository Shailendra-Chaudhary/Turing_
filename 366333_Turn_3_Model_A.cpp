#include <iostream>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <chrono>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;
using namespace std::chrono;

class AdaptiveTimer {
private:
    thread timer_thread;
    atomic<bool> is_running{false};
    condition_variable cv;
    mutex mtx;
    vector<pair<system_clock::time_point, function<void()>>> tasks;
    unordered_map<string, double> task_durations;
    const double alpha = 0.1; // EWMA smoothing factor (default is 0.1)

    void timer_loop() {
        while (is_running) {
            unique_lock<mutex> lock(mtx);
            cv.wait_until(lock, tasks.empty() ? system_clock::time_point::max() : tasks.front().first);

            // Execute all tasks due now
            while (!tasks.empty() && tasks.front().first <= system_clock::now()) {
                string task_name = tasks.front().second.target_name();
                auto start = system_clock::now();
                tasks.front().second();
                auto end = system_clock::now();
                auto duration = duration_cast<milliseconds>(end - start).count();

                // Update task duration estimate using EWMA
                double new_duration = alpha * duration + (1.0 - alpha) * task_durations[task_name];
                task_durations[task_name] = new_duration;

                tasks.erase(tasks.begin());
            }
        }
    }

public:
    AdaptiveTimer() : alpha(0.1) {
        timer_thread = thread([this] { timer_loop(); });
    }

    ~AdaptiveTimer() {
        if (is_running) {
            stop();
        }
    }

    // Schedule a task to be executed at a specific time
    void schedule_task(const string& task_name, system_clock::time_point deadline, function<void()> task) {
        {
            unique_lock<mutex> lock(mtx);
            auto estimated_duration = task_durations.find(task_name) != task_durations.end()
                                    ? task_durations[task_name]
                                    : 0;
            auto adjusted_deadline = deadline - milliseconds(estimated_duration);
            tasks.push_back({adjusted_deadline, move(task)});
            push_heap(tasks.begin(), tasks.end(), [](const auto& a, const auto& b) { return a.first > b.first; });
        }
        cv.notify_one();
    }

    void stop() {
        is_running = false;
        cv.notify_one();
        timer_thread.join();
    }
};

int main() {
    AdaptiveTimer timer;

    auto task1 = [] { cout << "Task 1 executed at: " << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() << " ms\n"; };
    auto task2 = [] { cout << "Task 2 executed at: " << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() << " ms\n"; };

    timer.schedule_task("task1", system_clock::now() + 2s, task1);
    timer.schedule_task("task2", system_clock::now() + 4s, task2);

    // Simulate some additional load on the system
    while (true) {
        this_thread::sleep_for(100ms);
    }

    return 0;
}
