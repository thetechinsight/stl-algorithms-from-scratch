# Algorithm Requirements

## std::find

Requirements:

```cpp
*it
++it
!=
```

Iterator Category:

- Input Iterator

Complexity:

- O(n)

---

## std::count

Requirements:

```cpp
*it
++it
!=
```

Iterator Category:

- Input Iterator

Complexity:

- O(n)

---

## std::reverse

Requirements:

```cpp
++it
--it
```

Iterator Category:

- Bidirectional Iterator

Complexity:

- O(n)

---

## std::sort

Requirements:

```cpp
it + n
it - n
it1 < it2
```

Iterator Category:

- Random Access Iterator

Complexity:

- O(n log n)