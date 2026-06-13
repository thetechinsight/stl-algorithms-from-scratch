# Stream Iterators

## Learning Objectives

After completing this chapter, you should be able to:

- Explain what Stream Iterators are
- Understand `std::istream_iterator`
- Understand `std::ostream_iterator`
- Understand how streams can be treated as iterator ranges
- Use STL algorithms directly with streams
- Understand end-of-stream iterators
- Understand delimiters in `ostream_iterator`
- Explain why stream iterators model Input and Output Iterators
- Answer common Stream Iterator interview questions

---

# Motivation

Consider the traditional way of reading integers:

```cpp
int x;

while (std::cin >> x)
{
    // process x
}
```

And the traditional way of printing values:

```cpp
for (const auto& value : container)
{
    std::cout << value << ' ';
}
```

The STL asks:

```text
Can streams be treated like sequences?
```

The answer is:

```text
Yes.
```

using Stream Iterators.

---

# What Are Stream Iterators?

Stream Iterators are iterator adapters that allow streams to participate in the STL iterator model.

They adapt streams so that algorithms can process them through the iterator interface.

```text
Stream
   ↓
Iterator Adapter
   ↓
Algorithm
```

This allows algorithms to read from and write to streams exactly as they work with containers.

---

# Streams as Iterator Ranges

Streams can act as sources and destinations for STL algorithms.

Conceptually:

```text
Input Stream
      ↓
istream_iterator
      ↓
Algorithm
      ↓
ostream_iterator
      ↓
Output Stream
```

Example:

```cpp
std::copy(
    std::istream_iterator<int>(std::cin),
    std::istream_iterator<int>(),
    std::ostream_iterator<int>(
        std::cout,
        "\n"));
```

Input:

```text
10 20 30
```

Output:

```text
10
20
30
```

No container is involved.

---

# Types of Stream Iterators

The STL provides two stream iterator adapters:

```cpp
std::istream_iterator
std::ostream_iterator
```

---

# std::istream_iterator

## Purpose

Reads values from an input stream.

Example:

```cpp
std::istream_iterator<int> in(std::cin);
```

This iterator extracts values from the stream and makes them available through the iterator interface.

---

# How istream_iterator Works

An `istream_iterator` is associated with a stream and stores the most recently extracted value.

Conceptually:

```cpp
std::istream_iterator<int> it(std::cin);
```

performs an initial extraction from the stream.

Subsequent increments:

```cpp
++it;
```

extract additional values.

Thus:

```cpp
*it
```

returns the value most recently read from the stream.

---

# Reading Input

Example:

```cpp
#include <iostream>
#include <iterator>

int main()
{
    std::istream_iterator<int> in(std::cin);
    std::istream_iterator<int> end;

    while (in != end)
    {
        std::cout << *in << '\n';

        ++in;
    }
}
```

Input:

```text
10 20 30 40
```

Output:

```text
10
20
30
40
```

---

# Why Is It An Input Iterator?

Input Iterators:

```text
Read values
Move forward
Single-pass
```

Streams behave exactly the same way.

Once data has been extracted from a stream:

```text
It is consumed.
```

Therefore:

```cpp
std::istream_iterator
```

models an Input Iterator.

It does not provide the multi-pass guarantee required of Forward Iterators.

---

# End-of-Stream Iterator

A default-constructed `istream_iterator` represents the end of the stream.

Example:

```cpp
std::istream_iterator<int> end;
```

or:

```cpp
std::istream_iterator<int>()
```

This iterator is often called the **past-the-end stream iterator**.

When extraction from the stream fails:

```cpp
stream >> value
```

the stream iterator becomes equal to this end iterator.

Typical usage:

```cpp
std::istream_iterator<int> in(std::cin);
std::istream_iterator<int> end;

while (in != end)
{
    ...
}
```

---

# Using Algorithms With Input Streams

One of the most elegant examples is reading values directly into a container:

```cpp
std::vector<int> values;

std::copy(
    std::istream_iterator<int>(std::cin),
    std::istream_iterator<int>(),
    std::back_inserter(values));
```

Input:

```text
1 2 3 4
```

Result:

```text
values = {1,2,3,4}
```

No explicit loop is required.

---

# Constructing Containers From Streams

A container can even be constructed directly from a stream range:

```cpp
std::vector<int> values(
    std::istream_iterator<int>(std::cin),
    std::istream_iterator<int>());
```

All values are copied from the stream into the vector.

Again, no explicit loop is necessary.

---

# std::ostream_iterator

## Purpose

Writes values to an output stream.

Example:

```cpp
std::ostream_iterator<int> out(std::cout);
```

Assignments through the iterator write values to the stream.

---

# How ostream_iterator Works

Conceptually:

```cpp
*out = value;
```

becomes:

```cpp
stream << value;
```

The assignment operator is transformed into an output operation.

---

# Optional Delimiter

An `ostream_iterator` may be constructed with an optional delimiter string.

Example:

```cpp
std::ostream_iterator<int>(
    std::cout,
    " ");
```

Now every output operation writes:

```text
value + delimiter
```

Example:

```cpp
std::copy(
    v.begin(),
    v.end(),
    std::ostream_iterator<int>(
        std::cout,
        " "));
```

Output:

```text
10 20 30 40
```

Without a delimiter:

```cpp
std::ostream_iterator<int>(std::cout)
```

the output becomes:

```text
10203040
```

---

# Writing Output

Example:

```cpp
#include <iostream>
#include <iterator>

int main()
{
    std::ostream_iterator<int>
        out(std::cout, " ");

    *out = 10;
    *out = 20;
    *out = 30;
}
```

Output:

```text
10 20 30
```

---

# Why Is It An Output Iterator?

Output Iterators:

```text
Write values
Move forward
Single-pass
```

Output streams behave in exactly this manner.

Therefore:

```cpp
std::ostream_iterator
```

models an Output Iterator.

---

# Using Algorithms With Output Streams

Example:

```cpp
std::vector<int> v{10,20,30,40};

std::copy(
    v.begin(),
    v.end(),
    std::ostream_iterator<int>(
        std::cout,
        " "));
```

Output:

```text
10 20 30 40
```

No explicit loop is required.

---

# Stream-to-Stream Copy

One of the classic STL examples is copying directly from an input stream to an output stream:

```cpp
std::copy(
    std::istream_iterator<int>(std::cin),
    std::istream_iterator<int>(),
    std::ostream_iterator<int>(
        std::cout,
        "\n"));
```

Input:

```text
10 20 30
```

Output:

```text
10
20
30
```

The algorithm operates entirely through iterators.

---

# Conceptual Implementations

## istream_iterator

Conceptually:

```cpp
template<typename T>
class istream_iterator
{
    std::istream* stream;
    T value;

public:
    const T& operator*() const
    {
        return value;
    }

    istream_iterator& operator++()
    {
        (*stream) >> value;
        return *this;
    }
};
```

---

## ostream_iterator

Conceptually:

```cpp
template<typename T>
class ostream_iterator
{
    std::ostream* stream;

public:
    ostream_iterator&
    operator=(const T& value)
    {
        (*stream) << value;

        return *this;
    }
};
```

---

# Algorithms Do Not Know About Streams

Consider:

```cpp
std::copy(first, last, result);
```

The algorithm does not know whether:

```cpp
first
```

is:

```cpp
vector iterator
list iterator
istream_iterator
```

nor whether:

```cpp
result
```

is:

```cpp
vector iterator
back_insert_iterator
ostream_iterator
```

The algorithm simply uses the iterator interface.

This is one of the key design principles of the STL.

---

# Real STL Insight

Many developers think STL algorithms work only with containers.

This is not true.

Algorithms operate on iterators.

Streams become usable by algorithms because they can be adapted into iterators.

This is one of the strongest demonstrations of STL's generic design.

---

# Interview Trap

## Question

Why is `std::istream_iterator` only an Input Iterator and not a Forward Iterator?

### Answer

Because reading from a stream consumes data.

The iterator is single-pass and does not provide the multi-pass guarantee.

---

## Question

Why is `std::ostream_iterator` an Output Iterator?

### Answer

Because it supports writing values but does not provide meaningful read access.

---

## Question

What does a default-constructed `istream_iterator` represent?

### Answer

The end of the input stream.

---

# Interview Questions

## Q1

What does `std::istream_iterator` do?

**Answer:**

Reads values from a stream.

---

## Q2

What does `std::ostream_iterator` do?

**Answer:**

Writes values to a stream.

---

## Q3

What iterator category does `std::istream_iterator` model?

**Answer:**

Input Iterator.

---

## Q4

What iterator category does `std::ostream_iterator` model?

**Answer:**

Output Iterator.

---

## Q5

What does:

```cpp
std::istream_iterator<int>()
```

represent?

**Answer:**

A past-the-end stream iterator.

---

## Q6

Why can STL algorithms work directly with streams?

**Answer:**

Because streams can be adapted into iterators, and STL algorithms operate on iterators rather than containers.

---

# Key Takeaways

1. Stream Iterators adapt streams into iterators.
2. `std::istream_iterator` reads values from streams.
3. `std::ostream_iterator` writes values to streams.
4. A default-constructed `istream_iterator` represents the end of a stream.
5. `istream_iterator` is an Input Iterator.
6. `ostream_iterator` is an Output Iterator.
7. Stream Iterators allow STL algorithms to work directly with I/O.
8. Containers can be constructed directly from stream ranges.
9. STL algorithms work with streams because they operate on iterators rather than containers.
10. Stream Iterators are one of the best examples of STL's generic design.