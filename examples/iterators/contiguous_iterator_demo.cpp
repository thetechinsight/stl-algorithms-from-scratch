#include <vector>
#include <iostream>

int main() {
    std::vector<int> v{10, 20, 30, 40};
    auto it = v.begin();
    std::cout << &(*it) << '\n';
    std::cout << &(*(it + 1)) << '\n';
}