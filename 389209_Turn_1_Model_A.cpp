#include <vector>
#include <iostream>

class MyClass {
public:
    int value;
    MyClass(int v) : value(v) {}
};

int main() {
    std::vector<MyClass> v;
    v.push_back(MyClass(10));
    v.push_back(MyClass(20));
    v.push_back(MyClass(30));

    std::cout << v[1].value << std::endl; // Access by index
    return 0;
}
