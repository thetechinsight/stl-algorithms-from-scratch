# Iterator Categories

## Why Iterator Categories Exist

Not all containers support the same operations efficiently.

For example:

```cpp
std::vector<int>
```

supports:

```cpp
it + 10
it - 10
it[5]
```

in constant time.

But:

```cpp
std::list<int>
```

cannot efficiently jump 10 positions forward because it is implemented as a linked list.

Because of these differences, STL classifies iterators into categories based on their capabilities.

Algorithms specify the minimum iterator category they require.

---

# Iterator Hierarchy

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

Each category inherits the capabilities of the previous category.

For example:

```text
Random Access Iterator
=
Bidirectional Iterator
+
Random Access Operations
```

---

# Category 1: Input Iterator

Purpose:

Read elements while moving forward.

*Once you read a value, you typically move forward and don't revisit it.*

Supported Operations:

```cpp
*it
++it
it == other
it != other
```
Example:

```cpp
std::istream_iterator<int>
```

Algorithms That Need Only Input Iterators:

```cpp
find
count
count_if
all_of
any_of
none_of
```

Because they only need:

```cpp
*it
++it
```

# Category 2: Forward Iterator

Purpose:

Read or write elements while moving forward.

Adds:

```text
Multi-pass traversal
Meaning you can traverse the same range multiple times safely.
```

Example:

```cpp
std::forward_list<int>
```

Supports:

```cpp
*it
++it
==
!=
```

But no:

```cpp
--it
it + n
```

Mental Model:

```text
1 -> 2 -> 3 -> 4
```

Still forward-only.

But traversal can be repeated.

---

# Category 3: Bidirectional Iterator

Purpose:

Move in both directions.

Adds:

```cpp
--it
```

Now movement is possible in both directions.

Examples:

```cpp
std::list
std::set
std::map
std::multiset
std::multimap
```
## Algorithms Requiring Bidirectional

Example:
```cpp
std::reverse
```

Why?

Because reverse needs:

```cpp
++first
--last
```
from both ends.


Mental Model:

```text
1 <-> 2 <-> 3 <-> 4
```

You can move forward and backward.

---

# Category 4: Random Access Iterator

Purpose:

Jump directly to any position.

Adds:

```cpp
it + n
it - n
it += n
it -= n
it[n]
it1 < it2
it1 > it2

```
and all of those are constant time.


Examples:

```cpp
std::vector
std::deque
std::array
T*
```

## Why sort Requires Random Access

Consider:
```cpp
middle = first + (last - first)/2;
```

This operation must be fast.

Therefore:

```cpp
std::sort
```

requires Random Access Iterators

Mental Model:

```text
Index-based access
```


# Category 5: Contiguous Iterator (C++20)

Purpose:

Guarantee that elements are stored contiguously in memory.
Meaning Elements are physically adjacent in memory

Examples:

```cpp
int*
std::vector<int>::iterator
std::array<int>::iterator

not
- std::deque (because deque storage is segmented)
```

Guarantee:

```cpp
&*(it + n)
==
std::addressof(*it) + n
```

This allows implementations to use low-level memory optimizations.

---

# Iterator Categories and Containers

| Container    | Iterator Category          |
| ------------ | -------------------------- |
| forward_list | Forward                    |
| list         | Bidirectional              |
| set          | Bidirectional              |
| map          | Bidirectional              |
| vector       | Random Access + Contiguous |
| array        | Random Access + Contiguous |
| deque        | Random Access              |
| raw pointer  | Contiguous                 |

---

# Algorithm Requirements

| Algorithm | Minimum Requirement    |
| --------- | ---------------------- |
| find      | Input Iterator         |
| count     | Input Iterator         |
| copy      | Input Iterator         |
| reverse   | Bidirectional Iterator |
| sort      | Random Access Iterator |

Algorithms are written against the minimum capability required.

This is one of the core design principles of STL.

---

# Important Interview Question

Why does:

```cpp
std::sort(v.begin(), v.end());
```

work?

but:

```cpp
std::sort(lst.begin(), lst.end());
```

fail?

Answer:

`std::sort` requires Random Access Iterators.

`std::vector` provides Random Access Iterators.

`std::list` provides only Bidirectional Iterators.

Therefore `std::sort` cannot operate on `std::list`.

Instead:

```cpp
lst.sort();
```

must be used.

---

# Key Takeaways

1. Iterators are categorized by capability.
2. Categories form a hierarchy.
3. More powerful categories support more operations.
4. Algorithms specify the minimum iterator category required.
5. Containers expose iterators.
6. Algorithms operate on iterators, not containers.
