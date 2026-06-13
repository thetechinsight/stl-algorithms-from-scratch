#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

void print_vector(const std::vector<std::string>& v,
                  const std::string& name)
{
    std::cout << name << ":\n";

    for (std::size_t i = 0; i < v.size(); ++i)
    {
        std::cout << "  [" << i << "] = \""
                  << v[i]
                  << "\"\n";
    }

    std::cout << '\n';
}

int main()
{
    std::vector<std::string> source{
        "one",
        "two",
        "three"
    };

    std::vector<std::string> destination;

    std::cout << "Before move:\n\n";

    print_vector(source, "source");
    print_vector(destination, "destination");

    std::copy(
        std::make_move_iterator(source.begin()),
        std::make_move_iterator(source.end()),
        std::back_inserter(destination));

    std::cout << "After move:\n\n";

    print_vector(source, "source");
    print_vector(destination, "destination");

    return 0;
}

/**
Before move:

source:
  [0] = "one"
  [1] = "two"
  [2] = "three"

destination:

After move:

source:
  [0] = ""
  [1] = ""
  [2] = ""

destination:
  [0] = "one"
  [1] = "two"
  [2] = "three"
  
  */