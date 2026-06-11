#include <list>
#include <iostream>

int main()
{
    std::list<int> lst{10,20,30,40};

    auto it = lst.begin();

    ++it;
    ++it;

    std::cout << *it << '\n'; // 30

    --it;

    std::cout << *it << '\n'; // 20

    // Note: it + 2;    // ERROR
    // Can move both directions.
    return 0;
}