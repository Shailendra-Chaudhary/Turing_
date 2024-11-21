
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Complex {
public:
    double real;
    double imag;

    Complex(double real = 0, double imag = 0) : real(real), imag(imag) {}

    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }
};

namespace std {
    template <>
    struct hash<Complex> {
        size_t operator()(const Complex& z) const {
            const int prime1 = 31;
            const int prime2 = 17;

            return std::hash<double>()(z.real) * prime1 ^ std::hash<double>()(z.imag) * prime2;
        }
    };
}

int main() {

    {
        // Model 1: Using Complex numbers as keys in unordered_map
        unordered_map<Complex, int> complexMap;

        complexMap[Complex(1.0, 2.0)] = 10;
        complexMap[Complex(3.0, -4.0)] = 20;
        complexMap[Complex(1.0, 2.0)] = 30;  // Update the value

        cout << "Complex number (1.0, 2.0) maps to: " << complexMap[Complex(1.0, 2.0)] << endl;
        cout << "Complex number (3.0, -4.0) maps to: " << complexMap[Complex(3.0, -4.0)] << endl;

        for (const auto& entry : complexMap) {
            cout << "Key: (" << entry.first.real << ", " << entry.first.imag << "), Value: " << entry.second << endl;
        }
    }

    {
        // Model 2: Using Complex numbers as elements in unordered_set
        unordered_set<Complex> complexSet;

        complexSet.insert(Complex(1.0, 0.0));
        complexSet.insert(Complex(0.0, 1.0));
        complexSet.insert(Complex(-1.0, 0.0));
        complexSet.insert(Complex(1.0, 0.0));  // Duplicates are ignored

        cout << "\nComplex numbers in the set:" << endl;
        for (const auto& num : complexSet) {
            cout << "(" << num.real << ", " << num.imag << ")" << endl;
        }
    }

    return 0;
}
