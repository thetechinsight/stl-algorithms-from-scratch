#include <forward_list>
#include <iostream>

int main() {
    std::forward_list<int> fl{1, 2, 3, 4};

    auto a = fl.begin();
    auto b = fl.begin();

    ++a;

    std::cout << *a << '\n'; // 2
    std::cout << *b << '\n'; // 1

    /***
    b is still valid because a Forward Iterator provides independent, multi-pass traversal. 
    Each iterator maintains its own position in the sequence, so incrementing a has no effect on b. 
     */
    return 0;
}