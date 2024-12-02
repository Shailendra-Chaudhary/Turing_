#include <iostream>
#include <algorithm>
using namespace std;
 
// Rational class for representing and manipulating rational numbers
class Rational {
public:
    int numerator, denominator;

    // Default constructor: sets the rational number to 0/1
    Rational() : numerator(0), denominator(1) {}

    // Constructor with an integer: sets the rational number to num/1
    Rational(int num) : numerator(num), denominator(1) {}

    // Constructor with two integers: sets the rational number to num/den
    Rational(int num, int den) : numerator(num), denominator(den) {
        normalize();
    }

    // Normalize the rational number by dividing both numerator and denominator by their greatest common divisor (GCD)
    void normalize() {
        int gcd = greatestCommonDivisor(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
    }

    // Find the greatest common divisor (GCD) of two integers using the Euclidean algorithm
    int greatestCommonDivisor(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    // Addition operator overloading
    Rational operator+(const Rational& other) const {
        int new_numerator = numerator * other.denominator + other.numerator * denominator;
        int new_denominator = denominator * other.denominator;
        return Rational(new_numerator, new_denominator);
    }

    // Subtraction operator overloading
    Rational operator-(const Rational& other) const {
        int new_numerator = numerator * other.denominator - other.numerator * denominator;
        int new_denominator = denominator * other.denominator;
        return Rational(new_numerator, new_denominator);
    }

    // Multiplication operator overloading
    Rational operator*(const Rational& other) const {
        int new_numerator = numerator * other.numerator;
        int new_denominator = denominator * other.denominator;
        return Rational(new_numerator, new_denominator);
    }

    // Division operator overloading
    Rational operator/(const Rational& other) const {
        int new_numerator = numerator * other.denominator;
        int new_denominator = denominator * other.numerator;
        return Rational(new_numerator, new_denominator);
    }

    // Equality operator overloading
    bool operator==(const Rational& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    // Less-than operator overloading
    bool operator<(const Rational& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }

    // Output stream operator overloading for easy printing
    friend ostream& operator<<(ostream& os, const Rational& r) {
        os << r.numerator << "/" << r.denominator;
        return os;
    }
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    Rational r1(1, 2), r2(2, 3);

    cout << "r1 = " << r1 << endl;  // Output: r1 = 1/2
    cout << "r2 = " << r2 << endl;  // Output: r2 = 2/3

    cout << "r1 + r2 = " << r1 + r2 << endl;  // Output: r1 + r2 = 7/6
    cout << "r1 - r2 = " << r1 - r2 << endl;  // Output: r1 - r2 = -1/6
    cout << "r1 * r2 = " << r1 * r2 << endl;  // Output: r1 * r2 = 1/3
    cout << "r1 / r2 = " << r1 / r2 << endl;  // Output: r1 / r2 = 3/4

    cout << "r1 == r2 = " << (r1 == r2) << endl;  // Output: r1 == r2 = 0
    cout << "r1 < r2 = " << (r1 < r2) << endl;  // Output: r1 < r2 = 1

    return 0;
}
