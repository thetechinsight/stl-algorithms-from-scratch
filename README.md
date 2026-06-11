# STL Algorithms From Scratch

A hands-on exploration of C++ STL internals through custom implementations of algorithms, iterator utilities, and generic programming techniques.

## Goals

This repository is my personal study project for understanding how C++ STL algorithms work internally.

The goal is to:

* Learn iterator categories and their requirements
* Understand generic programming with templates
* Reimplement common STL algorithms
* Explore algorithm complexity and design decisions
* Build intuition for how containers and algorithms interact
* Document key STL concepts for future reference

---

## Iterator Categories

| Category                    | Supported Operations              |
| --------------------------- | --------------------------------- |
| Input Iterator              | Read, increment                   |
| Output Iterator             | Write, increment                  |
| Forward Iterator            | Multi-pass traversal              |
| Bidirectional Iterator      | Forward and backward traversal    |
| Random Access Iterator      | Arithmetic and indexing           |
| Contiguous Iterator (C++20) | Random access + contiguous memory |

---

## Common Iterator Operations

| Operation    | Meaning                  |
| ------------ | ------------------------ |
| `*it`        | Dereference              |
| `++it`       | Move to next element     |
| `--it`       | Move to previous element |
| `it1 == it2` | Equality comparison      |
| `it1 != it2` | Inequality comparison    |
| `it + n`     | Jump forward             |
| `it - n`     | Jump backward            |
| `it[n]`      | Random access            |

---

## Learning Roadmap

### Phase 1 — Basic Algorithms

* [x] my_find
* [ ] my_find_if
* [x] my_count
* [ ] my_count_if
* [ ] my_for_each

### Phase 2 — Iterator Utilities

* [ ] my_distance
* [ ] my_advance
* [ ] my_next
* [ ] my_prev

### Phase 3 — Modification Algorithms

* [x] my_copy
* [ ] my_fill
* [ ] my_transform
* [ ] my_replace

### Phase 4 — Comparison Algorithms

* [ ] my_equal
* [ ] my_mismatch
* [ ] my_lexicographical_compare

### Phase 5 — Numeric Algorithms

* [ ] my_accumulate
* [ ] my_inner_product

### Phase 6 — Advanced Algorithms

* [ ] my_partition
* [ ] my_reverse
* [ ] my_rotate
* [ ] my_sort

---

## Project Structure

```text
stl-algorithms-from-scratch/
│
├── README.md
│
├── docs/
│   ├── algorithm_requirements.md
│   ├── iterator_categories.md
│   ├── my_count.md
│   ├── my_find.md
│   ├── notes.md
│   └── iterators/
│       ├── README.md
│       ├── 01_introduction.md
│       ├── 02_iterator_categories.md
│       ├── 03_input_iterator.md
│       ├── 04_forward_iterator.md
│       ├── 05_bidirectional_iterator.md
│       ├── 06_random_access_iterator.md
│       ├── 07_contiguous_iterator.md
│       ├── 08_iterator_traits.md
│       ├── 09_distance_and_advance.md
│       └── 10_custom_iterator.md
│
├── include/
│   ├── my_copy.hpp
│   ├── my_count.hpp
│   └── my_find.hpp
│
├── examples/
│   ├── algorithms/
│   │   ├── count_example.cpp
│   │   └── find_example.cpp
│   └── iterators/
│       ├── bidirectional_iterator_demo.cpp
│       ├── contiguous_iterator_demo.cpp
│       ├── forward_iterator_demo.cpp
│       ├── input_iterator_demo.cpp
│       ├── iterator_traits_demo.cpp
│       └── random_access_iterator_demo.cpp
│
└── tests/
    └── test_find.cpp
```

---

## Example: my_find

**Requirements**

* Dereference (`*it`)
* Increment (`++it`)
* Comparison (`!=`)

**Iterator Category**

* Input Iterator or stronger

**Complexity**

* O(n)

```cpp
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
```

---

## References

### Books

* Effective STL — Scott Meyers
* The C++ Standard Library — Nicolai Josuttis

### Online Resources

* https://en.cppreference.com/w/cpp/algorithm
* https://en.cppreference.com/w/cpp/iterator

### Source Code

* libc++ (LLVM)
* libstdc++ (GCC)

---

## Progress

This repository is actively maintained as part of my C++ learning journey.

Each algorithm will include:

* Source code
* Iterator requirements
* Complexity analysis
* Usage examples
* Notes and observations

Contributions, suggestions, and discussions are welcome.
