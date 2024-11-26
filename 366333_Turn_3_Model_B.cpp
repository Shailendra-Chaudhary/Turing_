#include <iostream>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <chrono>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <deque>
#include <mutex>

using namespace std;
using namespace std::chrono;

class PredictiveTimer {
private:
    struct Task {
        string name;
        system_clock::time_point deadline;
        function<void()> task;
    };

    thread timer_thread;
    atomic<bool> is_running{false};
    condition_variable cv;
    mutex mtx;
    vector<Task> tasks;
    unordered_map<string, duration<double>> task_durations;
    deque<duration<double>> system_loads;
    const int max_system_loads = 10;
    double system_load_factor = 1.0;

    void timer_loop() {
        while (is_running) {
            this_thread::sleep_for(1ms);
            {
                unique_lock<mutex> lock(mtx);
                if (tasks.empty()) {
                    continue;
                }

                if (system_loads.size() >= max_system_loads) {
                    system_loads.pop_front();
                }
                system_loads.push_back(system_clock::now() - tasks.front().deadline);
                double avg_system_load = accumulate(system_loads.begin(), system_loads.end(), duration<double>(0)) / system_loads.size();
                system_load_factor = max(1.0, avg_system_load.count() / duration<double>(1s).count());
            }

            {
                unique_lock<mutex> lock(mtx);
                if (tasks.front().deadline <= system_clock::now()) {
                    string task_name = tasks.front().name;
                    auto start = system_clock::now();
                    tasks.front().task();
                    auto end = system_clock::now();
                    auto duration = end - start;
                    task_durations[task_name] = average_duration(task_durations[task_name], duration);
                    tasks.erase(tasks.begin());
                    cv.notify_one();
                }
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
    // Schedule a task to be executed at a specific time with the given deadline adjustment factor
    void schedule_task(const string& task_name, system_clock::time_point deadline, function<void()> task, double adjustment_factor = 1.0) {
        {
            unique_lock<mutex> lock(mtx);
            auto estimated_duration = task_durations.find(task_name) != task_durations.end()
                                    ? task_durations[task_name] * system_load_factor * adjustment_factor
                                    : duration<double>(0);
            auto adjusted_deadline = deadline - estimated_duration;
            tasks.push_back({task_name, adjusted_deadline, move(task)});
            push_heap(tasks.begin(), tasks.end(), [](const auto& a, const auto& b) { return a.deadline > b.deadline; });
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
