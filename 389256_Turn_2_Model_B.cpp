#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast.hpp>
#include <boost/thread.hpp>
#include <thread>
#include <functional>
#include <future>
#include <atomic>
#include <queue>
#include <mutex>

using namespace boost::asio;
using namespace boost::beast;
using namespace boost::beast::http;
using ip::tcp;

// Simple thread pool class
class ThreadPool {
private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable cv;
    std::atomic<bool> stop{false};

public:
    ThreadPool(size_t num_threads) {
        for (size_t i = 0; i < num_threads; ++i) {
            threads.emplace_back([this] {
                while (!stop) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queue_mutex);
                        cv.wait(lock, [this] { return !tasks.empty() || stop; });
                        if (stop) {
                            break;
                        }
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    ~ThreadPool() {
        stop = true;
        cv.notify_all();
        for (auto& thread : threads) {
            thread.join();
        }
    }

    template <class F>
    void post(F&& f) {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            tasks.emplace(std::forward<F>(f));
        }
        cv.notify_one();
    }
};

// Session class to handle each client request
class Session : public std::enable_shared_from_this<Session> {
private:
    tcp::socket socket_;
    flat_buffer buffer_;
    request<string_body> req_;
    response<string_body> res_;
    ThreadPool& thread_pool_;
    io_context::strand<tcp::socket::executor_type> strand_;

public:
    Session(tcp::socket socket, ThreadPool& thread_pool)
        : socket_(std::move(socket)), thread_pool_(thread_pool), strand_(socket_.get_executor()) {}

    void start() {
        do_read();
    }

private:
    void do_read() {
        async_read(
            socket_, buffer_, beast::http::async_read_some(req_), strand_.wrap([this](boost::system::error_code ec, std::size_t bytes_transferred) {
                if (ec) {
                    std::cerr << "Read error: " << ec.message() << std::endl;
                    return;
                }

                // Handle the request
                handle_request();
            }));
    }

    void handle_request() {
        // Do something with the request here
        // This example will just send a response after a 2-second delay

        // Start an asynchronous task to perform time-consuming work
        auto async_task = std::async(std::launch::async, &Session::do_cpu_bound_work, shared_from_this());

        // In the meantime, keep reading requests from the client on the I/O thread
        do_read();

        // After the task is complete, write the response
        async_task.wait();
        do_write();
    }
