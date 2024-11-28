#include <iostream>
#include <vector>
#include <algorithm>

// Define a simple class for demonstration
struct Item {
    int value;
    Item(int val) : value(val) {}
    Item(Item&& other) : value(std::move(other.value)) {}
    Item& operator=(Item&& other) {
        value = std::move(other.value);
        return *this;
    }
    ~Item() {
        std::cout << "Destructor called for value: " << value << std::endl;
    }
};

// Custom predicate function to remove even numbers
bool isEven(const Item& item) {
    return item.value % 2 == 0;
}

// Custom eraser using std::remove_if and std::vector::erase
template <typename Container>
void customErase(Container& container, typename Container::iterator start, typename Container::iterator end) {
    container.erase(start, end);
}

// Custom mover using std::remove_if_with_move_backward
template <typename Container>
typename Container::iterator customMove(Container& container, typename Container::iterator start, typename Container::iterator end) {
    return std::remove_if_with_move_backward(start, end, container.end(), isEven);
}

int main() {
    std::vector<Item> items = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::cout << "Original vector size: " << items.size() << std::endl;
    for (const auto& item : items) {
        std::cout << item.value << " ";
    }
    std::cout << std::endl;

    // Using customErase with std::remove_if
    auto newEnd = std::remove_if(items.begin(), items.end(), isEven);
    customErase(items, newEnd, items.end());

    std::cout << "Vector size after customErase: " << items.size() << std::endl;
    for (const auto& item : items) {
        std::cout << item.value << " ";
    }
    std::cout << std::endl;

    // Using customMove with std::remove_if_with_move_backward
    items = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto newEndMove = customMove(items, items.begin(), items.end());
    items.resize(newEndMove - items.begin());

    std::cout << "Vector size after customMove: " << items.size() << std::endl;
    for (const auto& item : items) {
        std::cout << item.value << " ";
    }
    std::cout << std::endl;

    return 0;
}
