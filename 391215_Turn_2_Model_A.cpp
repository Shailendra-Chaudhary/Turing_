#include <iostream>

class Calculator {
public:
    double add(double a, double b) {
        std::cout << "Adding: " << a << " + " << b << std::endl;
        return a + b;
    }

    double subtract(double a, double b) {
        std::cout << "Subtracting: " << a << " - " << b << std::endl;
        return a - b;
    }
};

int main() {
    Calculator cal;
    std::cout << cal.add(5.0, 3.0) << std::endl;
    std::cout << cal.subtract(5.0, 3.0) << std::endl;
}
