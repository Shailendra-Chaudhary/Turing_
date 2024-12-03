#include <iostream>
#include <vector>
#include <map>

// A simple class to track memory allocations
class MemoryTracker {
public:
    static size_t totalMemoryAllocated;

    static void* allocate(size_t size) {
        totalMemoryAllocated += size;
        return malloc(size);
    }

    static void deallocate(void* pointer, size_t size) {
        totalMemoryAllocated -= size;
        free(pointer);
    }
};

size_t MemoryTracker::totalMemoryAllocated = 0;

// Custom allocator using MemoryTracker
template <typename T>
struct CustomAllocator {
    typedef T value_type;

    CustomAllocator() = default;

    template <class U>
    constexpr CustomAllocator(const CustomAllocator<U>&) noexcept {}

    T* allocate(std::size_t n) {
        std::cout << "Allocating " << n * sizeof(T) << " bytes.\n";
        return static_cast<T*>(MemoryTracker::allocate(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) noexcept {
        std::cout << "Deallocating " << n * sizeof(T) << " bytes.\n";
        MemoryTracker::deallocate(p, n * sizeof(T));
    }
};

// Flyweight class: intrinsic state
class Circle {
public:
    Circle(int radius, const std::string& color) : radius_(radius), color_(color) {}

    void draw(int x, int y) const {
        std::cout << "Circle: Draw() [Color : " << color_ << ", radius : " << radius_ << ", x : " << x << ", y :" << y << "]\n";
    }

private:
    int radius_;
    std::string color_;
};

// Flyweight Factory
class CircleFactory {
public:
    Circle* getCircle(const std::string& color) {
        if (circle_map_.find(color) == circle_map_.end()) {
            std::cout << "Creating circle of color : " << color << "\n";
            circle_map_[color] = new Circle(10, color);
        }
        return circle_map_[color];
    }

private:
    std::map<std::string, Circle*, std::less<>, CustomAllocator<std::pair<const std::string, Circle*>>> circle_map_;
};

int main() {
    CircleFactory circleFactory;

    std::vector<Circle*, CustomAllocator<Circle*>> circles;
    circles.push_back(circleFactory.getCircle("Red"));
    circles.push_back(circleFactory.getCircle("Green"));
    circles.push_back(circleFactory.getCircle("Blue"));
    circles.push_back(circleFactory.getCircle("Red"));
    circles.push_back(circleFactory.getCircle("Green"));
    circles.push_back(circleFactory.getCircle("Red"));

    for (int i = 0; i < circles.size(); ++i) {
        int x = i * 10;
        int y = i * 15;
        circles[i]->draw(x, y);
    }

    std::cout << "Total Memory Allocated: " << MemoryTracker::totalMemoryAllocated << " bytes.\n";

    // Clean up
    for (auto entry : circle_factory) {
        delete entry.second;
    }

    return 0;
}
