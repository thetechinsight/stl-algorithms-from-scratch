# Forward Iterator

## What is a Forward Iterator?

A Forward Iterator is an iterator that can:

1. Read elements
2. Move forward
3. Traverse the same range multiple times

It extends the capabilities of an Input Iterator.

Hierarchy:

```text
Input Iterator
      ↑
Forward Iterator
```

Everything an Input Iterator can do, a Forward Iterator can do.

Additionally, a Forward Iterator provides the multi-pass guarantee.

---

# Supported Operations

Given:

```cpp
ForwardIterator it;
```

The following operations are valid:

```cpp
*it
++it
it++
it == other
it != other
```

Just like Input Iterators.

---

# What Makes It Different?

The major difference is:

```text
Multi-Pass Guarantee
```

Copies of a Forward Iterator remain independently usable.

Example:

```cpp
auto a = it;
auto b = it;

++a;
```

After advancing:

```cpp
a
```

and

```cpp
b
```

still refer to valid positions in the range.

This behavior is guaranteed.

---

# Why Input Iterators Cannot Guarantee This

Consider:

```cpp
std::istream_iterator<int>
```

Reading:

```text
10 20 30
```

Suppose:

```cpp
auto a = first;
auto b = first;

++a;
```

Advancing `a` consumes data from the stream.

Now `b` is no longer an independent traversal position.

Both iterators share the same underlying stream.

Therefore Input Iterators are considered single-pass.

---

# Why Forward Iterators Exist

Many algorithms require multiple passes.

Example:

```cpp
Pass 1:
Count elements

Pass 2:
Process elements
```

This is impossible with a pure Input Iterator.

But perfectly valid with a Forward Iterator.

---

# Example Container

The standard example is:

```cpp
std::forward_list<int>
```

Internally:

```text
Node
  |
  v
Node
  |
  v
Node
```

A singly linked list.

---

# Visual Model

```text
1 -> 2 -> 3 -> 4 -> 5
```

You can move:

```cpp
++it
```

but not:

```cpp
--it
```

because links only exist in one direction.

---

# Example

```cpp
#include <forward_list>
#include <iostream>

int main()
{
    std::forward_list<int> fl{1,2,3,4};

    for(auto it = fl.begin();
        it != fl.end();
        ++it)
    {
        std::cout << *it << '\n';
    }
}
```

Output:

```text
1
2
3
4
```

---

# Comparison with Input Iterator

Input Iterator:

```text
Read once
```

Forward Iterator:

```text
Read many times
```

Example:

```cpp
auto first = fl.begin();

auto a = first;
auto b = first;

++a;

std::cout << *b;
```

Valid.

`b` still points to the original element.

---

# Algorithms Requiring Forward Iterators

Some algorithms need to revisit elements.

Examples:

```cpp
std::remove
std::unique
std::partition
```

These algorithms require stronger guarantees than Input Iterators provide.

---

# Complexity Implications

Forward Iterators still do not support:

```cpp
it + n
it - n
it[n]
```

To move forward:

```cpp
for(int i = 0; i < n; ++i)
{
    ++it;
}
```

Complexity:

```text
O(n)
```

---

# Real STL Insight

Most node-based containers provide at least Forward Iterators.

Examples:

```cpp
std::forward_list
std::unordered_set
std::unordered_map
```

These containers are not contiguous.

They are connected through nodes.

---

# Input Iterator vs Forward Iterator

| Feature              | Input          | Forward    |
| -------------------- | -------------- | ---------- |
| Read                 | Yes            | Yes        |
| Forward Movement     | Yes            | Yes        |
| Multi-Pass           | No             | Yes        |
| Copy Iterator Safely | Not Guaranteed | Guaranteed |
| Backward Movement    | No             | No         |

---

# Interview Questions

## Q1

What is the biggest difference between Input Iterator and Forward Iterator?

Answer:

Forward Iterators provide the multi-pass guarantee.

Input Iterators do not.

---

## Q2

Can a Forward Iterator move backward?

Answer:

No.

Only forward movement is supported.

---

## Q3

Why isn't std::istream_iterator a Forward Iterator?

Answer:

Advancing one iterator consumes input from the stream.

Copies cannot be used independently.

Therefore it is only an Input Iterator.

---

# Key Takeaways

1. Forward Iterator extends Input Iterator.
2. It provides the multi-pass guarantee.
3. Copies remain independently usable.
4. It still supports only forward traversal.
5. std::forward_list is the canonical Forward Iterator example.
6. Many STL algorithms depend on the multi-pass guarantee.
