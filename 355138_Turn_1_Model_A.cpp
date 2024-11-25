#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <functional>

template <typename Container>
void displayContainer(const Container& container, const std::string& name)
{
    std::cout << "\nContents of " << name << ":\n";
    for (const auto& element : container) {
        std::cout << element << " ";
    }
    std::cout << "\n";
}

template <typename Container>
void applyLambda(Container& container, const std::string& name, const std::function<void(typename Container::iterator)>& lambda)
{
    std::cout << "\nApplying lambda to " << name << ":\n";
    std::for_each(container.begin(), container.end(), lambda);
    displayContainer(container, name);
}

int main()
{
    std::vector<int> myVector = {1, 2, 3, 4, 5};
    std::list<int> myList = {6, 7, 8, 9, 10};
    std::deque<int> myDeque = {11, 12, 13, 14, 15};

    // Display initial contents
    displayContainer(myVector, "myVector");
    displayContainer(myList, "myList");
    displayContainer(myDeque, "myDeque");

    // Apply lambda function to multiply each element by 2
    auto multiplyByTwo = [](auto& it) { *it *= 2; };

    applyLambda(myVector, "myVector", multiplyByTwo);
    applyLambda(myList, "myList", multiplyByTwo);
    applyLambda(myDeque, "myDeque", multiplyByTwo);

    // Display containers after applying lambda
    displayContainer(myVector, "myVector");
    displayContainer(myList, "myList");
    displayContainer(myDeque, "myDeque");

    return 0;
}
