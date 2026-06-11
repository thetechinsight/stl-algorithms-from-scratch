# Iterator Categories

## Input Iterator

Supports:

```cpp
*it
++it
it != other
```

Examples:

- std::forward_list
- std::list
- std::vector

---

## Forward Iterator

Supports:

```cpp
*it
++it
it != other
```

Can traverse a range multiple times.

Examples:

- std::forward_list

---

## Bidirectional Iterator

Supports:

```cpp
--it
```

in addition to Forward Iterator operations.

Examples:

- std::list
- std::set
- std::map

---

## Random Access Iterator

Supports:

```cpp
it + n
it - n
it[n]
it1 < it2
```

Examples:

- std::vector
- std::deque
- std::array

---

## Contiguous Iterator (C++20)

Elements are stored contiguously in memory.

Examples:

- std::vector
- std::array