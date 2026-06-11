#pragma once

template<typename Iterator, typename T>
Iterator my_find(Iterator first, Iterator last, const T& value)
{
    while (first != last)
    {
        if (*first == value)
        {
            return first;
        }

        ++first;
    }

    return last;
}