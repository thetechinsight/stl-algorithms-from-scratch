# Contiguous Iterator

## Learning Objectives

After completing this chapter, you should be able to:

* Explain what a Contiguous Iterator is
* Understand how Contiguous Iterators extend Random Access Iterators
* Understand the contiguous memory guarantee
* Explain the difference between Random Access and Contiguous Iterators
* Identify containers that provide Contiguous Iterators
* Understand why contiguous storage is important for performance
* Answer common Contiguous Iterator interview questions

---

# What is a Contiguous Iterator?

A Contiguous Iterator is a Random Access Iterator whose elements are stored contiguously in memory.

Hierarchy:

```text
Input Iterator
      ↑
Forward Iterator
      ↑
Bidirectional Iterator
      ↑
Random Access Iterator
      ↑
Contiguous Iterator
```

A Contiguous Iterator supports all Random Access Iterator operations and adds a stronger memory-layout guarantee.

The defining feature is:

```text
Elements occupy contiguous memory locations.
```

---

# Why Was a New Category Needed?

Before C++20:

```cpp
std::vector<int>::iterator
```

and

```cpp
std::deque<int>::iterator
```

were both Random Access Iterators.

Both support:

```cpp
it + n
it - n
it[n]
```

However:

```cpp
std::vector
```

stores elements contiguously.

```cpp
std::deque
```

does not.

The iterator category could not express this difference.

C++20 introduced Contiguous Iterators to solve this problem.

---

# Contiguous Memory

Consider:

```cpp
std::vector<int> v{10,20,30,40};
```

Memory layout:

```text
+----+----+----+----+
| 10 | 20 | 30 | 40 |
+----+----+----+----+
```

Elements are stored one after another with no gaps.

Therefore:

```cpp
&v[0]
```

points to the beginning of a contiguous block of memory.

---

# The Contiguous Iterator Guarantee

For a Contiguous Iterator:

```cpp
*(iter + n)
```

refers to the same element as:

```cpp
*(std::to_address(iter) + n)
```

Conceptually:

```text
Iterator arithmetic
      ==
Pointer arithmetic
```

This stronger guarantee is what distinguishes Contiguous Iterators from ordinary Random Access Iterators.

---

# Example: vector

```cpp
#include <vector>
#include <iostream>

int main()
{
    std::vector<int> v{10,20,30,40};

    auto it = v.begin();

    std::cout << *(it + 2) << '\n';
    std::cout << *(v.data() + 2) << '\n';
}
```

Output:

```text
30
30
```

Both expressions refer to the same element.

---

# Why std::deque Is Not Contiguous

Consider:

```cpp
std::deque<int>
```

A deque is typically implemented as multiple memory blocks.

Conceptually:

```text
+----+----+----+

+----+----+----+

+----+----+
```

The blocks may be scattered throughout memory.

Although:

```cpp
it + n
```

is still supported in O(1),

there is no guarantee that all elements occupy a single contiguous memory region.

Therefore:

```cpp
std::deque::iterator
```

is a Random Access Iterator but not a Contiguous Iterator.

---

# Providers of Contiguous Iterators

Common containers providing Contiguous Iterators:

```cpp
std::array
std::vector
std::basic_string
```

Raw pointers:

```cpp
int*
double*
char*
```

are also Contiguous Iterators.

---

# Why Contiguous Storage Matters

Contiguous memory improves:

### Cache Locality

```text
CPU cache efficiency
```

### Memory Bandwidth

```text
Sequential memory access
```

### Interoperability

```text
C APIs
System APIs
Hardware APIs
```

Many low-level APIs require a pointer to a contiguous memory block.

---

# Interoperability Example

```cpp
std::vector<int> v{1,2,3,4};

some_c_api(
    v.data(),
    v.size());
```

This works because:

```cpp
v.data()
```

returns a pointer to a contiguous block of memory.

---

# Random Access vs Contiguous Iterator

| Feature                        | Random Access Iterator | Contiguous Iterator |
| ------------------------------ | ---------------------- | ------------------- |
| `iter + n`                     | Yes                    | Yes                 |
| `iter[n]`                      | Yes                    | Yes                 |
| O(1) Distance                  | Yes                    | Yes                 |
| Ordering Comparisons           | Yes                    | Yes                 |
| Contiguous Memory Guarantee    | No                     | Yes                 |
| Pointer Arithmetic Equivalence | No                     | Yes                 |

---

# Contiguous Iterator vs Raw Pointer

A raw pointer:

```cpp
int*
```

is the canonical Contiguous Iterator.

Modern STL containers attempt to provide iterator behavior that is as efficient as pointer manipulation.

---

# Real STL Insight

Many developers assume:

```cpp
std::deque
```

must be contiguous because:

```cpp
deque[i]
```

is O(1).

This is incorrect.

Random access and contiguous storage are different concepts.

A container may provide:

```text
O(1) random access
```

without storing all elements contiguously.

`std::deque` is the classic example.

---

# Interview Trap

## Question

If `std::vector` and `std::deque` both provide Random Access Iterators, why was Contiguous Iterator introduced?

### Answer

Because Random Access Iterators describe supported operations.

They do not describe memory layout.

Contiguous Iterators add the guarantee that elements occupy contiguous memory locations.

---

## Question

Is `std::deque::iterator` a Contiguous Iterator?

### Answer

No.

It is a Random Access Iterator.

A deque does not provide contiguous storage.

---

## Question

What is the canonical Contiguous Iterator?

### Answer

A raw pointer.

Example:

```cpp
int*
```

---

# Interview Questions

## Q1

What additional guarantee does a Contiguous Iterator provide?

**Answer:**

Elements are stored contiguously in memory.

---

## Q2

Which standard containers provide Contiguous Iterators?

**Answer:**

```cpp
std::array
std::vector
std::basic_string
```

and raw pointers.

---

## Q3

Does `std::deque` provide Contiguous Iterators?

**Answer:**

No.

It provides Random Access Iterators.

---

## Q4

Why is contiguous storage important?

**Answer:**

Because it improves cache efficiency and allows direct interoperability with APIs requiring raw memory buffers.

---

## Q5

What is the key difference between Random Access and Contiguous Iterators?

**Answer:**

Contiguous Iterators provide a memory-layout guarantee in addition to Random Access operations.

---

# Interview Summary

## Must Remember

* Contiguous Iterator extends Random Access Iterator.
* The defining feature is contiguous memory storage.
* Supports all Random Access operations.
* Raw pointers are Contiguous Iterators.
* Containers:

  * `std::vector`
  * `std::array`
  * `std::basic_string`
* `std::deque` is **not** contiguous.
* Contiguous storage improves cache performance and API interoperability.

---

# Key Takeaways

1. A Contiguous Iterator is a Random Access Iterator with a contiguous memory guarantee.
2. C++20 introduced Contiguous Iterators.
3. `std::vector`, `std::array`, and `std::basic_string` provide Contiguous Iterators.
4. Raw pointers are Contiguous Iterators.
5. Random Access does not imply contiguous storage.
6. `std::deque` is Random Access but not Contiguous.
7. Contiguous storage is important for performance and interoperability.
