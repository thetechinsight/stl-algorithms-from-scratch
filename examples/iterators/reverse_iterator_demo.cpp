#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::vector<int> v{10, 20, 30, 40, 50};

    std::cout << "Forward traversal:\n";

    for (auto it = v.begin(); it != v.end(); ++it)
    {
        std::cout << *it << ' ';
    }

    std::cout << "\n\n";

    std::cout << "Reverse traversal:\n";

    for (auto rit = v.rbegin(); rit != v.rend(); ++rit)
    {
        std::cout << *rit << ' ';
    }

    std::cout << "\n\n";

    auto rit = v.rbegin();

    std::cout << "First reverse element : "
              << *rit
              << '\n';

    std::cout << "rit.base() == v.end() : "
              << std::boolalpha
              << (rit.base() == v.end())
              << '\n';

    std::cout << "\n";

    std::cout << "Using std::copy with reverse iterators:\n";

    std::copy(
        v.rbegin(),
        v.rend(),
        std::ostream_iterator<int>(std::cout, " "));

    std::cout << '\n';
}

/**
Expected Output:

Forward traversal:
10 20 30 40 50

Reverse traversal:
50 40 30 20 10

First reverse element : 50
rit.base() == v.end() : true

Using std::copy with reverse iterators:
50 40 30 20 10

*/