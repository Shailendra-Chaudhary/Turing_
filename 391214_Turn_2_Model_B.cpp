#include <iostream>
using namespace std;

int add(int a, int b) {
    int result;
    // Inline Assembly in GCC
    asm("addl %%ebx, %%eax;"
        : "=a"(result) // output list
        : "a"(a), "b"(b) // input list
    );
    return result;
}

int main() {
    cout << add(5, 10) << endl;  // Should print 15
    return 0;
}
