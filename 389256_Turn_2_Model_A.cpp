#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>
#include <chrono>
#include <vector>

using namespace boost::asio;
using ip::tcp;

// Simple thread pool class
class ThreadPool {
private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable cv;
    bool stop = false;

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

    template <typename F>
    void post(F&& f) {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            tasks.emplace(std::forward<F>(f));
        }
        cv.notify_one();
    }
};

// Connection handler class
class ConnectionHandler {
private:
    tcp::socket socket_;
    ThreadPool& thread_pool_;

public:
    ConnectionHandler(tcp::socket socket, ThreadPool& thread_pool)
        : socket_(std::move(socket)), thread_pool_(thread_pool) {}

    void handle_connection() {
        char data[1024];
        do {
            std::size_t len = socket_.read_some(buffer(data, sizeof(data)));
            if (len == 0) {
                break;
            }

            // Process data
            process_data(data, len);

        } while (!socket_.is_closed());
    }

private:
    void process_data(char const* data, std::size_t len) {
        // Simple echo for this example
        std::string response = std::string(data, len);
        std::cout << "Received: " << response << std::endl;

        // Simulate a time-consuming task with a thread
        thread_pool_.post([this, response] { simulate_time_consuming_task(response); });

        // Send back the data
        async_write(socket_, buffer(response), [this](boost::system::error_code ec, std::size_t len) {
            if (ec) {
                std::cerr << "Write error: " << ec.message() << std::endl;
            }
        });
    }

    void simulate_time_consuming_task(const std::string& data) {
        // Simulate work by sleeping for a few milliseconds
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        std::cout << "Processed: " << data << std::endl;
    }
};

// Web server class
class WebServer {
private:
    io_context ioc_;
    tcp::acceptor acceptor_;
    ThreadPool thread_pool_;

public:
    WebServer(short port, size_t num_threads)
        : acceptor_(ioc_, tcp::endpoint(tcp::v4(), port)), thread_pool_(num_threads) {
        do_accept();
    }

    void run() {
        ioc_.run();
    }

private:
    void do_accept() {
        acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::make_shared<ConnectionHandler>(std::move(socket), thread_pool_)->handle_connection();
            }
            do_accept();
        });
    }
};

int main() {
    try {
        // Start the web server on port 8080 with 4 worker threads
        WebServer server(8080, 4);
        server.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
