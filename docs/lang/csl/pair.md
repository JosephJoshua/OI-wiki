author: sbofgayschool

`std::pair` is a class template defined in the standard library. It ties two variables together to form a "pair", and the two variables can have different data types.

??? note "Class templates"
    A class template is not itself a class. It is a "template" that can produce **different classes** for **different data types**.
    
    When you use it, the compiler generates the matching class for the data types you pass in, and then creates the corresponding instance.
    
    Templates are a fairly advanced C++ feature and almost never come up in competitive programming. If you are interested, you can read *C++ Primer* to learn C++ in more depth.

Using `pair` flexibly makes it easy to handle situations where **related data needs to be stored and processed together**.

??? note "Struct"
    Compared with a custom `struct`, `pair` does not require defining a structure or overloading operators, so it is easier to use.
    
    However, the variable names in a custom `struct` are often clearer (`pair` can only use `first` and `second` to access its two variables). Also, if you need to tie together more than two variables, a custom `struct` is more suitable.

## Usage

### Initialization

You can initialize a `pair` directly when defining it.

```cpp
pair<int, double> p0(1, 2.0);
```

You can also define it first and assign values later.

```cpp
pair<int, double> p1;
p1.first = 1;
p1.second = 2.0;
```

You can also use the `std::make_pair` function. It takes two variables and returns a `pair` made of them.

```cpp
pair<int, double> p2 = make_pair(1, 2.0);
```

A common trick is to use the macro `#define mp make_pair` to shorten the rather long `make_pair` to `mp`.

In C++11 and later, `make_pair` can be used with `auto` to avoid declaring the data types explicitly.

```cpp
auto p3 = make_pair(1, 2.0);
```

For using `auto` in competitive programming, see the note in the [Iterators](./iterator.md) section.

### Access

You can access the two variables in a `pair` through its members `first` and `second`.

```cpp
int i = p0.first;
double d = p0.second;
```

You can also modify them.

```cpp
p1.first++;
```

### Comparison

`pair` already defines all comparison operators, including `<`, `>`, `<=`, `>=`, `==`, `!=`. Of course, this requires that the data types of the two variables in the `pair` define the `==` and/or `<` operators.

The four operators `<`, `>`, `<=`, `>=` first compare the first variables of the two `pair`s, and only compare the second variables if the first ones are equal.

```cpp
if (p2 >= p3) {
  cout << "do something here" << endl;
}
```

Since `pair` defines `<` and `==`, which are commonly used in the STL, it works well with other STL functions and data structures. For example, `pair` can be the data type of a `priority_queue`.

```cpp
priority_queue<pair<int, double>> q;
```

### Assignment and swapping

You can assign the value of a `pair` to another `pair` of the same type.

```cpp
p0 = p1;
```

You can also swap the values of `pair`s with the `swap` function.

```cpp
swap(p0, p1);
p2.swap(p3);
```

## Application examples

### Discretization

`pair` makes discretization easy.

We can create an array of `pair`s, using the value of the original data as the first variable of each `pair` and the position of the original data as the second variable. After sorting, assign the rank of each original value (its position after sorting) to the position where that value originally was.

```cpp
// a is the original data
pair<int, int> a[MAXN];
// ai is the data after discretization
int ai[MAXN];
for (int i = 0; i < n; i++) {
  // first is the value of the original data, second is its position
  scanf("%d", &a[i].first);
  a[i].second = i;
}
// Sort
sort(a, a + n);
for (int i = 0; i < n; i++) {
  // Assign the rank of this value to the position where it originally was
  ai[a[i].second] = i;
}
```

### Dijkstra

As mentioned above, `pair` can be the data type of a `priority_queue`.

So in the heap-optimized Dijkstra's algorithm, you can use `pair` and `priority_queue` to maintain nodes, with the node's current distance to the source as the first variable and the node's index as the second variable.

```cpp
priority_queue<pair<int, int>, std::vector<pair<int, int>>,
               std::greater<pair<int, int>>>
    q;
... while (!q.empty()) {
  // dis is the node's distance to the source when it was pushed; i is the node's index
  int dis = q.top().first, i = q.top().second;
  q.pop();
  ...
}
```

### pair and map

`map` is the C++ data structure for storing key-value pairs. In many cases, the key-value pairs stored in a `map` are exposed through `pair`.

```cpp
map<int, double> m;
m.insert(make_pair(1, 2.0));
```

For more about `map`, see the relevant parts of [Associative containers](./associative-container.md) and [Unordered associative containers](./unordered-container.md).
