# Iterator Traits

## Learning Objectives

After completing this chapter, you should be able to:

- Explain what `std::iterator_traits` is
- Understand why iterator traits exist
- Understand the five classic iterator traits
- Understand how STL algorithms use iterator traits
- Understand the traits programming technique
- Understand iterator category dispatching
- Understand special handling for raw pointers
- Understand the relationship between iterator traits and modern iterator concepts
- Answer common STL interview questions

---

# Motivation

Consider:

```cpp
std::advance(it, 10);
```

Question:

How does `std::advance()` know whether:

```cpp
it
```

is:

```text
std::vector<int>::iterator
std::list<int>::iterator
int*
std::deque<int>::iterator
```

?

For example:

```cpp
it += 10;
```

is efficient for:

```text
Random Access Iterator
```

but impossible for:

```text
Input Iterator
```

and unavailable for:

```text
Bidirectional Iterator
```

The STL needs a way to discover iterator properties at compile time.

The solution is:

```cpp
std::iterator_traits
```

---

# What Are Iterator Traits?

Iterator traits are compile-time metadata associated with an iterator type.

Think of them as:

```text
Iterator
    ↓
Iterator Traits
    ↓
Metadata
    ↓
Algorithm
```

An algorithm can query:

```cpp
std::iterator_traits<Iterator>
```

to discover information about the iterator.

---

# Why Traits Are Needed

Algorithms are written in terms of iterator types:

```cpp
template<typename Iterator>
void algorithm(
    Iterator first,
    Iterator last);
```

The algorithm does not know whether:

```cpp
Iterator
```

is:

```cpp
std::vector<int>::iterator
std::list<int>::iterator
int*
```

or some user-defined iterator.

Nevertheless, the algorithm often needs information such as:

```text
Element type
Distance type
Iterator category
```

Iterator traits provide this information at compile time.

---

# Traits and Generic Programming

Iterator traits are an example of the STL traits programming technique.

The general idea is:

```text
Type
   ↓
Traits Class
   ↓
Compile-Time Information
```

Instead of modifying a type, a separate traits class provides information about that type.

Iterator traits are among the most important and widely used traits classes in the STL.

---

# The Five Classic Iterator Traits

Classic STL iterators expose five associated types through:

```cpp
std::iterator_traits<Iterator>
```

```cpp
value_type
difference_type
pointer
reference
iterator_category
```

These traits describe the iterator and the elements it accesses.

---

# Accessing Iterator Traits

Iterator traits are accessed through:

```cpp
std::iterator_traits<Iterator>
```

Example:

```cpp
using Value =
    typename
    std::iterator_traits<
        Iterator
    >::value_type;
```

The algorithm can obtain information about the iterator without knowing its exact type.

---

# value_type

Represents:

```text
Type of element
```

Example:

```cpp
std::vector<int>::iterator
```

provides:

```cpp
value_type = int
```

---

# difference_type

Represents:

```text
Distance between iterators
```

Typically:

```cpp
std::ptrdiff_t
```

Used by:

```cpp
std::distance()
```

and:

```cpp
std::advance()
```

---

# pointer

Represents:

```text
Pointer to element
```

Example:

```cpp
int*
```

---

# reference

Represents:

```text
Reference to element
```

Example:

```cpp
int&
```

---

# iterator_category

The most important classic trait.

Represents:

```text
Iterator capability
```

Possible values:

```cpp
std::input_iterator_tag
std::output_iterator_tag
std::forward_iterator_tag
std::bidirectional_iterator_tag
std::random_access_iterator_tag
```

Algorithms use this trait to determine which operations are available.

---

# Using iterator_traits

Example:

```cpp
using Iter =
    std::vector<int>::iterator;

using Value =
    std::iterator_traits<
        Iter
    >::value_type;
```

Result:

```cpp
Value == int
```

Similarly:

```cpp
using Category =
    std::iterator_traits<
        Iter
    >::iterator_category;
```

Result:

```cpp
std::random_access_iterator_tag
```

---

# Why STL Needs Iterator Traits

Consider:

```cpp
std::distance(first, last);
```

For a list:

```cpp
++it;
++it;
++it;
```

must be used.

Complexity:

```text
O(n)
```

For a vector:

```cpp
last - first
```

is available.

Complexity:

```text
O(1)
```

The STL chooses the correct implementation using:

```cpp
iterator_category
```

obtained through iterator traits.

---

# Category Dispatching

One of the most important STL implementation techniques is:

```text
Category Dispatching
```

The algorithm selects an implementation based on the iterator category.

Conceptually:

```cpp
advance_impl(
    it,
    n,
    iterator_category);
```

Different overloads exist for different iterator categories.

---

# Simplified Example

```cpp
template<typename Iterator>
void my_advance(
    Iterator& it,
    int n)
{
    my_advance_impl(
        it,
        n,
        typename
        std::iterator_traits<
            Iterator
        >::iterator_category{});
}
```

The category object determines which implementation is selected.

---

# Random Access Version

```cpp
template<typename Iterator>
void my_advance_impl(
    Iterator& it,
    int n,
    std::random_access_iterator_tag)
{
    it += n;
}
```

Complexity:

```text
O(1)
```

---

# Bidirectional Version

```cpp
template<typename Iterator>
void my_advance_impl(
    Iterator& it,
    int n,
    std::bidirectional_iterator_tag)
{
    if (n >= 0)
    {
        while (n--)
        {
            ++it;
        }
    }
    else
    {
        while (n++)
        {
            --it;
        }
    }
}
```

---

# Input Iterator Version

```cpp
template<typename Iterator>
void my_advance_impl(
    Iterator& it,
    int n,
    std::input_iterator_tag)
{
    while (n--)
    {
        ++it;
    }
}
```

Complexity:

```text
O(n)
```

Input Iterators can only move forward.

---

# Raw Pointer Specialization

Raw pointers are valid iterators.

Example:

```cpp
int*
```

However, pointers do not contain nested typedefs such as:

```cpp
value_type
iterator_category
```

Therefore the STL provides specializations of:

```cpp
std::iterator_traits<T*>
```

and:

```cpp
std::iterator_traits<const T*>
```

---

# Example

Conceptually:

```cpp
template<typename T>
struct iterator_traits<T*>
{
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    using iterator_category =
        std::random_access_iterator_tag;
};
```

This allows pointers to behave exactly like STL iterators.

---

# Why Raw Pointers Work With Algorithms

Because of the pointer specialization:

```cpp
int arr[5];

std::sort(
    arr,
    arr + 5);
```

works naturally.

The algorithm sees:

```cpp
int*
```

as a Random Access Iterator.

---

# Real STL Insight

Most STL algorithms do not care about:

```cpp
std::vector
std::list
std::deque
```

They care about:

```text
Iterator Capabilities
```

Those capabilities are communicated through:

```cpp
std::iterator_traits
```

This is one of the most important ideas in STL design.

Algorithms are selected based on iterator capabilities rather than container types.

---

# Modern C++

Since C++20, iterator concepts provide a richer mechanism for expressing iterator requirements.

Examples:

```cpp
std::input_iterator
std::forward_iterator
std::random_access_iterator
```

However:

```cpp
std::iterator_traits
```

remains an important and widely used component of the standard library.

Many existing algorithms and iterator implementations still rely on iterator traits.

---

# Interview Trap

## Question

Why does:

```cpp
std::advance()
```

run faster on a vector than on a list?

### Answer

Because iterator traits identify vector iterators as Random Access Iterators.

The implementation can use:

```cpp
it += n;
```

instead of repeated increments.

---

## Question

Why do raw pointers work with STL algorithms?

### Answer

Because the STL provides specializations of:

```cpp
std::iterator_traits<T*>
```

for pointer types.

---

## Question

Why does STL use traits instead of checking container types?

### Answer

Because algorithms operate on iterators, not containers.

Iterator traits describe iterator capabilities independently of the container.

---

# Interview Questions

## Q1

What is `std::iterator_traits`?

**Answer:**

A traits class that provides compile-time information about an iterator.

---

## Q2

What is the most important iterator trait?

**Answer:**

```cpp
iterator_category
```

because it describes iterator capabilities.

---

## Q3

Which trait represents the element type?

**Answer:**

```cpp
value_type
```

---

## Q4

Why does STL use iterator traits?

**Answer:**

To obtain information about iterators and select optimal implementations at compile time.

---

## Q5

Do raw pointers have iterator traits?

**Answer:**

Yes.

The STL provides specializations for pointer types.

---

## Q6

What STL technique is demonstrated by iterator traits?

**Answer:**

Traits programming.

Compile-time information is associated with a type through a separate traits class.

---

# Key Takeaways

1. `std::iterator_traits` provides compile-time metadata about iterators.
2. Iterator traits are an example of the STL traits programming technique.
3. The five classic traits are:
   - `value_type`
   - `difference_type`
   - `pointer`
   - `reference`
   - `iterator_category`
4. STL algorithms use traits to discover iterator capabilities.
5. `iterator_category` enables category dispatching.
6. Algorithms are optimized based on iterator categories.
7. Raw pointers are valid iterators because iterator traits are specialized for pointer types.
8. Iterator traits help algorithms work independently of concrete iterator types.
9. Modern C++ introduces iterator concepts, but iterator traits remain important.
10. Iterator traits are one of the foundational techniques behind the STL.