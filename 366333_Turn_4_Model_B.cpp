#include <iostream>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <chrono>
#include <vector>
#include <map>
#include <unordered_map>
#include <mutex>
#include <limits>
#include <functional>

using namespace std;
using namespace std::chrono;

// Executor Task Interface
class ExecutorTask {
public:
    virtual void execute() = 0;
    virtual string getName() const = 0;
};

// Function Executable Task
template <class F>
class FunctionTask : public ExecutorTask {
public:
    FunctionTask(F f, const string& name) : f(move(f)), name(name) {}
    void execute() override { f(); }
    string getName() const override { return name; }

private:
    F f;
    string name;
};

// Time Scheduler Base Class
class TimeScheduler {
public:
    virtual ~TimeScheduler() = default;
    virtual void schedule_task(unique_ptr<ExecutorTask> task, system_clock::time_point deadline) = 0;
    virtual system_clock::time_point get_next_task_time() const = 0;
    virtual void run_pending_tasks() = 0;
};

// Predictive Timer class using EWMA
class PredictiveTimer : public TimeScheduler {
public:
    PredictiveTimer(double alpha = 0.1) : alpha(alpha) {}

    void schedule_task(unique_ptr<ExecutorTask> task, system_clock::time_point deadline) override {
        {
            lock_guard<mutex> lock(mtx);
            auto task_name = task->getName();
            auto estimated_duration = task_durations.find(task_name) != task_durations.end()
                                        ? task_durations[task_name]
                                        : 0ms;
            auto adjusted_deadline = deadline - estimated_duration;
            tasks.emplace_back(make_pair(adjusted_deadline, move(task)));
            push_heap(tasks.begin(), tasks.end(), compare_pair);
        }
        cv.notify_one();
    }

    system_clock::time_point get_next_task_time() const override {
        unique_lock<mutex> lock(mtx);
        if (tasks.empty()) {
            return system_clock::time_point::max();
        }
        return tasks.front().first;
    }

    void run_pending_tasks() override {
        system_clock::time_point current_time;
        do {
            current_time = system_clock::now();
            run_ready_tasks();
        } while (current_time < get_next_task_time() && cv.wait_until(cv, get_next_task_time()) != cv_status::timeout);
    }

private:
    static bool compare_pair(const pair<system_clock::time_point, unique_ptr<ExecutorTask>>& lhs,
                             const pair<system_clock::time_point, unique_ptr<ExecutorTask>>& rhs) {
        return lhs.first > rhs.first;
    }

    void run_ready_tasks() {
        unique_lock<mutex> lock(mtx);
        while (!tasks.empty() && tasks.front().first <= system_clock::now()) {
            auto task_name = tasks.front().second->getName();
            auto start = system_clock::now();
            tasks.front().second->execute();
            auto end = system_clock::now();
            auto duration = duration_cast<milliseconds>(end - start);

            // Update task duration estimate using EWMA
            double new_duration = alpha * duration.count() + (1.0 - alpha) * task_durations[task_name];
            task_durations[task_name] = milliseconds(new_duration);

            pop_heap(tasks.begin(), tasks.end(), compare_pair);
            tasks.pop_back();
