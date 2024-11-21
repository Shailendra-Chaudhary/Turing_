#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unordered_set>
#include <functional>
#include <executor>
#include <future>

class Observer {
public:
    virtual ~Observer() = default;

    virtual void update(int newValue) = 0;
};

class ResourceSubject {
private:
    int value = 0;
    std::unordered_set<Observer*> observers;
    std::mutex mtx;
    std::condition_variable cv;
    std::executor workQueue;

public:
    ResourceSubject() : workQueue(std::thread::pool(4)) {}  // Create a thread pool with 4 threads

    void attach(Observer* observer) {
        std::unique_lock<std::mutex> lock(mtx);
        observers.insert(observer);
    }

    void detach(Observer* observer) {
        std::unique_lock<std::mutex> lock(mtx);
        observers.erase(observer);
    }

    void notify() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.notify_all();
    }

    int getValue() const {
        std::unique_lock<std::mutex> lock(mtx);
        return value;
    }

    void setValue(int newValue) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            value = newValue;
        }
        notify();
    }

    void asyncUpdateObservers() {
        std::unique_lock<std::mutex> lock(mtx);
        for (auto observer : observers) {
            std::packaged_task<void()> task([observer, this] {
                auto future = asyncGetValue();
                int updatedValue = future.get();
                observer->update(updatedValue);
            });
            std::future<void> futureTask = task.get_future();
            std::post(workQueue, std::move(task));
        }
    }

    std::future<int> asyncGetValue() {
        return std::async([this] {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return true; });
            return value;
        });
    }
};

class SpecificObserver : public Observer {
private:
    const char* name;

public:
    SpecificObserver(const char* name_) : name(name_) {}

    void update(int newValue) override {
        std::cout << name << ": Resource updated to " << newValue << std::endl;
    }
};

int main() {
    ResourceSubject resourceSubject;

    // Create and attach two observers
    SpecificObserver observer1("Observer 1");
    SpecificObserver observer2("Observer 2");

    resourceSubject.attach(&observer1);
    resourceSubject.attach(&observer2);

    // Update the resource value asynchronously
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        resourceSubject.setValue(i * 10);
        resourceSubject.asyncUpdateObservers();
    }
    return 0;
}
