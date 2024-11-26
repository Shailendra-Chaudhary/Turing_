#include<iostream>
using namespace std;

class ComplexNumber {
private:
    double real;
    double imag;

public:
    // Constructor
    ComplexNumber(double r = 0, double i = 0) {
        real = r;
        imag = i;
    }

    // Overloading == operator for equality check
    bool operator==(const ComplexNumber &other) const {
        return real == other.real && imag == other.imag;
    }

    // Overloading != operator for inequality check
    bool operator!=(const ComplexNumber &other) const {
        return !(*this == other);
    }

    // Overloading < operator for less than check
    bool operator<(const ComplexNumber &other) const {
        if (real != other.real) {
            return real < other.real;
        } else {
            return imag < other.imag;
        }
    }

    // Overloading > operator for greater than check
    bool operator>(const ComplexNumber &other) const {
        return other < *this;
    }

    // Overloading <= operator for less than or equal to check
    bool operator<=(const ComplexNumber &other) const {
        return !(*this > other);
    }

    // Overloading >= operator for greater than or equal to check
    bool operator>=(const ComplexNumber &other) const {
        return !(*this < other);
    }

    // Overloading logical AND operator
    bool operator&&(const ComplexNumber &other) const {
        return (real != 0 || imag != 0) && (other.real != 0 || other.imag != 0);
    }

    // Overloading logical OR operator
    bool operator||(const ComplexNumber &other) const {
        return (real != 0 || imag != 0) || (other.real != 0 || other.imag != 0);
    }

    // Overloading ! operator for logical negation
    bool operator!() const {
        return (real == 0 && imag == 0);
    }

    // Printing the Complex Number
    void print() const {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    ComplexNumber c1(3, 4);
    ComplexNumber c2(5, 6);
    ComplexNumber c3(0, 0);

    // Using overloaded logical operators
    cout << "c1 == c2: " << (c1 == c2) << endl;
    cout << "c1 != c2: " << (c1 != c2) << endl;
    cout << "c1 < c2: " << (c1 < c2) << endl;
    cout << "c1 > c2: " << (c1 > c2) << endl;
    cout << "c1 <= c2: " << (c1 <= c2) << endl;
    cout << "c1 >= c2: " << (c1 >= c2) << endl;
    cout << "c1 && c2: " << (c1 && c2) << endl;
    cout << "c1 || c2: " << (c1 || c2) << endl;
    cout << "!c1: " << (!c1) << endl;
    cout << "!c3: " << (!c3) << endl;
 
    // Printing Complex Numbers
    c1.print();
    c2.print();
    c3.print();
 
    return 0;
}
 
