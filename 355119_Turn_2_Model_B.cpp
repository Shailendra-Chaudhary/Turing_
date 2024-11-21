#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include <functional>

// Custom data type: Complex number
class Complex {
public:
    double real;
    double imag;

    Complex(double real, double imag) : real(real), imag(imag) {}

    // Equality operator for unordered_set
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }
};

// Hash function for Complex class
namespace std {
template <>
struct hash<Complex> {
    size_t operator()(const Complex& z) const {
        // Combination of the hashes of real and imaginary parts
        std::hash<double> h;
        return h(z.real) ^ (h(z.imag) << 1);
    }
};
}  // namespace std

// Model 1: Using unordered_set
int main() {
    {
        std::unordered_set<Complex> complex_set;

        complex_set.insert(Complex(1.0, 2.0));
        complex_set.insert(Complex(3.0, 4.0));
        complex_set.insert(Complex(1.0, 2.0));

        std::cout << "\nExample using unordered_set:\n";
        for (const Complex& num : complex_set) {
            std::cout << "(" << num.real << ", " << num.imag << ") ";
        }
        std::cout << std::endl;
    }

    // Model 2: Using unordered_map with Complex number as key
    {
        std::unordered_map<Complex, int> complex_map;

        complex_map[Complex(1.0, 2.0)] = 1;
        complex_map[Complex(3.0, 4.0)] = 2;
        complex_map[Complex(1.0, 2.0)] = 3;

        std::cout << "\nExample using unordered_map:\n";
        for (const auto& entry : complex_map) {
            const Complex& key = entry.first;
            int value = entry.second;
            std::cout << "(" << key.real << ", " << key.imag << ") -> " << value << std::endl;
        }
    }

    return 0;
}  
