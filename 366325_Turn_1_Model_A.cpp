#include <iostream>

class Vector2D {
private:
    double x;
    double y;

public:
    // Constructor
    Vector2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    // Accessors
    double getX() const { return x; }
    double getY() const { return y; }

    // Overloading the == operator
    friend bool operator==(const Vector2D& left, const Vector2D& right) {
        return left.x == right.x && left.y == right.y;
    }

    // Overloading the != operator (optional, but often useful alongside ==)
    friend bool operator!=(const Vector2D& left, const Vector2D& right) {
        return !(left == right);
    }

    // Function to print the vector
    void print() const {
        std::cout << "Vector2D(" << x << ", " << y << ")" << std::endl;
    }
};

int main() {
    // Creating instances of Vector2D
    Vector2D vector1(1.0, 2.0);
    Vector2D vector2(1.0, 2.0);
    Vector2D vector3(3.0, 4.0);

    // Checking for equality using the overloaded == operator
    if (vector1 == vector2) {
        std::cout << "Vector1 is equal to Vector2." << std::endl;
    } else {
        std::cout << "Vector1 is not equal to Vector2." << std::endl;
    }

    if (vector1 != vector3) {
        std::cout << "Vector1 is not equal to Vector3." << std::endl;
    } else {
        std::cout << "Vector1 is equal to Vector3." << std::endl;
    }

    // Printing the vectors
    vector1.print();
    vector2.print();
    vector3.print();

    return 0;
}
