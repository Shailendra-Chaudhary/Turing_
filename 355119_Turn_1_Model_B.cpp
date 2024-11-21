
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <utility>
using namespace std;

//Custom data type: Complex number
class Complex {
private:
    double real;
    double imag;

public:
    Complex(double real = 0, double imag = 0) : real(real), imag(imag) {}
    Complex(const Complex& other) : real(other.real), imag(other.imag) {}
    Complex& operator=(const Complex& other) {
        real = other.real;
        imag = other.imag;
        return *this;
    }
    
    bool operator==(const Complex& other) const {
        return (real == other.real && imag == other.imag);
    }

    double getReal() const {
        return real;
    }

    double getImag() const {
        return imag;
    }
    void display() const {
        (imag < 0) ? cout << real << " - " << abs(imag) << "i" :
                     cout << real << " + " << imag << "i";
    }
};

// Hash function for unordered_set and unordered_map
namespace std {
    template <>
    struct hash<Complex> {
        size_t operator()(const Complex& c) const {
            size_t x = static_cast<size_t>(c.getReal() * 12.34567);
            size_t y = static_cast<size_t>(c.getImag() * 87.65432);
            return x ^ y;
        }
    };
}
 
int main() {
    {
        unordered_set<Complex> complex_set;

        complex_set.insert(Complex(1.0, 2.0));
        complex_set.insert(Complex(3.0, 4.0));
        complex_set.insert(Complex(1.0, 2.0)); 

        cout << "Complex Set:\n";
        for (const auto& z : complex_set) {
            z.display();
            cout << endl;
        }
        cout << "Size of complex_set: " << complex_set.size() << endl;
    }

    {
        unordered_map<Complex, int> complex_map;

        complex_map[Complex(2.5, -1.0)] = 10;
        complex_map[Complex(4.0, 0.0)] = 20;
        complex_map[Complex(2.5, -1.0)] = 30; 

        cout << "\nComplex Map:\n";
        for (const auto& entry : complex_map) {
            entry.first.display();
            cout << " -> " << entry.second << endl;
        }
        cout << "Size of complex_map: " << complex_map.size() << endl;
    }

    return 0;
}
