# Introduction to Iterators

## What is an Iterator?

An iterator is an object that behaves like a generalized pointer.

Just as a pointer can traverse elements in an array, an iterator can traverse elements in many different container types.

Example:

```cpp
int arr[] = {10, 20, 30};

int* p = arr;

std::cout << *p;   // 10

++p;

std::cout << *p;   // 20
```

The Standard Template Library (STL) extends this idea by providing iterators for containers such as:

* std::vector
* std::list
* std::deque
* std::set
* std::map

This allows algorithms to work independently of the container type.

---

## Why Iterators Exist

Without iterators, every algorithm would need a different implementation for each container.

Example:

```cpp
find_in_vector(...)
find_in_list(...)
find_in_set(...)
```

STL avoids this by expressing algorithms in terms of iterators.

Example:

```cpp
std::find(first, last, value);
```

The algorithm only knows how to use iterators.

It does not know which container is being traversed.

---

## Core Iterator Operations

Most iterators support:

```cpp
*it      // access current element

++it     // move to next element

it != end
```

Example:

```cpp
for(auto it = v.begin(); it != v.end(); ++it)
{
    std::cout << *it << '\n';
}
```

---

## Iterators and Generic Programming

Consider:

```cpp
template<typename Iterator, typename T>
Iterator my_find(Iterator first,
                 Iterator last,
                 const T& value)
{
    while(first != last)
    {
        if(*first == value)
            return first;

        ++first;
    }

    return last;
}
```

This algorithm works with:

* vector iterators
* list iterators
* set iterators
* raw pointers

because all of them satisfy the iterator requirements needed by the algorithm.

---

## Key Insight

Algorithms do not operate on containers.

Algorithms operate on iterators.

Containers provide iterators.

This separation is one of the most important design ideas in STL.
