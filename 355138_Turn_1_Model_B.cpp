#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <functional>

template <typename Container>
void display_container(const Container& container) {
    for (const auto& element : container) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

template <typename Container>
void apply_lambda_to_container(Container& container, const std::function<void(typename Container::value_type&)>& lambda) {
    for (auto& element : container) {
        lambda(element);
    }
}

template <typename Container>
Container apply_filter_lambda(const Container& container, const std::function<bool(const typename Container::value_type&)>& lambda) {
    return Container(std::remove_if(container.begin(), container.end(), lambda), container.end());
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::list<int> lst = {6, 7, 8, 9, 10};
    std::deque<int> dq = {11, 12, 13, 14, 15};

    {
        std::cout << "Original containers:\n";
        display_container(vec);
        display_container(lst);
        display_container(dq);
    }

    {
        // Apply lambda function to double each element
        auto double_lambda = [](int& x) { x *= 2; };

        std::cout << "\nAfter applying double_lambda:\n";
        apply_lambda_to_container(vec, double_lambda);
        apply_lambda_to_container(lst, double_lambda);
        apply_lambda_to_container(dq, double_lambda);
        display_container(vec);
        display_container(lst);
        display_container(dq);
    }

    {
        // Filter elements divisible by 3 using lambda
        auto is_divisible_by_three = [](const int& x) { return x % 3 == 0; };

        std::cout << "\nAfter filtering elements divisible by 3:\n";
        vec = apply_filter_lambda(vec, is_divisible_by_three);
        lst = apply_filter_lambda(lst, is_divisible_by_three);
        dq = apply_filter_lambda(dq, is_divisible_by_three);
        display_container(vec);
        display_container(lst);
        display_container(dq);
    }

    return 0;
}
