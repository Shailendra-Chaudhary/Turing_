#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

//Custom Predicate
struct IsDivisibleByThree
{
    bool operator()(const std::unique_ptr<int>& ptr) const
    {
        return *ptr % 3 == 0;
    }
};

// Custom erase algorithm for unique_ptr vectors
template <typename ForwardIt, typename Predicate>
ForwardIt custom_erase_if(ForwardIt first, ForwardIt last, Predicate pred) {
    using value_type = typename std::iterator_traits<ForwardIt>::value_type;
    
    ForwardIt d_first = first;
    while (first != last) {
        if (!pred(*first)) {
            // Move the element only if it's not being deleted
            *d_first = std::move(*first);
            ++d_first;
        }
        ++first;
    }
    return d_first;
}

int main()
{
    std::vector<std::unique_ptr<int>> v;
    for (int i = 1; i <= 20; ++i) 
    {
        v.emplace_back(std::make_unique<int>(i));
    }

    // before removing : 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
    for (const auto& ptr : v) {
        std::cout << *ptr << " ";
    }
    std::cout << "\n";
    
    //Use custom erase and move algorithm to remove elements divisible by 3
    auto new_end = custom_erase_if(v.begin(), v.end(), IsDivisibleByThree());
    
    v.erase(new_end, v.end());

    // after removing : 1 2 4 5 7 8 10 11 13 14 16 17 19 
    for (const auto& ptr : v) {
        std::cout << *ptr << " ";
    }
    std::cout << "\n";
    return 0;
}                  
