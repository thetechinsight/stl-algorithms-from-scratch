# Input Iterator

## What is an Input Iterator?

An Input Iterator is the most basic iterator used for reading elements from a sequence.

It allows:

```cpp
*it      // read current element
++it     // move to next element
it != end
```

An Input Iterator can move only forward.

It is primarily intended for reading data.

---

# Mental Model

Think of reading a file:

```text
10
20
30
40
50
```

You read:

```text
10 -> 20 -> 30 -> 40 -> 50
```

Once you move forward, you do not go backward.

This is the intuition behind an Input Iterator.

---

# Supported Operations

Given:

```cpp
InputIterator it;
```

The following operations are valid:

```cpp
*it
++it
it++
it == other
it != other
```

The following are NOT required:

```cpp
--it
it + 5
it - 5
it[5]
```

---

# Why Is It Called "Input"?

Historically, Input Iterators were designed to represent input streams.

Example:

```cpp
std::istream_iterator<int>
```

which reads values from:

```cpp
std::cin
std::ifstream
```

Example:

```cpp
std::istream_iterator<int> first(std::cin);
std::istream_iterator<int> last;

while(first != last)
{
    std::cout << *first << '\n';
    ++first;
}
```

The iterator reads values from the stream as it advances.

---

# Single-Pass Nature

This is the most important property.

Input Iterators are considered:

```text
Single-pass iterators
```

Meaning:

Once you advance, previous positions may no longer be usable.

Example:

```cpp
auto a = it;
++it;
```

For a pure Input Iterator:

```cpp
a
```

may no longer represent an independent traversal position.

This is different from Forward Iterators.

---

# Why Single-Pass Matters

Imagine reading:

```text
10 20 30 40
```

from a file.

When you consume:

```text
10
```

the stream moves forward.

You cannot magically go back.

Input Iterators model this behavior.

---

# Real STL Example

```cpp
std::istream_iterator<int>
```

Example:

```cpp
#include <iterator>
#include <iostream>

int main()
{
    std::istream_iterator<int> first(std::cin);
    std::istream_iterator<int> last;

    while(first != last)
    {
        std::cout << *first << '\n';
        ++first;
    }
}
```

Input:

```text
1 2 3 4
```

Output:

```text
1
2
3
4
```

---

# Algorithms That Require Only Input Iterators

Many algorithms need nothing more than:

```cpp
*it
++it
!=
```

Examples:

```cpp
std::find
std::count
std::count_if
std::all_of
std::any_of
std::none_of
```

These algorithms simply walk through a range.

---

# Example: my_find

```cpp
template<typename InputIt, typename T>
InputIt my_find(InputIt first,
                InputIt last,
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

Required operations:

```cpp
*first
++first
first != last
```

Nothing more.

Therefore Input Iterator is sufficient.

---

# Why STL Uses Minimum Requirements

Suppose std::find required Random Access Iterators.

Then it could not work with:

```cpp
std::list
std::set
std::istream_iterator
```

By requiring only Input Iterator operations, STL makes the algorithm usable with many more types.

This is a fundamental STL design principle.

---

# Input Iterator vs Pointer

Pointers satisfy all Input Iterator requirements.

Example:

```cpp
int arr[] = {1,2,3,4,5};

int* first = arr;
int* last  = arr + 5;
```

The following works:

```cpp
my_find(first, last, 3);
```

This demonstrates that raw pointers are also iterators.

---

# Interview Questions

## Q1

What is the minimum iterator category required by std::find?

Answer:

Input Iterator.

---

## Q2

Why does std::find work on std::list?

Answer:

Because std::find only needs:

```cpp
*it
++it
!=
```

which a list iterator provides.

---

## Q3

Can an Input Iterator move backward?

Answer:

No.

Input Iterators support forward traversal only.

---

# Key Takeaways

1. Input Iterator is the most basic readable iterator.
2. It supports reading and moving forward.
3. It is generally considered a single-pass iterator.
4. Many STL algorithms require only Input Iterators.
5. STL algorithms are designed around minimum iterator requirements.


## Question
If my_find() only uses *, ++, and !=, why would it ever require a Random Access Iterator?

Answer:

It doesn't. Requiring a stronger iterator category would unnecessarily restrict where the algorithm can be used.