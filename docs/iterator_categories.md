# Iterator Categories

An iterator is a generalized pointer that allows STL algorithms
to work independently of container type.

## Input Iterator

Supported Operations

- *it
- ++it
- it != other

Examples

- istream_iterator

Used By

- find
- count
- count_if

---

## Forward Iterator

Supported Operations

- Input Iterator operations
- Multiple passes

Examples

- forward_list

---

## Bidirectional Iterator

Supported Operations

- Forward Iterator operations
- --it

Examples

- list
- set
- map

Used By

- reverse

---

## Random Access Iterator

Supported Operations

- Bidirectional Iterator operations
- it + n
- it - n
- it[n]

Examples

- vector
- deque
- array

Used By

- sort
- binary_search