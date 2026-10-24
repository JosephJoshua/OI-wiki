## `set`

`set` is an associative container that holds a sorted set of objects of the key type. Searching, removal and insertion take logarithmic time. `set` is usually implemented internally as a [red-black tree](../../ds/rbtree.md). The properties of [balanced binary trees](../../ds/bst.md) make `set` well suited to situations that need lookup, insertion and deletion all at once.

Like a set in mathematics, a `set` never contains two elements with the same value. If you need a set with repeated elements, use `multiset`. `multiset` is used in basically the same way as `set`.

### Insertion and deletion

-   `insert(x)` inserts the element x into the `set` when the container has no equivalent element.
-   `erase(x)` deletes **all** elements with value x and returns the number of elements deleted.
-   `erase(pos)` deletes the element at iterator pos; the iterator must be valid.
-   `erase(first,last)` deletes all elements whose iterators are in the range $[first,last)$.
-   `clear()` empties the `set`.

???+ note "Return value of insert"
    The return type of insert is `pair<iterator, bool>`. The iterator points to the inserted element (or to the element already in the container that equals the inserted value), and the bool says whether the insertion succeeded. Since elements in a `set` are unique, if the `set` already has an equal element, the insertion fails and returns false; otherwise it succeeds and returns true. The same holds for insert in `map`.

### Iterators

`set` provides the following iterators:

1.  `begin()/cbegin()`   
    Returns an iterator to the first element, where `*begin = front`.
2.  `end()/cend()`   
    Returns an iterator to the placeholder past the end of the array. Note that there is no element there.
3.  `rbegin()/crbegin()`   
    Returns a reverse iterator to the first element of the reversed array, which you can think of as the last element of the container in forward order.
4.  `rend()/crend()`   
    Returns an iterator to the position after the last element of the reversed array, which corresponds to the position before the start of the container; there is no element there.

Among the iterators above, those with the letter `c` are read-only iterators. You cannot change the values of elements in a `set` through a read-only iterator. If a `set` is itself read-only, its ordinary iterators and read-only iterators are exactly the same. Read-only iterators are supported since C++11.

### Lookup

-   `count(x)` returns the number of elements with key x in the `set`.
-   `find(x)` returns an iterator to the element with key x if there is one in the `set`; otherwise it returns `end()`.
-   `lower_bound(x)` returns an iterator to the first element that is not less than the given key. If there is no such element, it returns `end()`.
-   `upper_bound(x)` returns an iterator to the first element greater than the given key. If there is no such element, it returns `end()`.
-   `empty()` returns whether the container is empty.
-   `size()` returns the number of elements in the container.

???+ warning "Time complexity of `lower_bound` and `upper_bound`"
    The member functions `lower_bound` and `upper_bound` of `set` run in $O(\log n)$ time.
    
    But using the `lower_bound` and `upper_bound` functions from the `algorithm` library to query elements of a `set` takes $O(n)$ time.

???+ warning "Time complexity of `nth_element`"
    `set` has no built-in `nth_element`. Using `nth_element` from the `algorithm` library to find the $k$-th largest element takes $O(n)$ time.
    
    If you need the $O(\log n)$ "find the $k$-th largest element" operation that a balanced binary tree provides, you have to write a balanced binary tree or a value-indexed segment tree yourself, or use the balanced binary tree in the pb\_ds library.

### Usage examples

#### Using `set` in greedy algorithms

Greedy algorithms often need something like **find and delete the smallest element that is greater than or equal to some value**. This is easy to do with `set`.

```cpp
// Elements currently available
set<int> available;
// The value the element must be greater than or equal to
int x;

// Find the smallest element that is >= x
set<int>::iterator it = available.lower_bound(x);
if (it == available.end()) {
  // No such element; handle this case...
} else {
  // Found such an element; remove it from the available elements
  available.erase(it);
  // Do the corresponding work...
}
```

## `map`

`map` is a sorted container of key-value pairs, and the keys of its elements are unique. Search, removal and insertion take logarithmic time. `map` is usually implemented as a [red-black tree](../../ds/rbtree.md).

Imagine this situation: you need to store some key-value pairs, such as students' names and their scores: `Tom 0`, `Bob 100`, `Alan 100`. Array indices can only be non-negative integers, so you cannot use names as indices. The simplest solution here is the STL `map`.

`map` overloads `operator[]`, so you can use any type that defines `operator <` as the index (in a `map` this is called the `key`, i.e. the index):

```cpp
map<Key, T> yourMap;
```

Here `Key` is the type of the key and `T` is the type of the value. Here is an example of using `map`:

```cpp
map<string, int> mp;
```

A `map` never has two elements with the same key, while a `multimap` allows several elements to share a key. `multimap` is used in basically the same way as `map`.

??? warning "Warning"
    Precisely because `multimap` allows several elements to share a key, `multimap` does not provide a way to access the value for a given key.

### Insertion and deletion

-   You can query or insert directly through subscript access, for example `mp["Alan"]=100`.
-   You can also insert an element by inserting a value of type `pair<Key, T>` into the `map`, for example `mp.insert(pair<string,int>("Alan",100));`.
-   The `erase(key)` function deletes **all** elements with key `key`. It returns the number of elements deleted.
-   `erase(pos)`: deletes the element at iterator pos; the iterator must be valid.
-   `erase(first,last)`: deletes all elements whose iterators are in the range $[first,last)$.
-   The `clear()` function empties the whole container.

???+ note "Things to watch for with subscript access"
    When you access an element of a `map` by subscript and the `map` has no element with that key, a new element is automatically inserted into the `map` with a default value (zero for integers; for types with a default constructor, the default constructor is called to initialize it).
    
    If you use subscript access too often, the container fills up with many meaningless elements, which hurts the efficiency of the `map`. So in general it is better to use the `find()` function to look for an element with a specific key.

### Queries

-   `count(x)`: returns the number of elements with key x in the container. The complexity is $O(\log(size)+ans)$ (logarithmic in the container size, plus the number of matches).
-   `find(x)`: if the container has an element with key x, returns an iterator to it; otherwise returns `end()`.
-   `lower_bound(x)`: returns an iterator to the first element that is not less than the given key.
-   `upper_bound(x)`: returns an iterator to the first element greater than the given key. If all elements in the container are less than or equal to the given key, returns `end()`.
-   `empty()`: returns whether the container is empty.
-   `size()`: returns the number of elements in the container.

### Usage examples

#### Using `map` to store complex states

In search, we sometimes need to store fairly complex states (such as coordinates, values that cannot be discretized, strings, etc.) together with related answers (such as the minimum number of steps to reach the state). `map` can do this: the key is the state and the value is the related answer. The example below shows how to use `map` to store states represented as `string`.

```cpp
// Store states and their answers
map<string, int> record;

// A newly found state and its answer
string status;
int ans;
// Check whether this state has appeared before
map<string, int>::iterator it = record.find(status);
if (it == record.end()) {
  // This state has not been searched yet; add it to the record
  record[status] = ans;
  // Do the corresponding work...
} else {
  // This state has already been searched; do the corresponding work...
}
```

## Traversing a container

You can use iterators to traverse all elements of an associative container.

```cpp
set<int> s;
using si = set<int>::iterator;
for (si it = s.begin(); it != s.end(); it++) cout << *it << endl;
```

Note that dereferencing an iterator of a `map` gives a key-value pair of type `pair<Key, T>`.

In C++11, a range-based for loop makes the code much shorter:

```cpp
set<int> s;
for (auto x : s) cout << x << endl;
```

For any associative container, traversing it with iterators takes $O(n)$ time.

## Custom comparison

By default, the comparison function of a `set` is `<` (for non-built-in types you need to [overload the `<` operator](../op-overload.md#comparison-operators)). In some special cases, however, we want to customize how the `set` compares elements internally.

You can solve this by passing in a custom comparator.

Specifically, we define a class and [overload the `()` operator](../op-overload.md#the-function-call-operator) in it.

For example, to keep a `set` of integers with larger values first, you can write:

```cpp
struct cmp {
  bool operator()(int a, int b) const { return a > b; }
};

set<int, cmp> s;
```

For other associative containers, custom comparison works in a similar way, so we won't repeat it here.
