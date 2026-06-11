#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    using Iter = std::vector<int>::iterator;

    std::cout
        << typeid(
            std::iterator_traits<Iter>::value_type
           ).name()
        << '\n';
}