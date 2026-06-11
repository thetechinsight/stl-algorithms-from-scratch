# STL Algorithms From Scratch

A repository for understanding how C++ STL algorithms work internally by implementing them using iterators.

## Goals

* Learn iterator categories
* Understand algorithm requirements
* Reimplement common STL algorithms
* Explore template programming
* Study how generic programming works in C++

---

## Iterator Requirements Cheat Sheet

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

### Iterator Categories

| Category               | Supported Operations           |
| ---------------------- | ------------------------------ |
| Input Iterator         | Read, increment                |
| Output Iterator        | Write, increment               |
| Forward Iterator       | Multi-pass traversal           |
| Bidirectional Iterator | Forward and backward traversal |
| Random Access Iterator | Arithmetic and indexing        |

---

## Algorithms Implemented

### Searching

* [ ] my_find
* [ ] my_find_if
* [ ] my_count
* [ ] my_count_if

### Traversal

* [ ] my_for_each

### Modification

* [ ] my_copy
* [ ] my_fill
* [ ] my_transform

### Comparison

* [ ] my_equal
* [ ] my_mismatch

### Numeric

* [ ] my_accumulate

### Iterator Utilities

* [ ] my_distance
* [ ] my_advance
* [ ] my_next
* [ ] my_prev

### Sorting

* [ ] my_partition
* [ ] my_sort

---

## Example: my_find

Requirements:

* Dereference (`*it`)
* Increment (`++it`)
* Comparison (`!=`)

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

Works with:

* std::vector
* std::list
* std::forward_list
* std::set
* std::map

---

## References

* cppreference.com
* Effective STL (Scott Meyers)
* The C++ Standard Library (Nicolai Josuttis)
* libc++ source code
* libstdc++ source code
