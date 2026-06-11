#pragma once

template<typename Iterator, typename T>
std::size_t my_count(Iterator first, Iterator last, const T& value)
{
    std::size_t count = 0;
    while (first != last)
    {
        if (*first == value)
        {
            ++count;
        }

        ++first;
    }

    return count;
}