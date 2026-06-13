# Iterator Fundamentals

## Learning Objectives

After completing this chapter, you should be able to:

* Explain what an iterator is
* Explain why iterators exist
* Understand the relationship between containers, iterators, and algorithms
* Understand STL ranges
* Understand begin() and end()
* Explain STL's generic programming model

---

# The Problem STL Solves

Suppose we want to find a value inside different container types.

Without iterators we might need:

```cpp
find_in_vector(...)
find_in_list(...)
find_in_set(...)
find_in_deque(...)
```

Every algorithm would need to understand every container implementation.

This does not scale.

The STL solves this problem using iterators.

---

# What Is an Iterator?

An iterator is an object that represents a position within a sequence.

A useful mental model is:

```text
Iterator = Generalized Pointer
```

Just as a pointer can traverse an array, an iterator can traverse many different container types.

Example:

```cpp
int arr[] = {10, 20, 30};

int* p = arr;

std::cout << *p; // 10

++p;

std::cout << *p; // 20
```

The STL generalizes this concept.

---

# The Three Pillars of STL

The STL consists of:

```text
Containers
Iterators
Algorithms
```

Responsibilities:

| Component | Responsibility |
| --------- | -------------- |
| Container | Stores data    |
| Iterator  | Accesses data  |
| Algorithm | Processes data |

---

# How STL Views the World

Traditional design:

```text
Algorithm
    ↓
Container
```

STL design:

```text
Container
    ↓
Iterator
    ↓
Algorithm
```

Algorithms do not know which container they are working with.

Algorithms only know how to use iterators.

---

# Generic Programming

Consider:

```cpp
template<typename Iterator,
         typename T>
Iterator my_find(
    Iterator first,
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

```cpp
std::vector
std::list
std::deque
std::set
raw pointers
```

because it operates only on iterators.

---

# Core Iterator Operations

Most iterators support:

```cpp
*it
```

Access current element.

```cpp
++it
```

Move to next element.

```cpp
it != end
```

Determine whether traversal is finished.

Example:

```cpp
for(auto it = v.begin();
    it != v.end();
    ++it)
{
    std::cout << *it << '\n';
}
```

---

# Obtaining Iterators

Containers provide iterators.

Example:

```cpp
std::vector<int> v{10,20,30};
```

Beginning of range:

```cpp
auto first = v.begin();
```

End of range:

```cpp
auto last = v.end();
```

---

# Understanding Ranges

Most STL algorithms operate on:

```cpp
[first, last)
```

This means:

```text
first = included
last  = excluded
```

Example:

```cpp
std::vector<int> v{10,20,30,40};
```

Range:

```cpp
[v.begin(), v.end())
```

contains:

```text
10 20 30 40
```

---

# Why end() Is Not the Last Element

One of the most common interview questions.

Consider:

```cpp
std::vector<int> v{10,20,30};
```

Conceptually:

```text
10 20 30
         ^
         end()
```

`end()` points one position past the final element.

This design simplifies iteration.

Example:

```cpp
while(it != end)
{
    ...
}
```

No special handling is required for the last element.

---

# Advantages of Iterators

Iterators provide:

* Generic programming
* Code reuse
* Container independence
* Flexible algorithm design
* Strong abstraction

Without iterators, STL would not be possible.

---

# Real STL Example

The same algorithm:

```cpp
std::find(first, last, value);
```

works with:

```cpp
std::vector<int>
std::list<int>
std::deque<int>
std::set<int>
int*
```

because it depends only on iterator operations.

---

# Interview Questions

## Q1

What is an iterator?

Answer:

An iterator is an object that represents a position within a sequence and provides a generalized pointer-like interface for traversing elements.

---

## Q2

Why does STL use iterators?

Answer:

To separate algorithms from containers and enable generic programming.

---

## Q3

What are the three pillars of STL?

Answer:

```text
Containers
Iterators
Algorithms
```

---

## Q4

What does `[first,last)` mean?

Answer:

The range includes `first` and excludes `last`.

---

## Q5

Why does `end()` point past the last element?

Answer:

It simplifies iteration and range representation.

---

# Key Takeaways

1. Iterators are generalized pointers.
2. Algorithms operate on iterators rather than containers.
3. Iterators enable generic programming.
4. STL is built around containers, iterators, and algorithms.
5. STL algorithms typically operate on `[first,last)` ranges.
6. The separation of storage, traversal, and algorithms is the foundation of STL design.
