#include <iostream>
#include <cassert>

// Macro definitions for preconditions, postconditions, and invariants
#define PRECONDITION(condition) if (!(condition)) throw std::runtime_error(#condition)
#define POSTCONDITION(condition) if (!(condition)) throw std::runtime_error(#condition)
#define INVARIANT(condition) if (!(condition)) throw std::runtime_error(#condition)

class Stack {
private:
    int* elements;
    int size;
    int capacity;

    void resize() {
        int new_capacity = capacity * 2;
        int* new_elements = new int[new_capacity];
        for (int i = 0; i < size; ++i) {
            new_elements[i] = elements[i];
        }
        delete[] elements;
        elements = new_elements;
        capacity = new_capacity;
    }

public:
    Stack() : size(0), capacity(1) {
        elements = new int[capacity];
        // Invariant: Size must be less than or equal to capacity
        INVARIANT(size <= capacity);
    }

    ~Stack() {
        delete[] elements;
    }

    void push(int value) {
        PRECONDITION(size < capacity);
        elements[size++] = value;
        // Invariant: Size must be less than or equal to capacity
        INVARIANT(size <= capacity);
    }

    int pop() {
        PRECONDITION(size > 0);
        int value = elements[--size];
        // Postcondition: Size must be decreased by one
        POSTCONDITION(size == (size + 1));
        // Invariant: Size must be less than or equal to capacity
        INVARIANT(size <= capacity);
        return value;
    }

    bool isEmpty() const {
        return size == 0;
    }
};

int main() {
    Stack stack;

    stack.push(10);
    stack.push(20);

    std::cout << "Popped value: " << stack.pop() << std::endl;

    // Uncommenting the next line will cause an exception due to precondition violation
    // stack.pop();

    return 0;
}
