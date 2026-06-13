# STL Iterators

## Overview

Iterators are one of the most important concepts in the Standard Template Library (STL).

The STL is built around three core components:

```text
Containers
Iterators
Algorithms
```

Containers store data.

Iterators provide access to data.

Algorithms operate on iterators.

This separation allows STL algorithms to work with many different container types without knowing how the container is implemented internally.

Example:

```cpp
std::find(first, last, value);
```

The algorithm works with:

```cpp
std::vector
std::list
std::deque
std::set
std::map
raw pointers
```

because it operates on iterators rather than containers.

---

# Learning Objectives

After completing this section, you should be able to:

* Explain the purpose of iterators in STL
* Understand iterator categories and capabilities
* Understand STL range semantics `[first,last)`
* Explain algorithm iterator requirements
* Understand iterator adapters
* Understand iterator_traits
* Understand tag dispatching
* Implement custom iterators
* Explain iterator-related interview questions confidently

---

# STL Design Philosophy

The STL separates:

```text
Storage
    ↓
Traversal
    ↓
Algorithms
```

or more concretely:

```text
Container
    ↓
Iterator
    ↓
Algorithm
```

This allows algorithms to remain independent from container implementations.

---

# Learning Roadmap

## Part 1: Fundamentals

* Iterator Fundamentals
* Iterator Categories

## Part 2: Iterator Categories

* Output Iterator
* Input Iterator
* Forward Iterator
* Bidirectional Iterator
* Random Access Iterator
* Contiguous Iterator (C++20)

## Part 3: Iterator Utility Functions

* std::advance()
* std::distance()
* std::next()
* std::prev()

## Part 4: Iterator Adapters

* reverse_iterator
* insert_iterator
* ostream_iterator
* istream_iterator
* move_iterator

## Part 5: STL Internals

* iterator_traits
* Iterator Tags
* Tag Dispatching
* Compile-Time Optimization

## Part 6: Implementation

* Building a Custom Iterator
* Making Custom Iterators Work with STL Algorithms

---

# Iterator Hierarchy

```text
                    Input Iterator      Output Iterator

                           Forward Iterator
                                   ↑
                         Bidirectional Iterator
                                   ↑
                        Random Access Iterator
                                   ↑
                        Contiguous Iterator (C++20)
```

Note:

Output Iterators form a separate category because they are write-oriented rather than read-oriented.

---

# Interview Focus

Common interview topics covered in this section:

* What is an iterator?
* Why STL uses iterators
* Input vs Output Iterator
* Why std::sort requires Random Access Iterators
* Why std::list cannot use std::sort
* Difference between vector and deque iterators
* Complexity of std::distance()
* Complexity of std::advance()
* iterator_traits
* Tag dispatching
* Reverse iterators
* Insert iterators

---

# References

Primary Reference:

* Nicolai M. Josuttis

  * The C++ Standard Library (Chapter 9)

Additional References:

* cppreference.com
* Effective STL
* libstdc++
* libc++
* MSVC STL

---

# Folder Structure

```text
iterators/

README.md

01_iterator_fundamentals.md
02_iterator_categories.md

03_output_iterator.md
04_input_iterator.md
05_forward_iterator.md
06_bidirectional_iterator.md
07_random_access_iterator.md
08_contiguous_iterator.md

09_distance_and_advance.md

10_reverse_iterator.md
11_insert_iterator.md
12_stream_iterator.md
13_move_iterator.md

14_iterator_traits.md
15_custom_iterator.md
```
