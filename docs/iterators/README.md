# Iterators

Iterators are one of the core abstractions of the STL.

An iterator acts like a generalized pointer that allows algorithms to traverse data structures without knowing their internal implementation.

For example, the same `find()` algorithm can work with:

* std::vector
* std::list
* std::deque
* std::set
* std::map
* raw arrays

because the algorithm interacts only with iterators.

```cpp
template<typename Iterator, typename T>
Iterator my_find(Iterator first,
                 Iterator last,
                 const T& value);
```

The algorithm does not need to know the container type. It only requires that the iterator supports the operations needed by the algorithm.

This separation between algorithms and containers is one of the fundamental design principles of the STL.

Topics covered in this section:

* Iterator categories
* iterator_traits
* std::distance
* std::advance
* Tag dispatching
* Iterator requirements of algorithms
* Iterator invalidation
