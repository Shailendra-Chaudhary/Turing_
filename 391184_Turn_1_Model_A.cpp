#include <iostream>

// Valid overloading: different parameter lists
void greet(std::string name) {
    std::cout << "Hello, " << name << "!" << std::endl;
}

void greet(int age) {
    std::cout << "Hello, you are " << age << " years old!" << std::endl;
}

// Invalid overloading: same parameter list, different return type
// void greet(std::string name) {
//     std::cout << "Hi, " << name << "!" << std::endl;
// }

// Invalid overloading: same parameter list, different default parameter
// void greet(std::string name, int age = 0) {
//     std::cout << "Hello, " << name << ", you are " << age << " years old!" << std::endl;
// }

int main() {
    greet("Alice"); // Calls greet(std::string)
    greet(30);      // Calls greet(int)
    return 0;
}
