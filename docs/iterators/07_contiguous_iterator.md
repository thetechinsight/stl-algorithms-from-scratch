# Contiguous Iterator

## What is a Contiguous Iterator?

A Contiguous Iterator is a Random Access Iterator that guarantees elements are stored in contiguous memory.

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
Contiguous Iterator (C++20)
```

A Contiguous Iterator supports everything a Random Access Iterator supports and additionally guarantees memory layout.

---

# Motivation

Consider:

```cpp
std::vector<int> v{10,20,30,40,50};
```

Memory:

```text
+----+----+----+----+----+
| 10 | 20 | 30 | 40 | 50 |
+----+----+----+----+----+
```

All elements are adjacent.

The address of each element can be calculated directly.

Example:

```cpp
&v[1]
```

is exactly one integer after:

```cpp
&v[0]
```

in memory.

---

# Formal Guarantee

Given:

```cpp
auto it = v.begin();
```

The following must be true:

```cpp
&*(it + n)
```

is equivalent to:

```cpp
std::addressof(*it) + n
```

This means iterator movement directly corresponds to memory addresses.

---

# Why Random Access Is Not Enough

Consider:

```cpp
std::deque<int>
```

A deque provides:

```cpp
it + n
it - n
it[n]
```

So it is a Random Access Iterator.

However, its memory layout is usually:

```text
Block A:
1 2 3

Block B:
4 5 6

Block C:
7 8 9
```

Multiple blocks.

Not one continuous memory region.

Therefore:

```cpp
std::deque
```

provides:

```text
Random Access Iterator
```

but NOT:

```text
Contiguous Iterator
```

---

# Containers Providing Contiguous Iterators

Examples:

```cpp
std::vector
std::array
std::basic_string
```

Raw pointers:

```cpp
int*
char*
double*
```

are also Contiguous Iterators.

---

# Containers That Are Not Contiguous

Examples:

```cpp
std::list
std::set
std::map
std::deque
std::forward_list
```

These do not guarantee contiguous memory.

---

# Visual Comparison

Vector:

```text
+----+----+----+----+----+
| 10 | 20 | 30 | 40 | 50 |
+----+----+----+----+----+
```

Contiguous.

---

Deque:

```text
Block 1
+----+----+
| 10 | 20 |
+----+----+

Block 2
+----+----+
| 30 | 40 |
+----+----+

Block 3
+----+
| 50 |
+----+
```

Random Access but not contiguous.

---

# Why Contiguous Memory Matters

Suppose:

```cpp
for(auto x : v)
{
    sum += x;
}
```

CPU loads memory efficiently.

Adjacent elements often arrive in cache together.

This is called:

```text
Cache Locality
```

Contiguous memory significantly improves performance.

---

# STL Optimization Example

Suppose we want:

```cpp
std::copy(first, last, dest);
```

For generic iterators:

```cpp
while(first != last)
{
    *dest = *first;
    ++dest;
    ++first;
}
```

For contiguous iterators and trivially copyable types:

```cpp
memmove(...)
```

can be used.

This is one of the major STL optimizations.

---

# Why Vector Is Often Faster Than List

Many developers expect:

```cpp
std::list
```

to be faster because insertion is O(1).

In practice:

```cpp
std::vector
```

often wins.

Reason:

```text
Cache locality
```

Vector:

```text
10 20 30 40 50
```

stored together.

List:

```text
10 -> 20 -> 30 -> 40 -> 50
```

nodes scattered throughout memory.

The CPU prefers contiguous memory.

---

# Example

```cpp
std::vector<int> v{1,2,3,4,5};

auto p = v.data();
```

`data()` returns a pointer to the first element.

Because storage is contiguous.

---

This works:

```cpp
std::memcpy(
    buffer,
    v.data(),
    v.size() * sizeof(int));
```

because the memory is contiguous.

---

# C++20 Contiguous Iterator Concept

C++20 introduced:

```cpp
std::contiguous_iterator
```

This allows algorithms to recognize:

```text
Contiguous Storage
```

and apply specialized optimizations.

---

# Comparison Table

| Feature                           | Random Access | Contiguous |
| --------------------------------- | ------------- | ---------- |
| it + n                            | Yes           | Yes        |
| it[n]                             | Yes           | Yes        |
| O(1) distance                     | Yes           | Yes        |
| Adjacent memory guarantee         | No            | Yes        |
| Suitable for memcpy optimizations | Not always    | Yes        |

---

# Real STL Insight

A vector iterator is typically implemented as:

```cpp
T*
```

or a tiny wrapper around:

```cpp
T*
```

This is why vector iteration is extremely fast.

A deque iterator is much more complicated because it must track:

```text
Current Block
Current Position
Block Map
```

while still supporting Random Access operations.

---

# Interview Questions

## Q1

Is every Random Access Iterator a Contiguous Iterator?

Answer:

No.

Example:

```cpp
std::deque
```

provides Random Access Iterators but not Contiguous Iterators.

---

## Q2

Which standard containers provide Contiguous Iterators?

Answer:

```cpp
std::vector
std::array
std::basic_string
```

and raw pointers.

---

## Q3

Why is vector iteration usually faster than list iteration?

Answer:

Because vector elements are stored contiguously, improving cache locality.

---

## Q4

Why can STL implementations use memcpy or memmove optimizations?

Answer:

Because contiguous iterators guarantee predictable memory layout.

---

# Key Takeaways

1. Contiguous Iterator extends Random Access Iterator.
2. It guarantees contiguous memory layout.
3. std::vector provides Contiguous Iterators.
4. std::deque provides Random Access Iterators but not Contiguous Iterators.
5. Contiguous memory enables cache-friendly access patterns.
6. Modern STL implementations use this guarantee for optimizations.
