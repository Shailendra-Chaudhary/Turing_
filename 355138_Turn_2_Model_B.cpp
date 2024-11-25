#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <functional>
#include <ranges>
#include <iterator>

int main() {
    std::vector<int> vec = {1, 2, 3};
    std::list<int> lst = {4, 5, 6, 7};
    std::deque<int> dq = {8, 9};

    auto combined_containers = vec | std::views::append(lst) | std::views::append(dq);

    {
        std::cout << "Original containers:\n";
        for (const auto& num : vec) {
            std::cout << num << " ";
        }
        std::cout << "\n";
        for (const auto& num : lst) {
            std::cout << num << " ";
        }
        std::cout << "\n";
        for (const auto& num : dq) {
            std::cout << num << " ";
        }
        std::cout << "\n";
    }

    {
        std::cout << "Combined view:\n";
        for (const auto& num : combined_containers) {
            std::cout << num << " ";
        }
        std::cout << "\n";
    }

    {
        // Apply lambda function to double each element in the combined view
        auto double_lambda = [](int& x) { x *= 2; };

        std::cout << "\nAfter applying double_lambda to combined view:\n";
        for (auto& num : combined_containers) {
            double_lambda(num);
        }
        for (const auto& num : combined_containers) {
            std::cout << num << " ";
        }
        std::cout << "\n";
    }

    {
        // Filter elements divisible by 3 using lambda on the combined view
        auto is_divisible_by_three = [](const int& x) { return x % 3 == 0; };

        std::cout << "\nElements divisible by 3 after filtering combined view:\n";
        auto filtered_elements = combined_containers | std::views::filter(is_divisible_by_three);
        for (const auto& num : filtered_elements) {
            std::cout << num << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
