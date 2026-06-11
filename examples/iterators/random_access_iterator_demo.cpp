#include <vector>
#include <iostream>

int main()
{
    std::vector<int> v{10,20,30,40,50};

    auto it = v.begin();

    it += 3;

    std::cout << *it << '\n'; // 40
}

/***
Constant-Time Distance
auto distance = v.end() - v.begin();

std::cout << distance;
 */