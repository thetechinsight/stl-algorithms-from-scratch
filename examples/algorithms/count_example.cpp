#include <iostream>
#include <vector>

#include "../include/my_count.hpp"

int main()
{
    std::vector<int> nums{1, 2, 2, 3, 2};

    int count = my_count(nums.begin(), nums.end(), 2);

    std::cout << "Count: " << count << '\n';
    
    count = my_count(nums.begin(), nums.end(), 0);

    std::cout << "Count: " << count << '\n';
    return 0;
}