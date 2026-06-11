# distance() and advance()

## Motivation

Different iterators support different operations.

For example:

```cpp
std::vector<int>::iterator
```

supports:

```cpp
it + n
last - first
```

But:

```cpp
std::list<int>::iterator
```

does not.

Question:

How can STL provide a single interface that works with both?

Example:

```cpp
std::distance(first, last);

std::advance(it, n);
```

The answer is:

```cpp
iterator_traits
+
iterator_category
+
tag dispatching
```

---

# std::distance()

Purpose:

Determine how many elements exist between two iterators.

Example:

```cpp
std::vector<int> v{1,2,3,4,5};

auto n =
    std::distance(
        v.begin(),
        v.end());

std::cout << n;
```

Output:

```text
5
```

---

# Vector Example

```cpp
std::vector<int> v{1,2,3,4,5};
```

Internally STL can do:

```cpp
v.end() - v.begin()
```

Result:

```text
5
```

Complexity:

```text
O(1)
```

because vector iterators are Random Access.

---

# List Example

```cpp
std::list<int> lst{1,2,3,4,5};
```

There is no:

```cpp
last - first
```

for list iterators.

STL must walk through nodes:

```cpp
while(first != last)
{
    ++count;
    ++first;
}
```

Complexity:

```text
O(n)
```

---

# Same Interface, Different Implementation

User code:

```cpp
std::distance(first, last);
```

Implementation selected:

```text
Random Access  -> O(1)
Forward/List   -> O(n)
```

This is one of the core ideas behind STL.

---

# Simplified Implementation

Public interface:

```cpp
template<typename Iterator>
auto my_distance(
    Iterator first,
    Iterator last)
{
    using category =
        typename
        std::iterator_traits<
            Iterator
        >::iterator_category;

    return my_distance_impl(
        first,
        last,
        category{});
}
```

Notice:

```cpp
category{}
```

This is tag dispatching.

---

# Forward Iterator Version

```cpp
template<typename Iterator>
auto my_distance_impl(
    Iterator first,
    Iterator last,
    std::forward_iterator_tag)
{
    typename
    std::iterator_traits<
        Iterator
    >::difference_type n = 0;

    while(first != last)
    {
        ++n;
        ++first;
    }

    return n;
}
```

Complexity:

```text
O(n)
```

---

# Random Access Version

```cpp
template<typename Iterator>
auto my_distance_impl(
    Iterator first,
    Iterator last,
    std::random_access_iterator_tag)
{
    return last - first;
}
```

Complexity:

```text
O(1)
```

---

# Why This Is Beautiful

The user writes:

```cpp
std::distance(first, last);
```

The STL automatically chooses the best implementation.

No runtime overhead.

Everything happens at compile time.

---

# std::advance()

Purpose:

Move an iterator forward by N positions.

Example:

```cpp
auto it = v.begin();

std::advance(it, 3);
```

Now:

```cpp
*it
```

is the fourth element.

---

# List Example

Suppose:

```cpp
std::list<int> lst;
```

STL must do:

```cpp
while(n--)
{
    ++it;
}
```

Complexity:

```text
O(n)
```

---

# Vector Example

Suppose:

```cpp
std::vector<int> v;
```

STL can do:

```cpp
it += n;
```

Complexity:

```text
O(1)
```

---

# Simplified Implementation

Forward Iterator:

```cpp
template<typename Iterator>
void my_advance_impl(
    Iterator& it,
    int n,
    std::forward_iterator_tag)
{
    while(n--)
    {
        ++it;
    }
}
```

---

# Random Access Version

```cpp
template<typename Iterator>
void my_advance_impl(
    Iterator& it,
    int n,
    std::random_access_iterator_tag)
{
    it += n;
}
```

---

# Bidirectional Iterator Version

Bidirectional Iterators can move both directions.

Example:

```cpp
std::advance(it, -3);
```

Possible because:

```cpp
--it
```

exists.

Implementation:

```cpp
if(n > 0)
{
    while(n--)
        ++it;
}
else
{
    while(n++)
        --it;
}
```

---

# Complexity Comparison

| Iterator Category | distance() | advance() |
| ----------------- | ---------- | --------- |
| Input             | O(n)       | O(n)      |
| Forward           | O(n)       | O(n)      |
| Bidirectional     | O(n)       | O(n)      |
| Random Access     | O(1)       | O(1)      |

---

# Real STL Insight

Many developers accidentally write:

```cpp
for(int i = 0;
    i < std::distance(first,last);
    ++i)
{
    ...
}
```

If:

```cpp
first
```

is a list iterator,

then:

```cpp
std::distance()
```

is O(n).

Calling it repeatedly can make an algorithm unexpectedly slow.

Understanding iterator categories helps avoid these mistakes.

---

# Example

Bad:

```cpp
for(auto it = lst.begin();
    it != lst.end();
    ++it)
{
    auto n =
        std::distance(
            it,
            lst.end());
}
```

Potential complexity:

```text
O(n²)
```

---

# Interview Questions

## Q1

Why is std::distance() O(1) for vector but O(n) for list?

Answer:

Vector iterators are Random Access.

List iterators are Bidirectional.

---

## Q2

How does STL select the correct implementation?

Answer:

Using:

```cpp
iterator_traits
iterator_category
tag dispatching
```

---

## Q3

Can std::advance(it, -5) work for a Forward Iterator?

Answer:

No.

Forward Iterators cannot move backward.

---

## Q4

Why does std::advance() have different complexities?

Answer:

Because different iterator categories provide different capabilities.

---

# Key Takeaways

1. distance() measures the range length.
2. advance() moves an iterator.
3. Random Access Iterators allow O(1) implementations.
4. Other iterator categories require O(n) traversal.
5. iterator_traits enables compile-time optimization.
6. distance() and advance() are classic examples of STL generic programming.
