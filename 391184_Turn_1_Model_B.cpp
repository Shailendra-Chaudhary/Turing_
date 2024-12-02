#include <iostream>
using namespace std;

// Function overloading constraint:
// The number of parameters in a function overload must be different.

// Two functions with the same name but different number of parameters
int add(int a, int b) {
    return a + b;
}

int add(int a, int b, int c) {
    return a + b + c;
}

// Template instantiation constraint:
// A template can only be instantiated with types that support the operations performed on them.

template <typename T>
T add_template(T a, T b) {
    return a + b;
}

int main() {
    // Function overloading example:
    cout << "add(10, 20): " << add(10, 20) << endl; // Output: 30
    cout << "add(10, 20, 30): " << add(10, 20, 30) << endl; // Output: 60
    
    // Template instantiation example:
    cout << "add_template<int>(10, 20): " << add_template<int>(10, 20) << endl; // Output: 30
    
    // Attempting to instantiate a template with an incompatible type (string) will result in a compile-time error
    // cout << "add_template<string>(\"Hello\", \" World\"): " << add_template<string>("Hello", " World") << endl; // Compile-time error!
    
    return 0;
}
