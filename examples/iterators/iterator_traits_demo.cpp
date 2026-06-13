#include <iostream>
#include <iterator>
#include <list>
#include <type_traits>
#include <vector>

template <typename Iterator>
void inspect_iterator(const std::string& name)
{
    using Traits = std::iterator_traits<Iterator>;

    std::cout << "=================================\n";
    std::cout << name << '\n';
    std::cout << "=================================\n";

    std::cout << "value_type       : "
              << typeid(typename Traits::value_type).name()
              << '\n';

    std::cout << "difference_type  : "
              << typeid(typename Traits::difference_type).name()
              << '\n';

    std::cout << "pointer          : "
              << typeid(typename Traits::pointer).name()
              << '\n';

    std::cout << "reference        : "
              << typeid(typename Traits::reference).name()
              << '\n';

    std::cout << "iterator_category: ";

    using Category = typename Traits::iterator_category;

    if constexpr (std::is_same_v<
                      Category,
                      std::input_iterator_tag>)
    {
        std::cout << "input_iterator_tag";
    }
    else if constexpr (std::is_same_v<
                           Category,
                           std::output_iterator_tag>)
    {
        std::cout << "output_iterator_tag";
    }
    else if constexpr (std::is_same_v<
                           Category,
                           std::forward_iterator_tag>)
    {
        std::cout << "forward_iterator_tag";
    }
    else if constexpr (std::is_same_v<
                           Category,
                           std::bidirectional_iterator_tag>)
    {
        std::cout << "bidirectional_iterator_tag";
    }
    else if constexpr (std::is_same_v<
                           Category,
                           std::random_access_iterator_tag>)
    {
        std::cout << "random_access_iterator_tag";
    }
    else
    {
        std::cout << "unknown";
    }

    std::cout << "\n\n";
}

/**
=================================
std::vector<int>::iterator
=================================
value_type       : int
difference_type  : long
pointer          : int*
reference        : int&
iterator_category: random_access_iterator_tag

=================================
std::list<int>::iterator
=================================
value_type       : int
difference_type  : long
pointer          : int*
reference        : int&
iterator_category: bidirectional_iterator_tag

=================================
int*
=================================
value_type       : int
difference_type  : long
pointer          : int*
reference        : int&
iterator_category: random_access_iterator_tag
 */
int main()
{
    inspect_iterator<
        std::vector<int>::iterator>(
            "std::vector<int>::iterator");

    inspect_iterator<
        std::list<int>::iterator>(
            "std::list<int>::iterator");

    inspect_iterator<
        int*>(
            "int*");  // int* reports as a random access iterator tag
            /* for example, this allows us to do because Pointers ARE iterators.
            int arr[] = {1,2,3,4};
            std::sort(
                std::begin(arr),
                std::end(arr)); 
    */
}