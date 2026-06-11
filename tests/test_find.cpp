#include <cassert>
#include <vector>

#include "../include/my_find.hpp"

int main()
{
    std::vector<int> nums{1, 2, 3, 4, 5};

    auto it = my_find(nums.begin(), nums.end(), 3);

    assert(it != nums.end());
    assert(*it == 3);

    auto missing = my_find(nums.begin(), nums.end(), 10);

    assert(missing == nums.end());
}