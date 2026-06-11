# Bidirectional Iterator

## What is a Bidirectional Iterator?

A Bidirectional Iterator is a Forward Iterator that can move both forward and backward.

Hierarchy:

```text
Input Iterator
      ↑
Forward Iterator
      ↑
Bidirectional Iterator
```

A Bidirectional Iterator supports everything a Forward Iterator supports and adds:

```cpp
--it
it--
```

---

# Why Do We Need Bidirectional Iterators?

Consider a singly linked list:

```text
1 -> 2 -> 3 -> 4 -> 5
```

You can move:

```cpp
++it
```

But you cannot move backward because nodes only know their next node.

Now consider a doubly linked list:

```text
1 <-> 2 <-> 3 <-> 4 <-> 5
```

Each node stores:

```cpp
prev
next
```

Now both directions are possible.

```cpp
++it
--it
```

This is the fundamental idea behind Bidirectional Iterators.

---

# Supported Operations

Given:

```cpp
BidirectionalIterator it;
```

Supported:

```cpp
*it

++it
it++

--it
it--

it == other
it != other
```

Not supported:

```cpp
it + 5
it - 5
it[3]
```

These require Random Access Iterators.

---

# Visual Model

Forward Iterator:

```text
1 -> 2 -> 3 -> 4
```

Bidirectional Iterator:

```text
1 <-> 2 <-> 3 <-> 4
```

You can travel in both directions.

---

# Standard Containers

Examples:

```cpp
std::list
std::set
std::map
std::multiset
std::multimap
```

All provide Bidirectional Iterators.

---

# Example with std::list

```cpp
#include <list>
#include <iostream>

int main()
{
    std::list<int> lst{10,20,30,40};

    auto it = lst.begin();

    ++it;
    ++it;

    std::cout << *it << '\n';
}
```

Output:

```text
30
```

Move backward:

```cpp
--it;
```

Now:

```text
20
```

---

# Why std::set Supports --it

Internally:

```cpp
std::set
```

is typically implemented as a Red-Black Tree.

Each tree node stores:

```cpp
parent
left
right
```

This allows traversal in sorted order.

Example:

```cpp
std::set<int> s{10,20,30,40};

auto it = s.end();

--it;

std::cout << *it;
```

Output:

```text
40
```

Even though a tree is not an array, the iterator can move backward because the tree structure provides enough information.

---

# Why Reverse Traversal Matters

Suppose:

```cpp
std::list<int> lst{1,2,3,4,5};
```

We want:

```text
5 4 3 2 1
```

Possible because:

```cpp
--it
```

exists.

Without backward movement, reverse traversal becomes difficult or impossible.

---

# Algorithm Example: reverse()

A simplified reverse algorithm:

```cpp
while(first != last &&
      first != --last)
{
    std::iter_swap(first, last);
    ++first;
}
```

Notice:

```cpp
--last
```

This immediately tells us:

```text
reverse()
requires Bidirectional Iterator
```

---

# Why Not Random Access?

Suppose:

```cpp
std::list<int>
```

supports:

```cpp
it + 100
```

To perform that operation, the implementation would need to walk through 100 nodes.

Complexity:

```text
O(n)
```

But STL expects:

```cpp
it + n
```

to be:

```text
O(1)
```

Therefore Bidirectional Iterators do not provide:

```cpp
it + n
```

---

# Complexity Comparison

Moving one step:

```cpp
++it
--it
```

Complexity:

```text
O(1)
```

Moving 100 steps:

```cpp
for(int i = 0; i < 100; ++i)
{
    ++it;
}
```

Complexity:

```text
O(100)
```

Linear.

---

# Comparison with Forward Iterator

| Feature           | Forward | Bidirectional |
| ----------------- | ------- | ------------- |
| Read              | Yes     | Yes           |
| Multi-pass        | Yes     | Yes           |
| ++it              | Yes     | Yes           |
| --it              | No      | Yes           |
| Forward traversal | Yes     | Yes           |
| Reverse traversal | No      | Yes           |

---

# Real STL Insight

Many people assume:

```cpp
std::list
```

must be faster than:

```cpp
std::vector
```

because insertion is O(1).

In reality:

```text
vector
```

often wins due to cache locality.

Understanding iterator categories helps explain why.

List iterators move through scattered nodes.

Vector iterators move through contiguous memory.

---

# Interview Questions

## Q1

What capability does a Bidirectional Iterator add?

Answer:

```cpp
--it
```

Backward traversal.

---

## Q2

Which STL containers provide Bidirectional Iterators?

Answer:

```cpp
std::list
std::set
std::map
```

and their multi variants.

---

## Q3

Why does std::reverse require Bidirectional Iterators?

Answer:

Because it needs:

```cpp
--last
```

to move from the end toward the beginning.

---

## Q4

Can a Bidirectional Iterator perform:

```cpp
it + 10
```

?

Answer:

No.

That requires Random Access Iterators.

---

# Key Takeaways

1. Bidirectional Iterator extends Forward Iterator.
2. It supports both forward and backward movement.
3. It provides:

   ```cpp
   ++it
   --it
   ```
4. std::list, std::set and std::map use Bidirectional Iterators.
5. Bidirectional does not imply Random Access.
6. Algorithms like reverse() depend on Bidirectional Iterators.
