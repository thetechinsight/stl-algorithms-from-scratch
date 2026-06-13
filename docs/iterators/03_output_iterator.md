# Output Iterator

## Learning Objectives

After completing this chapter, you should be able to:

* Explain what an Output Iterator is
* Understand why Output Iterators form a separate iterator category
* Explain the single-pass nature of Output Iterators
* Understand how STL algorithms write through Output Iterators
* Use common Output Iterator adapters
* Explain Output Iterator interview questions confidently

---

# What is an Output Iterator?

An Output Iterator is an iterator that provides write access while moving forward through a sequence.

Unlike Input Iterators, which are used to read values, Output Iterators are used to write values to a destination.

Typical destinations include:

```text
Console
File
Container
Stream
Custom Output Sink
```

Conceptually:

```text
Source
   |
   v
Algorithm
   |
   v
Output Iterator
   |
   v
Destination
```

Examples:

```text
vector ---> copy ---> ostream_iterator ---> cout

vector ---> copy ---> back_insert_iterator ---> vector

vector ---> copy ---> insert_iterator ---> set
```

Output Iterators are part of the STL's generic programming model because they allow algorithms to write to many different destinations using a common interface.

---

# Why Output Iterators Are a Separate Category

The STL iterator hierarchy is primarily based on reading elements.

Output Iterators are fundamentally different because their purpose is writing rather than reading.

For this reason, Output Iterators form a separate iterator category rather than participating in the Input → Forward → Bidirectional → Random Access hierarchy.

Conceptually:

```text
Input Iterator  -> Read values

Output Iterator -> Write values
```

---

# Single-Pass Nature

Output Iterators are single-pass iterators.

They are intended to be used only once while moving forward.

The typical usage pattern is:

```cpp
while (...)
{
    *pos = value;
    ++pos;
}
```

Each write operation is normally followed by an increment operation.

The behavior of repeatedly writing to the same position without advancing the iterator is not generally guaranteed.

Because of this property, Output Iterators are classified as single-pass iterators.

---

# Operations Supported

Output Iterators support the following operations:

```cpp
*iter = value;
```

Writes a value to the destination.

```cpp
++iter;
```

Advances the iterator.

```cpp
iter++;
```

Advances the iterator and returns the previous iterator value.

```cpp
TYPE(iter);
```

Copy construction.

Unlike many other iterator categories, Output Iterators do not require comparison operations.

---

# Write-Oriented Access

For an Output Iterator:

```cpp
*iter = value;
```

is valid.

However:

```cpp
auto value = *iter;
```

is generally not meaningful.

The value obtained through:

```cpp
*iter
```

is intended to be assigned to rather than read from.

For this reason, Output Iterators are often described as write-only iterators.

---

# Mutable Iterators

Many iterators support both reading and writing.

Example:

```cpp
std::vector<int>::iterator it = v.begin();

int value = *it; // read

*it = 42;        // write
```

Such iterators are often called mutable iterators.

Output Iterators are different because they are designed specifically for output operations.

---

# Output Iterators and STL Algorithms

A common use of Output Iterators is as destinations for STL algorithms.

Consider:

```cpp
std::copy(
    first,
    last,
    result);
```

where:

```text
[first,last)
```

represents the source range and

```text
result
```

is an Output Iterator.

The actual STL signature is:

```cpp
template<
    class InputIt,
    class OutputIt>
constexpr OutputIt copy(
    InputIt first,
    InputIt last,
    OutputIt d_first);
```

Notice that:

```cpp
InputIt
```

and

```cpp
OutputIt
```

are completely independent types.

This allows the same algorithm to copy data between many different destinations.

Examples:

```text
vector -> vector

vector -> list

vector -> file

vector -> console

vector -> network stream
```

without changing the algorithm itself.

---

# Simplified Implementation of std::copy

```cpp
template<typename InputIt,
         typename OutputIt>
OutputIt my_copy(
    InputIt first,
    InputIt last,
    OutputIt result)
{
    while(first != last)
    {
        *result = *first;

        ++result;
        ++first;
    }

    return result;
}
```

Notice that the algorithm only depends on the Output Iterator interface.

It does not know the actual destination type.

This is one of the key design principles of the STL.

---

# Common Output Iterator Adapters

## ostream_iterator

Writes values to an output stream.

Example:

```cpp
std::ostream_iterator<int>
```

Conceptually:

```cpp
*it = value;
```

becomes:

```cpp
std::cout << value;
```

---

## back_insert_iterator

Inserts elements at the end of a container.

Example:

```cpp
std::back_inserter(v)
```

Conceptually:

```cpp
*it = value;
```

becomes:

```cpp
v.push_back(value);
```

---

## front_insert_iterator

Inserts elements at the beginning of a container.

Example:

```cpp
std::front_inserter(lst)
```

Conceptually:

```cpp
*it = value;
```

becomes:

```cpp
lst.push_front(value);
```

---

## insert_iterator

Inserts elements at a specified position.

Example:

```cpp
std::inserter(container, pos)
```

Conceptually:

```cpp
*it = value;
```

becomes:

```cpp
container.insert(pos, value);
```

---

# Output Iterator vs Input Iterator

| Feature      | Output Iterator | Input Iterator |
| ------------ | --------------- | -------------- |
| Read Values  | No              | Yes            |
| Write Values | Yes             | Not Required   |
| Move Forward | Yes             | Yes            |
| Single-Pass  | Yes             | Yes            |
| Typical Role | Destination     | Source         |

---

# Interview Trap

## Question

Why is Output Iterator not derived from Input Iterator?

## Answer

Input Iterators are designed for reading values.

Output Iterators are designed for writing values.

Because their requirements are fundamentally different, the STL treats them as separate iterator categories.

---

# Interview Summary

## Must Remember

* Output Iterators are write-oriented iterators.
* Output Iterators are single-pass iterators.
* The primary operation is:

```cpp
*iter = value;
```

* Common examples:

  * ostream_iterator
  * back_insert_iterator
  * front_insert_iterator
  * insert_iterator
* std::copy() typically uses:

  * Input Iterator as source
  * Output Iterator as destination
* Output Iterators form a separate category from the read-oriented iterator hierarchy.

---

# Key Takeaways

1. Output Iterators provide write access while moving forward.
2. They are single-pass iterators.
3. They are intended for output operations rather than reading values.
4. STL algorithms use Output Iterators as generic destinations.
5. Iterator adapters such as back_inserter and ostream_iterator are Output Iterators.
6. Output Iterators are separate from the Input → Forward → Bidirectional → Random Access hierarchy.
