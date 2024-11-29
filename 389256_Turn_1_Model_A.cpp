#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cerrno>

using namespace std;

void handleRequest(int clientSocket) {
    // Simulate processing the request asynchronously using std::future
    cout << "Processing request on socket " << clientSocket << endl;
    this_thread::sleep_for(chrono::seconds(2)); // Simulate work time
    cout << "Request processed on socket " << clientSocket << endl;
}

void bindAndListen(int port) {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        cerr << "Error creating socket: " << strerror(errno) << endl;
        return;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        cerr << "Error binding socket: " << strerror(errno) << endl;
        close(serverSocket);
        return;
    }

    if (listen(serverSocket, 5) == -1) {
        cerr << "Error listening on socket: " << strerror(errno) << endl;
        close(serverSocket);
        return;
    }

    cout << "Server is listening on port " << port << endl;

    while (true) {
        sockaddr_in clientAddress;
        socklen_t addressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (sockaddr*)&clientAddress, &addressLength);
        if (clientSocket == -1) {
            cerr << "Error accepting connection: " << strerror(errno) << endl;
            continue;
        }

        cout << "New connection from " << inet_ntoa(clientAddress.sin_addr) 
             << " on socket " << clientSocket << endl;

        // Instead of immediately spawning a new thread, we can run it asynchronously
        // The examples below simulate both straight threading and using futures

        // Method 1: Using Threads
        // std::thread handleRequestThread(handleRequest, clientSocket);
        // handleRequestThread.detach();

        // Method 2: Using Asynchronous Tasks with std::future
        auto future = std::async(std::launch::async, handleRequest, clientSocket);
        
        // You can control the future to observe results or wait if needed.
        future.get(); // Just to wait on this task for demonstration; in real scenarios, might not wait
    }

    close(serverSocket);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <port>" << endl;
        return 1;
    }

    try {
        int port = stoi(argv[1]);
        bindAndListen(port);
    } catch (const invalid_argument& e) {
        cerr << e.what() << endl;
        return 1;
    } catch (const out_of_range& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}
