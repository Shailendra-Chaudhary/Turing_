#include<iostream>
using namespace std;

class Point {
private:
    int x;
    int y;

public:
    Point(int a = 0, int b = 0) {
        x = a;
        y = b;
    }

    // Overloading == operator for equality check
    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }

    // Overloading != operator for inequality check
    bool operator!=(const Point &other) const {
        return !(*this == other);
    }

    // Overloading < operator for less than check based on x-coordinate first
    bool operator<(const Point &other) const {
        return x < other.x || (x == other.x && y < other.y);
    }

    // Overloading logical AND operator for checking if both x and y are positive
    bool operator&&(const Point &other) const {
        return x > 0 && y > 0 && other.x > 0 && other.y > 0;
    }

    // Overloading logical OR operator for checking if any of the coordinates is positive
    bool operator||(const Point &other) const {
        return x > 0 || y > 0 || other.x > 0 || other.y > 0;
    }

    // Overloading ! operator for checking if both x and y are zero
    bool operator!() const {
        return x == 0 && y == 0;
    }

    // Printing the Point
    void print() const {
        cout << "(" << x << ", " << y << ")" << endl;
    }
};

int main() {
    Point p1(1, 2);
    Point p2(3, 4);
    Point p3(0, 0);
    Point p4(-1, -2);

    // Using overloaded logical operators for better readability
    if (p1 == p2) {
        cout << "p1 and p2 are equal." << endl;
    } else {
        cout << "p1 and p2 are not equal." << endl;
    }

    if (p1 < p2) {
        cout << "p1 is less than p2." << endl;
    } else {
        cout << "p1 is greater than or equal to p2." << endl;
    }

    if (p1 && p2) {
        cout << "Both p1 and p2 have positive coordinates." << endl;
    } else {
        cout << "At least one of p1 or p2 has negative coordinates." << endl;
    }

    if (p1 || p2) {
        cout << "At least one of p1 or p2 has positive coordinates." << endl;
    } else {
        cout << "Both p1 and p2 have negative coordinates." << endl;
    }

    if (!p3) {
        cout << "p3 has zero coordinates." << endl;
    }

    if (!p4) {
        cout << "p4 has zero coordinates." << endl;
    }

    return 0;
} 
