# STL Containers

## Overview

Containers are one of the three fundamental components of the Standard Template Library (STL).

The STL is built around:

```text
Containers
Iterators
Algorithms
```

Containers store data.

Iterators provide access to data.

Algorithms operate on iterators.

Together, these three components form the foundation of generic programming in C++.

---

# Learning Objectives

After completing this module, you should be able to:

* Explain what an STL container is
* Understand the different container categories
* Choose the appropriate container for a given problem
* Understand the strengths and weaknesses of each container
* Explain iterator support for different containers
* Understand container adapters
* Analyze container complexity characteristics
* Answer common STL container interview questions

---

# What Is a Container?

A container is an object that stores and manages a collection of other objects.

Examples:

```cpp
std::vector<int>
std::list<std::string>
std::set<int>
std::map<int, std::string>
```

Containers provide:

* Storage
* Memory management
* Element access
* Iteration support

Containers hide implementation details and provide a consistent interface to users and algorithms.

---

# Why Does STL Have Many Containers?

Different applications have different requirements.

Sometimes we need:

```text
Fast random access
```

Sometimes we need:

```text
Fast insertion and removal
```

Sometimes we need:

```text
Automatic sorting
```

Sometimes we need:

```text
Fast key-based lookup
```

No single container can optimize all operations simultaneously.

The STL therefore provides multiple container types, each optimized for different use cases.

---

# Container Classification

STL containers are grouped into three major categories:

```text
Containers
│
├── Sequence Containers
├── Associative Containers
└── Unordered Associative Containers
```

Additionally, STL provides:

```text
Container Adapters
```

which build specialized behavior on top of existing containers.

---

# Sequence Containers

Sequence containers store elements in a linear sequence.

Examples:

```cpp
std::vector
std::deque
std::list
std::forward_list
```

Characteristics:

* Preserve insertion order
* Allow traversal through iterators
* Different performance trade-offs

---

# Associative Containers

Associative containers organize elements according to keys.

Examples:

```cpp
std::set
std::multiset
std::map
std::multimap
```

Characteristics:

* Automatically sorted
* Fast searching
* Usually implemented as balanced trees

---

# Unordered Associative Containers

Unordered containers organize elements using hash tables.

Examples:

```cpp
std::unordered_set
std::unordered_map
```

Characteristics:

* No ordering guarantee
* Very fast average lookup
* Hash-based implementation

---

# Container Adapters

Container adapters provide specialized interfaces built on top of existing containers.

Examples:

```cpp
std::stack
std::queue
std::priority_queue
```

Characteristics:

* Restrict container operations
* Provide specialized behavior
* Built using underlying containers

---

# STL Container Hierarchy

```text
Containers
│
├── Sequence Containers
│   ├── vector
│   ├── deque
│   ├── list
│   └── forward_list
│
├── Associative Containers
│   ├── set
│   ├── multiset
│   ├── map
│   └── multimap
│
├── Unordered Associative Containers
│   ├── unordered_set
│   └── unordered_map
│
└── Container Adapters
    ├── stack
    ├── queue
    └── priority_queue
```

---

# Relationship with Iterators

Every STL container provides iterators.

Algorithms operate on iterators rather than directly on containers.

Example:

```cpp
std::find(
    container.begin(),
    container.end(),
    value);
```

This design allows algorithms to work with many container types without modification.

---

# Learning Roadmap

## Part 1: Container Fundamentals

* Container Overview
* Sequence Containers
* Associative Containers
* Unordered Containers
* Container Selection Guide

## Part 2: Sequence Containers

* vector
* deque
* list
* forward_list

## Part 3: Associative Containers

* set
* multiset
* map
* multimap

## Part 4: Unordered Containers

* unordered_set
* unordered_map

## Part 5: Container Adapters

* stack
* queue
* priority_queue

## Part 6: Practical Knowledge

* Container Complexities
* Container Interview Questions

---

# Interview Focus

Common interview topics covered in this module:

* vector vs deque
* vector vs list
* map vs unordered_map
* set vs unordered_set
* Why does std::list not support random access?
* Why does std::sort require random access iterators?
* Which container should be chosen for a specific problem?
* Complexity analysis of common operations
* Container adapter internals

---

# Current Status

```text
Containers Module

□ Fundamentals
□ Sequence Containers
□ Associative Containers
□ Unordered Containers
□ Container Adapters
□ Complexity Analysis
□ Interview Preparation
```

---

# References

Primary Reference:

* Nicolai M. Josuttis

  * The C++ Standard Library

Additional References:

* cppreference.com
* Effective STL
* libstdc++
* libc++
* MSVC STL
