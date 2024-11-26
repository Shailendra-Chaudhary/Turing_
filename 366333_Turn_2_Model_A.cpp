#include <iostream>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <chrono>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;
using namespace std::chrono;

class PredictiveTimer {
private:
    thread timer_thread;
    atomic<bool> is_running{false};
    condition_variable cv;
    mutex mtx;
    vector<pair<system_clock::time_point, function<void()>>> tasks;
    unordered_map<string, duration<double>> task_durations;

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
                auto duration = end - start;
                task_durations[task_name] = average_duration(task_durations[task_name], duration);
                tasks.erase(tasks.begin());
            }
        }
    }

    duration<double> average_duration(duration<double> old, duration<double> new_) {
        if (old.count() == 0) {
            return new_;
        }
        return (old + new_) / 2.0;
    }

public:
    PredictiveTimer() {
        timer_thread = thread([this] { timer_loop(); });
    }

    ~PredictiveTimer() {
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
                                    : duration<double>(0);
            auto adjusted_deadline = deadline - estimated_duration;
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
    PredictiveTimer timer;

    auto task1 = [] { cout << "Task 1 executed at: " << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() << " ms\n"; };
    auto task2 = [] { cout << "Task 2 executed at: " << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() << " ms\n"; };

    timer.schedule_task("task1", system_clock::now() + 2s, task1);
    timer.schedule_task("task2", system_clock::now() + 4s, task2);

    // Simulate some other work
    this_thread::sleep_for(6s);

    return 0;
}
