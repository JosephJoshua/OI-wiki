## Categories

![](images/container1.png)

### Sequence containers

-   **Vector** (`vector`): a sequential list that can efficiently add elements at the back.
-   **Array** (`array`) **C++11**: a fixed-length sequential list, a simple wrapper around C-style arrays.
-   **Double-ended queue** (`deque`): a sequential list that can efficiently add elements at both ends.
-   **List** (`list`): a linked list that can be traversed in both directions.
-   **Forward list** (`forward_list`): a linked list that can only be traversed in one direction.

### Associative containers

-   **Set** (`set`): a container that stores **distinct** elements in order. It is implemented as a red-black tree made of nodes; each node holds one element, and nodes are ordered by some predicate that compares elements.
-   **Multiset** (`multiset`): a container that stores elements in order. Equal elements are allowed.
-   **Map** (`map`): a set of {key, value} pairs, ordered by some predicate that compares keys.
-   **Multimap** (`multimap`): a multiset of {key, value} pairs, that is, a map that allows equal keys.

???+ note "What is a [**predicate**](https://en.wikipedia.org/wiki/Predicate_%28mathematical_logic%29)?"
    A predicate is a function that returns true or false. STL containers often use predicates as template parameters.

### Unordered (associative) containers

-   **Unordered (multi)set** (`unordered_set`/`unordered_multiset`) **C++11**: differs from `set`/`multiset` in that elements are not ordered; it only cares about "whether an element exists". It is implemented with hashing.
-   **Unordered (multi)map** (`unordered_map`/`unordered_multimap`) **C++11**: differs from `map`/`multimap` in that keys are not ordered; it only cares about "which value goes with which key". It is implemented with hashing.

### Container adapters

Container adapters are not really containers. They lack some features of containers (such as iterators, a `clear()` function, ...).

> "An adapter is a mechanism that makes one thing behave like another." An adapter wraps a container so that it behaves in a different way.

-   **Stack** (`stack`): a Last In, First Out (LIFO) container; by default a wrapper around a double-ended queue (`deque`).
-   **Queue** (`queue`): a First In, First Out (FIFO) container; by default a wrapper around a double-ended queue (`deque`).
-   **Priority queue** (`priority_queue`): a queue in which the order of elements is decided by some predicate applied to the stored values; by default a wrapper around a vector (`vector`).

## What they have in common

### Declaring containers

They are all declared in the form `containerName<typeName,...> name`, but the number and form of template parameters (the parameters inside `<>`) vary with the container.

The underlying reason: the STL is the "Standard Template Library", so all containers are class templates.

### Iterators

See [Iterators](./iterator.md).

### Common functions

`=`: there is an assignment operator and a copy constructor.

`begin()`: returns an iterator to the first element.

`end()`: returns an iterator to the position just past the last element. `end()` does not point to any element, but it is the successor of the last element.

`size()`: returns the number of elements in the container.

`max_size()`: returns the maximum number of elements the container can **theoretically** hold. It depends on the container type and the type of the stored variables.

`empty()`: returns whether the container is empty.

`swap()`: swaps two containers.

`clear()`: empties the container.

`==`/`!=`/`<`/`>`/`<=`/`>=`: compares two containers in **lexicographic order**. (When comparing elements, each element of a `map` is treated like `set<pair<key, value>>`; unordered containers do not support `<`/`>`/`<=`/`>=`.)
