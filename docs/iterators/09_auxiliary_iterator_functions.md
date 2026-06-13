# Auxiliary Iterator Functions

## Learning Objectives

After completing this chapter, you should be able to:

* Explain why auxiliary iterator functions exist
* Understand the increment and decrement problem of iterators
* Understand `std::next()`
* Understand `std::prev()`
* Understand `std::advance()`
* Understand `std::distance()`
* Understand how iterator categories affect complexity
* Write portable STL code
* Answer common iterator utility interview questions

---

# Why Do Auxiliary Iterator Functions Exist?

Different iterator categories support different operations.

For example:

```cpp
std::vector<int>::iterator
```

supports:

```cpp
it += n;
it + n;
```

because it is a Random Access Iterator.

However:

```cpp
std::list<int>::iterator
```

does not.

Therefore writing:

```cpp
it += 5;
```

is not generic STL code.

The STL provides utility functions that work correctly across iterator categories.

These functions automatically adapt their implementation based on the iterator category.

The most important ones are:

```cpp
std::next()
std::prev()
std::advance()
std::distance()
```

---

# The Increment and Decrement Problem

Consider:

```cpp
std::vector<int> coll;

/*
 * Sort everything except the first element
 */
std::sort(++coll.begin(), coll.end());
```

At first glance this appears perfectly reasonable.

The intention is:

```text
begin()      -> first element
++begin()    -> second element
sort from there
```

However, this code is not portable.

---

## Why?

The key observation is:

```cpp
coll.begin()
```

returns a temporary iterator object.

Conceptually:

```cpp
auto temp = coll.begin();
```

The expression:

```cpp
++coll.begin()
```

therefore means:

```cpp
++temporary_iterator
```

The increment operator is being applied directly to a temporary object.

---

## Why Does It Depend on the Implementation?

Historically, some STL implementations represented:

```cpp
std::vector<int>::iterator
```

as:

```cpp
int*
```

If:

```cpp
coll.begin()
```

returns a temporary pointer value, then:

```cpp
++coll.begin()
```

attempts to modify a temporary pointer.

This is not allowed.

Compilation fails.

---

Other implementations use iterator classes:

```cpp
class Iterator
{
public:
    Iterator& operator++()
    {
        // advance iterator
        return *this;
    }
};
```

In this case:

```cpp
++coll.begin()
```

may compile successfully.

---

## The Portability Problem

Code that compiles on one STL implementation may fail on another.

Example:

```cpp
std::sort(++coll.begin(), coll.end());
```

Portable?

```text
No
```

Implementation dependent?

```text
Yes
```

The same issue exists with:

```cpp
--coll.end()
```

---

## Modern STL Solution

Instead of:

```cpp
++coll.begin()
```

write:

```cpp
std::next(coll.begin())
```

Instead of:

```cpp
--coll.end()
```

write:

```cpp
std::prev(coll.end())
```

These expressions are portable and work correctly regardless of iterator implementation.

---

## Example

Non-portable:

```cpp
std::sort(
    ++coll.begin(),
    coll.end());
```

Portable:

```cpp
std::sort(
    std::next(coll.begin()),
    coll.end());
```

Both express:

```text
Start from the second element.
```

Only the second version is guaranteed to work everywhere.

---

# std::next()

## Purpose

Returns an iterator advanced by a specified number of positions.

Unlike:

```cpp
std::advance()
```

it does not modify the original iterator.

---

## Syntax

```cpp
std::next(iter)
```

```cpp
std::next(iter, n)
```

---

## Example

```cpp
std::vector<int> v{10,20,30,40};

auto it = v.begin();

auto second = std::next(it);
```

Afterward:

```cpp
it
```

still refers to:

```text
10
```

and

```cpp
second
```

refers to:

```text
20
```

---

## Conceptual Implementation

```cpp
template<typename Iter>
Iter next(Iter iter)
{
    ++iter;
    return iter;
}
```

The original iterator remains unchanged.

---

## Complexity

| Iterator Category | Complexity |
| ----------------- | ---------- |
| Input             | O(n)       |
| Forward           | O(n)       |
| Bidirectional     | O(n)       |
| Random Access     | O(1)       |

---

# std::prev()

## Purpose

Returns an iterator moved backward by a specified number of positions.

Like `std::next()`, it does not modify the original iterator.

---

## Syntax

```cpp
std::prev(iter)
```

```cpp
std::prev(iter, n)
```

---

## Example

```cpp
std::vector<int> v{10,20,30,40};

auto last = std::prev(v.end());
```

Now:

```cpp
*last
```

is:

```text
40
```

---

## Why Use std::prev()?

Avoid:

```cpp
--container.end()
```

Prefer:

```cpp
std::prev(container.end())
```

This avoids the temporary iterator problem.

---

## Complexity

| Iterator Category | Complexity |
| ----------------- | ---------- |
| Bidirectional     | O(n)       |
| Random Access     | O(1)       |

---

# std::advance()

## Purpose

Moves an iterator by a specified number of positions.

Unlike:

```cpp
std::next()
```

it modifies the iterator itself.

---

## Syntax

```cpp
std::advance(iter, n);
```

---

## Example

```cpp
std::list<int> lst{10,20,30,40,50};

auto it = lst.begin();

std::advance(it, 3);

std::cout << *it;
```

Output:

```text
40
```

---

## advance() vs next()

Using:

```cpp
std::advance(it, 3);
```

changes:

```cpp
it
```

itself.

Afterward:

```cpp
it
```

refers to the fourth element.

Using:

```cpp
auto pos = std::next(it, 3);
```

leaves:

```cpp
it
```

unchanged.

---

## Complexity

| Iterator Category | Complexity |
| ----------------- | ---------- |
| Input             | O(n)       |
| Forward           | O(n)       |
| Bidirectional     | O(n)       |
| Random Access     | O(1)       |

---

# std::distance()

## Purpose

Computes the number of elements between two iterators.

---

## Syntax

```cpp
std::distance(first, last)
```

---

## Example

```cpp
std::vector<int> v{10,20,30,40,50};

auto n =
    std::distance(
        v.begin(),
        v.end());
```

Result:

```text
5
```

---

## Complexity

For Random Access Iterators:

```cpp
last - first
```

can be used.

Complexity:

```text
O(1)
```

For weaker iterator categories, traversal is required.

Complexity:

```text
O(n)
```

---

# Iterator Category Optimization

One of the most elegant STL design ideas is that these functions automatically adapt to the iterator category.

Example:

```cpp
std::advance(it, 1000);
```

For:

```cpp
std::vector<int>::iterator
```

conceptually becomes:

```cpp
it += 1000;
```

Complexity:

```text
O(1)
```

For:

```cpp
std::list<int>::iterator
```

conceptually becomes:

```cpp
for (...)
{
    ++it;
}
```

Complexity:

```text
O(n)
```

Same interface.

Different implementation.

This is a core STL design principle.

---

# Visual Summary

```text
advance(it, n)
    modifies it

next(it, n)
    returns a new iterator

prev(it, n)
    returns a new iterator

distance(first, last)
    returns number of elements
```

---

# Interview Trap

## Question

Why should:

```cpp
++container.begin()
```

be avoided?

### Answer

Because `begin()` returns a temporary iterator.

Incrementing a temporary iterator may not be portable across implementations.

Use:

```cpp
std::next(container.begin())
```

instead.

---

## Question

What is the difference between:

```cpp
std::advance()
```

and

```cpp
std::next()
```

?

### Answer

`std::advance()` modifies the iterator.

`std::next()` returns a new iterator and leaves the original unchanged.

---

## Question

Why can:

```cpp
std::distance()
```

be O(1) for vectors but O(n) for lists?

### Answer

Random Access Iterators support:

```cpp
last - first
```

while list iterators require traversal.

---

# Interview Questions

## Q1

What does `std::advance()` do?

**Answer:**

Moves an iterator by a specified number of positions.

---

## Q2

What does `std::distance()` return?

**Answer:**

The number of elements between two iterators.

---

## Q3

What is the difference between `std::advance()` and `std::next()`?

**Answer:**

`advance()` modifies the iterator.

`next()` returns a new iterator.

---

## Q4

Why was `std::next()` introduced?

**Answer:**

To provide a portable way to advance temporary iterators.

---

## Q5

What is the complexity of `std::distance()` for Random Access Iterators?

**Answer:**

```text
O(1)
```

---

# Interview Summary

## Must Remember

* `begin()` and `end()` return temporary iterators.
* Avoid:

  * `++container.begin()`
  * `--container.end()`
* Prefer:

  * `std::next(container.begin())`
  * `std::prev(container.end())`
* `std::advance()` modifies an iterator.
* `std::next()` and `std::prev()` return new iterators.
* `std::distance()` computes the number of elements between iterators.
* Complexity depends on iterator category.

---

# Key Takeaways

1. Auxiliary iterator functions provide generic iterator manipulation.
2. `std::next()` and `std::prev()` solve the temporary iterator portability problem.
3. `std::advance()` modifies an iterator.
4. `std::next()` and `std::prev()` return new iterators.
5. `std::distance()` computes iterator separation.
6. Complexity depends on the iterator category.
7. STL utility functions automatically adapt to iterator capabilities.
8. These functions help write portable and generic STL code.
