#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

template <typename Container>
void print_container(const Container& c,
                     const std::string& name)
{
    std::cout << name << ": ";

    for (const auto& elem : c)
    {
        std::cout << elem << ' ';
    }

    std::cout << '\n';
}

int main()
{
    std::cout << "=====================================\n";
    std::cout << "Example 1: ostream_iterator\n";
    std::cout << "=====================================\n";

    std::vector<int> v{10, 20, 30, 40};

    std::copy(
        v.begin(),
        v.end(),
        std::ostream_iterator<int>(std::cout, " "));

    std::cout << "\n\n";

    std::cout << "=====================================\n";
    std::cout << "Example 2: istream_iterator -> vector\n";
    std::cout << "=====================================\n";

    std::istringstream input("1 2 3 4 5");

    std::vector<int> values;

    std::copy(
        std::istream_iterator<int>(input),
        std::istream_iterator<int>(),
        std::back_inserter(values));

    print_container(values, "values");

    std::cout << "\n";

    std::cout << "=====================================\n";
    std::cout << "Example 3: stream -> algorithm -> stream\n";
    std::cout << "=====================================\n";

    std::istringstream numbers("100 200 300 400");

    std::copy(
        std::istream_iterator<int>(numbers),
        std::istream_iterator<int>(),
        std::ostream_iterator<int>(std::cout, "\n"));

    return 0;
}

/**
=====================================
Example 1: ostream_iterator
=====================================
10 20 30 40

=====================================
Example 2: istream_iterator -> vector
=====================================
values: 1 2 3 4 5

=====================================
Example 3: stream -> algorithm -> stream
=====================================
100
200
300
400
 */