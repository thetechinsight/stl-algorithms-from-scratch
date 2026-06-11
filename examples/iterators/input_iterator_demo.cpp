#include <iostream>
#include <iterator>

int main()
{
    std::istream_iterator<int> first(std::cin);
    std::istream_iterator<int> last;

    while(first != last)
    {
        std::cout << *first << '\n';
        ++first;
    }
    return 0;
}