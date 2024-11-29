#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <thread>
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

public:
    Session(tcp::socket socket, ThreadPool& thread_pool)
        : socket_(std::move(socket)), thread_pool_(thread_pool) {}

    void start() {
        do_read();
    }

private:
    void do_read() {
        async_read(
            socket_, buffer_, beast::http::async_read_some(req_),
            strand_.wrap([this](boost::system::error_code ec, std::size_t bytes_transferred) {
                if (ec) {
                    std::cerr << "Read error: " << ec.message() << std::endl;
                    return;
                }

                // Handle the request
                handle_request();

                // Continue reading
                do_read();
            }));
    }

    void handle_request() {
        // Do something with the request here (e.g., process it, fetch data from a database, etc.)
        // For this example, we will just send a simple response.

        res_ = beast::http::response<beast::http::string_body>{
            std::string("Hello, World!"), beast::http::status::ok, 11};
        res_.set(beast::http::field::server, BOOST_BEAST_VERSION_STRING);
        res_.prepare_payload();

        // Post the response writing to the thread pool
        thread_pool_.post([this] { do_write(); });
    }

    void do_write() {
        async_write(
            socket_, buffer_(res_), strand_.wrap([this](boost::system::error_code ec, std::size_t bytes_transferred) {
                if (ec) {
                    std::cerr << "Write error: " << ec.message() << std::endl;
                    return;
                }

                // The request has been handled, close the socket
                socket_.shutdown(tcp::socket::shutdown_send);
            }));
    }

    ip::tcp::strand<io_context::executor_type> strand_{socket_.get_executor()};
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
            if (ec) {
                std::cerr << "Accept error: " << ec.message() << std::endl;
                return;
            }

            // Start a new session for the client
            std::make_shared<Session>(std::move(socket), thread_pool_)->start();

            // Continue accepting new connections
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
