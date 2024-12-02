#include <iostream>
#include <vector>
#include <memory>

class Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual ~Shape() = default;
};

class Rectangle : public Shape {
private:
    double length;
    double width;

public:
    Rectangle(double length, double width) : length(length), width(width) {}
    double area() const override { return length * width; }
    double perimeter() const override { return 2 * (length + width); }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double radius) : radius(radius) {}
    double area() const override { return 3.14 * radius * radius; }
    double perimeter() const override { return 2 * 3.14 * radius; }
};

// Function overloading to calculate the total area of a shape
double totalArea(const Rectangle& rect) {
    return rect.area();
}

double totalArea(const Circle& circle) {
    return circle.area();
}

// Challenge: Trying to overload the function based on the return type will lead to an error
// void totalArea(const Shape& shape) {
//     // Error: Cannot use Shape as a base for return type
//     return shape.area();
// }

// Template class to store and manipulate a collection of shapes
template <typename T>
class ShapeContainer {
private:
    std::vector<std::unique_ptr<T>> shapes;

public:
    void addShape(std::unique_ptr<T> shape) {
        shapes.push_back(std::move(shape));
    }

    // Challenge: Function overloading to calculate the total area of all shapes in the container
    // Restriction: We can't directly overload the function based on the template type 'T'
    // This is because the template can be instantiated with different types, and we don't want to create separate functions for each shape type.
    // Instead, we'll use a technique called "static polymorphism" through virtual functions.
    double totalArea() const {
        double total = 0;
        for (const auto& shape : shapes) {
            total += shape->area();  // We call the virtual area() function here
        }
        return total;
    }
};

int main() {
    Rectangle rect(10, 20);
    Circle circle(5);

    std::cout << "Area of Rectangle: " << totalArea(rect) << std::endl;
    std::cout << "Area of Circle: " << totalArea(circle) << std::endl;

    // Using ShapeContainer with Rectangle
    ShapeContainer<Rectangle> rectContainer;
    rectContainer.addShape(std::make_unique<Rectangle>(3, 4));
    rectContainer.addShape(std::make_unique<Rectangle>(5, 12));
    std::cout << "Total Area of Rectangles: " << rectContainer.totalArea() << std::endl;

    // Using ShapeContainer with Circle
    ShapeContainer<Circle> circleContainer;
    circleContainer.addShape(std::make_unique<Circle>(3));
    circleContainer.addShape(std::make_unique<Circle>(7));
    std::cout << "Total Area of Circles: " << circleContainer.totalArea() << std::endl;

    return 0;
} 
