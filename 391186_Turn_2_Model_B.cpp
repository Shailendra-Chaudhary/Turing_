#include<bits/stdc++.h>
using namespace std;

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
    // Rest of the operators (-, *, /, ==, !=, <, >, <=, >=) can be defined similarly

    Rational operator+(int rhs) const {
        return *this + Rational(rhs);
    }
    friend Rational operator+(int lhs, const Rational& rhs) {
        return Rational(lhs) + rhs;
    }
    // Printing rational number
    friend ostream& operator<<(ostream& out, const Rational& obj) {
        if (obj.den == 1) {
            out << obj.num;
        } else {
            out << obj.num << "/" << obj.den;
        }
        return out;
    }
};

Rational harmonicNumber(int n) {
   Rational result = Rational(0);
   for (int i = 1; i <= n; i++){
        result = result + Rational(1, i);
   }
   return result;
}

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;
    Rational ans = harmonicNumber(n);
    cout << "H_n: " << ans << "\n";
	return 0;
}
