#include <iostream>
#include <vector>

#include "../include/my_find.hpp"

int main()
{
    std::vector<int> nums{1, 2, 3, 4, 5};

    auto it = my_find(nums.begin(), nums.end(), 13);

    if (it != nums.end())
    {
        std::cout << "Found: " << *it << '\n';
    }
    else
    {
        std::cout << "Not found\n";
    }

    return 0;
}