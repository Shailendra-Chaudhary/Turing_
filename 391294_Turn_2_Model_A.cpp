#include <iostream>
#include <thread>
#include <vector>

std::vector<int> numbers(1000000);

void increment(int& num) {
    for (int i = 0; i < 1000000; ++i) {
        ++num;
    }
}

int main() {
    std::thread t1(increment, std::ref(numbers[0]));
    std::thread t2(increment, std::ref(numbers[0]));

    t1.join();
    t2.join();

    if (numbers[0] != 2000000) {
        std::cerr << "Data race detected: numbers[0] = " << numbers[0] << std::endl;
    }
    return 0;
}
