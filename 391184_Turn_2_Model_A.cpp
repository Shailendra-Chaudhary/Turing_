#include <iostream>
#include <type_traits>

// Function overloading example
void add(int a, int b) {
    std::cout << "Sum of two integers: " << a + b << std::endl;
}

void add(double a, double b) {
    std::cout << "Sum of two doubles: " << a + b << std::endl;
}

void add(const std::string& a, const std::string& b) {
    std::cout << "Concatenation of two strings: " << a << b << std::endl;
}

// Template instantiation example with type constraints
template <typename T, std::enable_if_t<std::is_arithmetic_v<T>>* = nullptr>
T multiply(T a, T b) {
    return a * b;
}

// Template with non-type constraint
template <int N, N > 0>
int power(int base, int exponent) {
    if (exponent == 0) return 1;
    return base * power(base, exponent - 1);
}

int main() {
    // Function overloading
    add(3, 5);        // Calls add(int, int)
    add(3.14, 1.59);  // Calls add(double, double)
    add("Hello", " "); // Calls add(const std::string&, const std::string&)

    // Template instantiation with type constraints
    std::cout << "Multiplication of 3 and 4: " << multiply(3, 4) << std::endl;
    std::cout << "Multiplication of 3.14 and 2.72: " << multiply(3.14, 2.72) << std::endl;

    // Template with non-type constraint
    std::cout << "2 to the power of 3: " << power(2, 3) << std::endl;

    // Challenges and restrictions
    // Uncommenting the following lines will lead to compile-time errors
    // add(3, 5.5);  // Invalid: cannot resolve overload; int and double
    // add("3", 4); // Invalid: cannot resolve overload; string and int

    // Invalid: Cannot multiply two non-arithmetic types (e.g., strings)
    // multiply("Hello", "World");

    // Invalid: Cannot compute power of a non-positive non-type template parameter
    // power(2, 0);

    return 0;
}
