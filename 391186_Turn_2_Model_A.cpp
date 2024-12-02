#include <iostream>
#include <numeric>

class Rational {
private:
    int num, den;

public:
    Rational(int n = 0, int d = 1) : num(n), den(std::abs(d)) {
        if (den == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }
        simplify();
    }

    void simplify() {
        int gcd = std::gcd(num, den);
        num /= gcd;
        den /= gcd;
        if (den < 0) {
            num = -num;
            den = -den;
        }
    }

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

    std::string toString() const {
        return (num == 0) ? "0" : (num < 0) ? "-" + std::to_string(-num) + "/" + std::to_string(den) : num + "/" + std::to_string(den);
    }
};

int main() {
    // Define two points in the plane
    int x1 = 1, y1 = 2;
    int x2 = 4, y2 = 6;

    // Calculate the slope using the formula (y2 - y1) / (x2 - x1)
    Rational slope = Rational(y2 - y1, x2 - x1);

    // Print the slope
    std::cout << "Slope of the line segment is: " << slope.toString() << std::endl;

    return 0;
}
