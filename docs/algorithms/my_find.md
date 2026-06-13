# my_find

## STL Equivalent

`std::find`

## Description

Searches for the first occurrence of a value in a range and returns an iterator to it.

If the value is not found, the algorithm returns `last`.

---

## Implementation

```cpp
template<typename Iterator, typename T>
Iterator my_find(Iterator first, Iterator last, const T& value)
{
    while (first != last)
    {
        if (*first == value)
        {
            return first;
        }

        ++first;
    }

    return last;
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

Because only these operations are used, `my_find` works with many container types.

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

In the worst case, every element must be examined.

### Space

`O(1)`

No additional memory is allocated.

---

## Example

```cpp
std::vector<int> nums{1, 2, 3, 4, 5};

auto it = my_find(nums.begin(), nums.end(), 3);

if (it != nums.end())
{
    std::cout << *it << '\n';
}
```

Output:

```text
3
```

---
## Important Insight

Containers provide iterators.

Algorithms consume iterators.

When calling:

```cpp
std::find(v.begin(), v.end(), 3);
```

the algorithm does not know whether it is working with a:

* `std::vector`
* `std::list`
* `std::set`

It only relies on iterator operations.

This separation between containers and algorithms is one of the core ideas behind the STL.

---

## Related Algorithms

* `std::find`
* `std::find_if`
* `std::count`
* `std::count_if`
