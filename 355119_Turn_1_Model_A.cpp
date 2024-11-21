
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
using namespace std;

// Custom data type: Complex number
class Complex {
private:
    double real;
    double imag;

public:
    Complex(double real = 0, double imag = 0) : real(real), imag(imag) {}
    Complex(const Complex& other) : real(other.real), imag(other.imag) {}

    // getters
    double getReal() const { return real; }
    double getImag() const { return imag; }

    Complex& operator=(const Complex& other) {
        real = other.real;
        imag = other.imag;
        return *this;
    }

    // Overload operator== for equality comparison
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    // Overload operator!= for inequality comparison
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    friend ostream& operator<<(ostream& out, const Complex& c) {
        return out << c.real << (c.imag < 0 ? " - " : " + ") << abs(c.imag) << "i";
    }
};

// Hash function for Complex class
namespace std {
    template <>
    struct hash<Complex> {
        size_t operator()(const Complex& c) const {
            // Combine the hashes of the real and imaginary parts using some suitable function
            // We use simple XOR here, but more sophisticated approaches can be used.
            std::hash<double> h;
            return h(c.getReal()) ^ h(c.getImag());
        }
    };
}

// Equality comparator for Complex class (used for unordered_set)
namespace std {
    template <>
    struct equal_to<Complex> {
        bool operator()(const Complex& lhs, const Complex& rhs) const {
            return lhs == rhs;
        }
    };
}
 
int main() {
    {
        unordered_map<Complex, int> complexMap;
        complexMap[Complex(1, 2)] = 10;
        complexMap[Complex(3, -4)] = 20;
        complexMap[Complex(1, 2)] = 30;  // Update the value for the existing key

        cout << "unordered_map usage:" << endl;
        for (const auto& entry : complexMap) {
            cout << entry.first << ": " << entry.second << endl;
        }
    }

    {
        unordered_set<Complex> complexSet;
        complexSet.insert(Complex(1, 2));
        complexSet.insert(Complex(3, -4));
        complexSet.insert(Complex(1, 2));  // Duplicates are ignored

        cout << "\nunordered_set usage:" << endl;
        for (const auto& c : complexSet) {
            cout << c << endl;
        }
    }
    return 0;
}
