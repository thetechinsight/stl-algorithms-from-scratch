# my_count

## STL Equivalent

`std::count`

## Description

Counts the number of occurrences of a value within a range.

Unlike `my_find`, which stops when a match is found, `my_count` must traverse the entire range to count all matching elements.

---

## Implementation

```cpp
template<typename Iterator, typename T>
int my_count(Iterator first, Iterator last, const T& value)
{
    int count = 0;

    while (first != last)
    {
        if (*first == value)
        {
            ++count;
        }

        ++first;
    }

    return count;
}
```

---

## Iterator Requirements

The algorithm requires the iterator to support:

```cpp
*it      // dereference
++it     // increment
it != other
```

---

## Iterator Category

Input Iterator or stronger.

Examples:

* `std::vector`
* `std::list`
* `std::forward_list`
* `std::set`
* `std::map`

---

## Complexity

### Time

`O(n)`

The algorithm examines every element in the range.

### Space

`O(1)`

No additional memory is allocated.

---

## Example

```cpp
std::vector<int> nums{1, 2, 2, 3, 2};

auto count = my_count(nums.begin(), nums.end(), 2);

std::cout << count;
```

Output:

```text
3
```

---

## Comparison with my_find

### my_find

Stops when the first match is found.

```cpp
if (*first == value)
{
    return first;
}
```

### my_count

Continues traversing the entire range.

```cpp
if (*first == value)
{
    ++count;
}
```

This is why `my_count` always examines every element, while `my_find` may terminate early.

---

## Key Insight

Many STL algorithms follow the same traversal pattern:

```cpp
while (first != last)
{
    // perform operation

    ++first;
}
```

The primary difference between algorithms is the action performed during traversal.

For example:

* `my_find` returns an iterator
* `my_count` increments a counter
* `my_for_each` executes a function
* `my_copy` writes to another range

Understanding this pattern makes STL algorithms easier to learn and implement.

---

## Notes

A more STL-like implementation would use:

```cpp
std::iterator_traits<Iterator>::difference_type
```

instead of `int` for the return type.

This will be explored later when studying `std::iterator_traits`.
