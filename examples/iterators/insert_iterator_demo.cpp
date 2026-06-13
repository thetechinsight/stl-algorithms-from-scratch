#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <set>
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
    std::vector<int> source{1, 2, 3, 4};

    print_container(source, "source");

    std::cout << "\n=== back_inserter ===\n";

    std::vector<int> vec_dest;

    std::copy(
        source.begin(),
        source.end(),
        std::back_inserter(vec_dest));

    print_container(vec_dest, "vec_dest");

    std::cout << "\nConceptually:\n";
    std::cout << "push_back(1)\n";
    std::cout << "push_back(2)\n";
    std::cout << "push_back(3)\n";
    std::cout << "push_back(4)\n";

    std::cout << "\n=== front_inserter ===\n";

    std::deque<int> deque_dest;

    std::copy(
        source.begin(),
        source.end(),
        std::front_inserter(deque_dest));

    print_container(deque_dest, "deque_dest");

    std::cout << "\nConceptually:\n";
    std::cout << "push_front(1)\n";
    std::cout << "push_front(2)\n";
    std::cout << "push_front(3)\n";
    std::cout << "push_front(4)\n";

    std::cout << "\n=== inserter ===\n";

    std::set<int> s{100, 200, 300};

    print_container(s, "before");

    std::copy(
        source.begin(),
        source.end(),
        std::inserter(s, s.begin()));

    print_container(s, "after");

    std::cout << "\nElements inserted using\n";
    std::cout << "container.insert(pos, value)\n";

    return 0;
}

/**
source: 1 2 3 4

=== back_inserter ===
vec_dest: 1 2 3 4

Conceptually:
push_back(1)
push_back(2)
push_back(3)
push_back(4)

=== front_inserter ===
deque_dest: 4 3 2 1

Conceptually:
push_front(1)
push_front(2)
push_front(3)
push_front(4)

=== inserter ===
before: 100 200 300
after: 1 2 3 4 100 200 300

Elements inserted using
container.insert(pos, value)

*/