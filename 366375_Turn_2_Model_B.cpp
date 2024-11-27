
#include <iostream>
#include <thread>

using namespace std;

int main() {
    int x = 10;
    int y = 20;

    // Initial value of x and y
    cout << "x = " << x << ", y = " << y << endl;

    // Thread to modify y
    thread modify_y([&y]() {
        for (int i = 0; i < 5; ++i) {
            y += 10;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    // Loop to modify x and watch y's value
    for (int i = 0; i < 5; ++i) {
        x += 2;
        cout << "x = " << x << ", y = " << y << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    modify_y.join();

    cout << "Final value of x: " << x << endl;
    cout << "Final value of y: " << y << endl;

    return 0;
}
  
