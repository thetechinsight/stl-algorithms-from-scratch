# Iterator Adapters

## Learning Objectives

After completing this chapter, you should be able to:

* Explain what an Iterator Adapter is
* Understand why Iterator Adapters exist
* Understand how adapters modify iterator behavior
* Identify the major Iterator Adapters provided by the STL
* Understand the relationship between algorithms and Iterator Adapters
* Prepare for deeper study of Reverse, Insert, Stream, and Move Iterators

---

# Motivation

One of the most powerful ideas in the STL is that algorithms operate only on iterators.

Consider:

```cpp
std::find(first, last, value);

std::count(first, last, value);

std::copy(first, last, result);
```

Algorithms do not know:

* Which container is being used
* Whether elements come from a container, stream, or generated sequence
* Whether traversal is forward or backward

Algorithms only know how to work with iterators.

---

# The Problem

Sometimes the default behavior of an iterator is not what we want.

For example:

```cpp
std::vector<int> src{1,2,3,4};
std::vector<int> dest;
```

How can we copy elements into an empty container?

```cpp
std::copy(
    src.begin(),
    src.end(),
    ???);
```

A normal iterator requires existing elements:

```cpp
*it = value;
```

But:

```cpp
dest.begin()
```

does not refer to valid elements because the container is empty.

We need a way to change the behavior of assignment.

---

# What Is an Iterator Adapter?

An Iterator Adapter is an object that wraps another iterator and modifies its behavior.

Conceptually:

```text
Algorithm
    ↓
Iterator Adapter
    ↓
Underlying Iterator / Container / Stream
```

The adapter intercepts iterator operations and performs different actions.

---

# Why Iterator Adapters Exist

Iterator Adapters allow us to:

* Traverse sequences differently
* Insert elements instead of overwriting them
* Read directly from streams
* Write directly to streams
* Move objects efficiently

without changing the algorithms themselves.

This is a key example of STL's philosophy:

```text
Algorithms remain generic.
Behavior is customized through iterators.
```

---

# Types of Iterator Adapters

The STL provides four major categories of Iterator Adapters.

```text
Iterator Adapters
│
├── Reverse Iterators
├── Insert Iterators
├── Stream Iterators
└── Move Iterators
```

---

# Reverse Iterators

Reverse Iterators change traversal direction.

Example:

```cpp
v.begin()  → first element
v.end()    → one past last element
```

becomes:

```cpp
v.rbegin() → last element
v.rend()   → one before first element
```

Algorithms can then operate in reverse order.

Example:

```cpp
std::copy(
    v.rbegin(),
    v.rend(),
    out);
```

---

# Insert Iterators

Insert Iterators transform assignment into insertion.

Example:

```cpp
std::copy(
    src.begin(),
    src.end(),
    std::back_inserter(dest));
```

Conceptually:

```cpp
*it = value;
```

becomes:

```cpp
dest.push_back(value);
```

This allows algorithms to grow containers automatically.

---

# Stream Iterators

Stream Iterators connect algorithms directly to I/O streams.

Input:

```cpp
std::istream_iterator<int>
```

Output:

```cpp
std::ostream_iterator<int>
```

Example:

```cpp
std::copy(
    v.begin(),
    v.end(),
    std::ostream_iterator<int>(std::cout, " "));
```

Algorithms can write directly to the console.

---

# Move Iterators

Move Iterators convert element access into move operations.

Instead of:

```cpp
*it
```

returning:

```cpp
T&
```

it behaves like:

```cpp
std::move(*it)
```

This allows algorithms to transfer ownership efficiently.

Example:

```cpp
std::move(
    src.begin(),
    src.end(),
    dest.begin());
```

---

# The Power of Iterator Adapters

A remarkable property of STL algorithms is that they do not need special versions for different behaviors.

For example:

```cpp
std::copy()
```

can:

```text
Copy forward
Copy backward
Insert into containers
Write to streams
Move objects
```

simply by changing the iterator type.

The algorithm itself remains unchanged.

---

# Real STL Insight

Many developers believe STL algorithms contain the complexity.

In reality:

```text
Algorithm
    +
Iterator
```

is the true design of STL.

Iterator Adapters are one of the clearest demonstrations of this principle.

The same algorithm can behave very differently depending on the iterators supplied.

---

# Interview Questions

## Q1

What is an Iterator Adapter?

**Answer:**

An object that wraps another iterator and modifies its behavior.

---

## Q2

Why do Iterator Adapters exist?

**Answer:**

To customize iterator behavior without changing algorithms.

---

## Q3

What are the major categories of Iterator Adapters?

**Answer:**

* Reverse Iterators
* Insert Iterators
* Stream Iterators
* Move Iterators

---

## Q4

Which adapter allows algorithms to append elements to a container?

**Answer:**

Insert Iterators such as:

```cpp
std::back_inserter()
```

---

## Q5

Which adapter allows algorithms to write directly to a stream?

**Answer:**

```cpp
std::ostream_iterator
```

---

# Key Takeaways

1. Iterator Adapters modify iterator behavior.
2. They allow algorithms to remain generic.
3. Reverse Iterators change traversal direction.
4. Insert Iterators convert assignment into insertion.
5. Stream Iterators connect algorithms to I/O streams.
6. Move Iterators enable efficient transfer of resources.
7. STL flexibility comes from combining algorithms with different iterator types.
8. Iterator Adapters are a central part of STL design.
