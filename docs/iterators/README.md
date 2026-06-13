# STL Iterators

## Overview

Iterators are one of the fundamental building blocks of the Standard Template Library (STL).

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

After completing this module, you should be able to:

* Explain the purpose of iterators in STL
* Understand iterator categories and capabilities
* Understand STL range semantics `[first, last)`
* Explain algorithm iterator requirements
* Understand iterator utility functions
* Understand iterator adapters
* Understand iterator traits
* Explain common iterator-related interview questions
* Understand how STL algorithms depend on iterator categories

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
* Iterator Categories Overview

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

* Reverse Iterators
* Insert Iterators
* Stream Iterators
* Move Iterators

## Part 5: STL Internals

* iterator_traits
* Iterator Categories and Algorithm Selection
* How STL Algorithms Use Iterators

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

Output Iterators form a separate hierarchy because they are write-oriented rather than read-oriented.

---

# Module Contents

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

09_auxiliary_iterator_functions.md

10_iterator_adapters.md
11_reverse_iterators.md
12_insert_iterators.md
13_stream_iterators.md
14_move_iterators.md

15_iterator_traits.md
```

---

# Example Programs

```text
examples/iterators/

input_iterator_demo.cpp
forward_iterator_demo.cpp
bidirectional_iterator_demo.cpp
random_access_iterator_demo.cpp
contiguous_iterator_demo.cpp

reverse_iterator_demo.cpp
insert_iterator_demo.cpp
stream_iterator_demo.cpp
move_iterator_demo.cpp

iterator_traits_demo.cpp
```

---

# Interview Focus

Common interview topics covered in this module:

* What is an iterator?
* Why STL uses iterators
* Input Iterator vs Output Iterator
* Forward Iterator vs Input Iterator
* Bidirectional Iterator vs Random Access Iterator
* Why std::sort requires Random Access Iterators
* Why std::list cannot be used with std::sort
* Complexity of std::advance()
* Complexity of std::distance()
* Reverse Iterators
* Insert Iterators
* Stream Iterators
* Move Iterators
* iterator_traits
* Iterator category based optimization

---

# Current Status

```text
Iterator Fundamentals        ✅
Iterator Categories          ✅
Iterator Utility Functions   ✅
Iterator Adapters            ✅
Iterator Traits              ✅
```

This module provides the iterator knowledge required to understand and implement STL algorithms.

Next Module:

```text
Algorithms
```

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
