#include <iostream>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;
using namespace std::chrono;

class PredictiveRealTimeTimer {
private:
    thread timer_thread;
    atomic<bool> is_running{false};
    condition_variable cv;
    mutex mtx;
    vector<pair<steady_clock::time_point, function<void()>>> tasks;

    void timer_loop() {
        while (is_running) {
            unique_lock<mutex> lock(mtx);
            cv.wait_until(lock, tasks.empty() ? steady_clock::time_point::max() : tasks.front().first);
 
            steady_clock::time_point now = steady_clock::now();
            // Execute all tasks due now
            while (!tasks.empty() && tasks.front().first <= now) {
                tasks.front().second();
                tasks.erase(tasks.begin());
                now = steady_clock::now();
            }
        }
    }

public:
    PredictiveRealTimeTimer() {
        timer_thread = thread([this] { timer_loop(); });
    }
 
    ~PredictiveRealTimeTimer() {
        if (is_running) {
            stop();
        }
    } 
 
    // Schedule a task to be executed at a specific time
    void schedule_task(steady_clock::time_point deadline, function<void()> task) {
        {
            unique_lock<mutex> lock(mtx);
            tasks.push_back({deadline, move(task)});
            push_heap(tasks.begin(), tasks.end(), [](const auto& a, const auto& b) { return a.first > b.first; }); 
        }
        cv.notify_one();
    } 
 
    void stop() {
        is_running = false;
        cv.notify_one(); 
        timer_thread.join();
    } 
 
    void predict_next_execution_time(const function<duration<double>>& predictor) {
        // Simulate some work to predict the next execution time
        auto predicted_time = steady_clock::now() + predictor();
        schedule_task(predicted_time, [] {} { });
    }
 
}; 
  
 int main() {
    PredictiveRealTimeTimer timer;
    
    auto task1 = [] { cout << "Task 1 executed at: " << duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count() << " ms\n"; }; 
    auto task2 = [] { cout << "Task 2 executed at: " << duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count() << " ms\n"; }; 
 
    timer.schedule_task(steady_clock::now() + 2s, task1);
    timer.schedule_task(steady_clock::now() + 4s, task2);
    
    // predict next execution based on some routine 
    auto predictor = []() -> duration<double> { 
        // Sample predictor routine - Replace this with your actual prediction logic
        this_thread::sleep_for(100ms);
        return 2s;
    };
    timer.predict_next_execution_time(predictor);

    // Simulate some other work
    this_thread::sleep_for(6s);
 
    return 0;
}
 
