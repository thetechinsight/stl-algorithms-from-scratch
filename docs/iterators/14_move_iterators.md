# Move Iterators

## Learning Objectives

After completing this chapter, you should be able to:

- Explain what a Move Iterator is
- Understand why Move Iterators exist
- Understand `std::move_iterator`
- Use `std::make_move_iterator()`
- Explain how Move Iterators transform algorithms
- Understand the relationship between Move Iterators and move semantics
- Use Move Iterators with move-only types
- Answer common Move Iterator interview questions

---

# Motivation

Consider:

```cpp
std::vector<std::string> source{
    "one",
    "two",
    "three"
};

std::vector<std::string> destination;
```

Using:

```cpp
std::copy(
    source.begin(),
    source.end(),
    std::back_inserter(destination));
```

copies every string.

Conceptually:

```cpp
destination.push_back(*it);
```

Each element is copied.

Sometimes copying is unnecessary or impossible.

Instead we would like to transfer ownership of the elements.

That is exactly what Move Iterators provide.

---

# Traditional Solution

Without Move Iterators we might write:

```cpp
for (auto& elem : source)
{
    destination.push_back(
        std::move(elem));
}
```

This works.

However:

```text
Manual loop required
Algorithm lost
```

Move Iterators allow STL algorithms to perform the move operation automatically.

---

# What Is a Move Iterator?

A Move Iterator is an iterator adapter that converts element access into move semantics.

Normal iterator:

```cpp
*it
```

returns:

```cpp
T&
```

Move Iterator:

```cpp
*it
```

behaves conceptually as:

```cpp
std::move(*it)
```

and yields:

```cpp
T&&
```

Thus:

```text
Dereference
     ↓
Convert to rvalue
     ↓
Move instead of copy
```

---

# std::move_iterator

The STL provides:

```cpp
std::move_iterator<Iterator>
```

which wraps an existing iterator.

Conceptually:

```text
Iterator
     ↓
move_iterator
     ↓
Rvalue Reference
```

The underlying traversal behavior remains unchanged.

Only dereferencing behavior changes.

---

# Creating Move Iterators

Move Iterators can be created directly:

```cpp
std::move_iterator<
    std::vector<std::string>::iterator>
        first(source.begin());
```

However, this syntax is cumbersome.

Usually:

```cpp
std::make_move_iterator()
```

is preferred.

Example:

```cpp
auto first =
    std::make_move_iterator(
        source.begin());

auto last =
    std::make_move_iterator(
        source.end());
```

---

# Using Move Iterators With Algorithms

Example:

```cpp
std::vector<std::string> source{
    "one",
    "two",
    "three"
};

std::vector<std::string> destination;

std::copy(
    std::make_move_iterator(source.begin()),
    std::make_move_iterator(source.end()),
    std::back_inserter(destination));
```

The algorithm is still:

```cpp
std::copy()
```

However:

```cpp
*first
```

now behaves like:

```cpp
std::move(*source_iterator)
```

Thus move construction occurs instead of copy construction.

---

# The Key STL Idea

The algorithm does not know whether it is copying or moving.

It simply performs:

```cpp
*result = *first;
```

The iterator determines the behavior.

Normal iterator:

```text
Copy
```

Move Iterator:

```text
Move
```

This is another example of STL behavior being customized through iterator types.

---

# Conceptual Implementation

A normal iterator typically provides:

```cpp
T& operator*();
```

A Move Iterator behaves conceptually as:

```cpp
T&& operator*();
```

Example:

```cpp
reference operator*() const
{
    return std::move(*current);
}
```

This is the central idea behind Move Iterators.

---

# Visual View

Normal Iterator:

```text
Container
   ↓
iterator
   ↓
T&
```

Move Iterator:

```text
Container
   ↓
move_iterator
   ↓
std::move(T&)
   ↓
T&&
```

---

# Move-Only Types

Move Iterators are especially useful for move-only types.

Example:

```cpp
std::vector<
    std::unique_ptr<int>> source;
```

This fails:

```cpp
std::copy(
    source.begin(),
    source.end(),
    std::back_inserter(dest));
```

because:

```cpp
std::unique_ptr
```

cannot be copied.

Using Move Iterators:

```cpp
std::copy(
    std::make_move_iterator(
        source.begin()),
    std::make_move_iterator(
        source.end()),
    std::back_inserter(dest));
```

works correctly.

Ownership is transferred rather than copied.

---

# Source After Moving

After moving:

```cpp
source
```

still contains the same number of elements.

However the elements are now in a:

```text
Valid but unspecified state
```

For strings this often means:

```cpp
""
```

but the standard does not guarantee any particular value.

Only validity is guaranteed.

---

# Move Iterators vs std::move Algorithm

C++11 also introduced:

```cpp
std::move(
    first,
    last,
    result);
```

Conceptually:

```cpp
*result =
    std::move(*first);
```

Thus:

```cpp
std::move(...)
```

and:

```cpp
std::copy(
    std::make_move_iterator(first),
    std::make_move_iterator(last),
    result);
```

have very similar behavior.

---

# What Move Iterators Do Not Do

A common misconception is that:

```cpp
++it
```

moves an element.

It does not.

Incrementing merely advances the iterator.

The move occurs when:

```cpp
*it
```

is used as an rvalue.

---

# Real STL Insight

Many STL algorithms can be transformed from copying algorithms into moving algorithms simply by changing the iterator type.

The algorithm itself remains unchanged.

This is one of the most elegant examples of iterator adapters in the STL.

---

# Interview Trap

## Question

Why does:

```cpp
std::copy(
    std::make_move_iterator(begin),
    std::make_move_iterator(end),
    result);
```

move elements even though the algorithm is `copy()`?

### Answer

Because dereferencing a Move Iterator yields an rvalue reference.

The algorithm therefore receives movable values rather than lvalue references.

---

## Question

Does a Move Iterator move elements when incremented?

### Answer

No.

Movement occurs when the dereferenced value is used.

Incrementing only advances the iterator.

---

# Interview Questions

## Q1

What is a Move Iterator?

**Answer:**

An iterator adapter that converts dereferencing into move semantics.

---

## Q2

Which helper function creates Move Iterators?

**Answer:**

```cpp
std::make_move_iterator()
```

---

## Q3

What does:

```cpp
*move_iterator
```

conceptually return?

**Answer:**

```cpp
std::move(*current)
```

---

## Q4

Why are Move Iterators useful?

**Answer:**

They allow STL algorithms to move elements instead of copying them without changing the algorithm.

---

## Q5

Can Move Iterators be used with move-only types?

**Answer:**

Yes.

They are particularly useful with:

```cpp
std::unique_ptr
```

and other move-only types.

---

# Key Takeaways

1. Move Iterators are iterator adapters.
2. They convert dereferencing into move semantics.
3. `std::make_move_iterator()` is the preferred creation mechanism.
4. STL algorithms remain unchanged.
5. The iterator determines whether values are copied or moved.
6. Move Iterators are especially useful with move-only types.
7. The move operation occurs during dereferencing, not incrementing.
8. Move Iterators demonstrate STL's design principle of behavior through iterator types.