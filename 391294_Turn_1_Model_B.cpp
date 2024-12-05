#include <iostream>
#include <thread>

int shared_variable = 0;

void increment() {
    for (int i = 0; i < 1000; ++i) {
        ++shared_variable;  // Potential data race
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Shared variable: " << shared_variable << std::endl;
    return 0;
}

// Compile with: g++ -fsanitize=thread -g your_program.cpp -o your_program
