#include <iostream>
#include <numeric>

class Rational {
private:
    int num, den;
    
public:
    // Constructor
    Rational(int n = 0, int d = 1) : num(n), den(std::abs(d)) {
        if (den == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }
        simplify();
    }

    // Method to simplify the fraction
    void simplify() {
        int gcd = std::gcd(num, den);
        num /= gcd;
        den /= gcd;
        if (den < 0) {
            num = -num;
            den = -den;
        }
    }

    // Operator overloads
    Rational operator+(const Rational& rhs) const {
        return Rational(num * rhs.den + den * rhs.num, den * rhs.den);
    }

    Rational operator-(const Rational& rhs) const {
        return Rational(num * rhs.den - den * rhs.num, den * rhs.den);
    }

    Rational operator*(const Rational& rhs) const {
        return Rational(num * rhs.num, den * rhs.den);
    }

    Rational operator/(const Rational& rhs) const {
        if (rhs.num == 0) {
            throw std::invalid_argument("Cannot divide by zero");
        }
        return Rational(num * rhs.den, den * rhs.num);
    }

    bool operator==(const Rational& rhs) const {
        return num * rhs.den == den * rhs.num;
    }

    bool operator!=(const Rational& rhs) const {
        return num * rhs.den != den * rhs.num;
    }

    bool operator<(const Rational& rhs) const {
        return num * rhs.den < den * rhs.num;
    }

    bool operator>(const Rational& rhs) const {
        return num * rhs.den > den * rhs.num;
    }

    bool operator<=(const Rational& rhs) const {
        return num * rhs.den <= den * rhs.num;
    }

    bool operator>=(const Rational& rhs) const {
        return num * rhs.den >= den * rhs.num;
    }

    // Method to convert to double
    double toDouble() const {
        return static_cast<double>(num) / den;
    }

    // Method to convert to string
    std::string toString() const {
        return (num == 0) ? "0" : (num < 0) ? "-" + std::to_string(-num) + "/" + std::to_string(den) : num + "/" + std::to_string(den);
    }
};

int main() {
    Rational a(1, 2);
    Rational b(1, 3);

    Rational sum = a + b;
    Rational difference = a - b;
    Rational product = a * b;
    Rational quotient = a / b;

    std::cout << "a: " << a.toString() << std::endl;
    std::cout << "b: " << b.toString() << std::endl;
    std::cout << "a + b: " << sum.toString() << std::endl;
    std::cout << "a - b: " << difference.toString() << std::endl;
    std::cout << "a * b: " << product.toString() << std::endl;
    std::cout << "a / b: " << quotient.toString() << std::endl;
    std::cout << "a == b: " << (a == b) << std::endl;
    std::cout << "a < b: " << (a < b) << std::endl;

    return 0;
}
