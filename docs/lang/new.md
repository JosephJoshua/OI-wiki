**Note**: Given what actually matters in competitive programming, this article does not cover the full syntax. It only describes the parts you are likely to use in contests.

The syntax in this article follows the **C++11** standard. Where semantics differ, **C++11** is taken as the standard. Syntax from C++14, C++17 and so on is mentioned where relevant and clearly marked.

## The `auto` type specifier

The `auto` type specifier deduces the type of a variable (and other things) automatically. For example:

```cpp
auto a = 1;        // a has type int
auto b = a + 0.1;  // b has type double
```

Note that `auto` drops references. If you want to avoid the cost of a copy, you need to say so explicitly:

```cpp
int a = 1;
int& b = a;
auto c = b;   // c has type int; there is a copy cost
auto& e = a;  // e has type int&; no copy cost
```

## The decltype specifier

`decltype` can deduce a type from an **entity** or from an **expression**. Note that the two are deduced in different ways, and using them wrongly can create dangling references. It is rarely used in contests, so we only give a rough introduction here.

```cpp
#include <iostream>
#include <vector>

int main() {
  int a = 1926;
  decltype(a) b;                 // deduced from an entity; b has type int
  decltype(1 + 1) c;             // deduced from an expression; c has type int
  decltype((a)) d = a;           // deduced from an expression; d has type int&!
  std::vector<decltype(b)> vec;  // deduced from an entity; vec has type std::vector <int>
  return 0;
}
```

## constexpr

> See also [Constant expressions: constexpr (C++11)](const.md#constant-expressions-constexpr-c11)

## Range-based `for` loops

Iterating over an iterable object with a range-based for is as efficient as iterating with iterators. Both are usually more efficient than iterating by index, since they don't need to compute an address from the index.

Here is a simple form of the range-based `for` loop syntax:

```cpp
for (item_declaration : range_initializer) statement
```

For example:

```cpp
std::array<int, 4> arr = {1, 2, 3, 4};
for (int x : arr) {
  std::cout << x << std::endl;
}
```

The code above has the same effect as the following:

```cpp
std::array<int, 4> arr = {1, 2, 3, 4};
for (auto px = arr.begin(), ed = arr.end(); px != ed; ++px) {
  std::cout << *px << std::endl;
}
```

### item-declaration: item declaration

This declares a variable that receives the elements of the container on the right. The variable's type must match the type of the container's elements. You can use `auto` to deduce the type; for complex types, `auto&` is often used to avoid the cost of copying.

### range-initializer: range initializer

The range initializer can be any iterable object (such as an array, or an object of a class that defines `begin` and `end` member functions). If you put an expression here, the expression is evaluated only once.

Example:

```cpp
int a[] = {1, 1, 4, 5, 1, 4};
std::vector<int> b{1, 1, 4, 5, 1, 4};
std::map<std::string, int> c{{"114", 114}, {"514", 514}};
for (int i : a) std::cout << i;
for (auto i : b) std::cout << i;
// below, i has type std::pair<const std::string, int>&
for (auto& i : c) std::cout << i.first << i.second;
for (auto i : {1, 1, 4, 5, 1, 4}) std::cout << i;
```

### Supporting range-based for in your own types

You only need to provide `begin` and `end` member functions. Their return type must support comparison, increment and dereference (the `*` operator).

Here is an example:

```cpp
#include <iostream>

struct C {
  int a[4];

  int* begin() { return a; }

  int* end() { return a + 4; }
};

int main() {
  C c = {1, 9, 2, 6};
  for (auto i : c) std::cout << i << " ";
  std::cout << std::endl;
  // output: 1 9 2 6
  return 0;
}
```

### Init-statement (C++20)

In C++20 you can also use an init-statement for things like a loop counter:

```cpp
#include <iostream>
#include <vector>

int main() {
  std::vector<int> v = {0, 1, 2, 3, 4, 5};

  for (int counter = 0; auto i : v)  // the init-statement (C++20)
    std::cout << counter++ << ' ' << i << std::endl;
}
```

## Structured bindings (C++17)

A structured binding is a piece of syntactic sugar in C++17 that makes it easy to extract sub-elements, or references to them, like this:

```cpp
struct C {
  int x{1}, y{2};
};

int arr[]{4, 5, 6};

auto [c1, c2] = C{};       // c1=1,c2=2; type int
auto& [a1, a2, a3] = arr;  // a1=arr[0],a2=arr[1],a3=arr[2]; type int&
```

Keep the following in mind:

-   The number of variables declared on the left must equal the number of sub-elements of the object on the right
-   The type must be declared with `auto`
-   You can add `&` to get references

You can write this when iterating over a `map` container:

```cpp
std::map<std::string, int> m = {{"k1", 1}, {"k2", 2}};

// using "auto&", no copy cost
for (auto& [k, v] : m) {
  // k has type const std::string&, since keys are already const
  // v has type int&
  std::cout << k << ' ' << v << std::endl;
}
```

## std::tuple

A [tuple](https://zh.cppreference.com/w/cpp/utility/tuple) is defined in the header `<tuple>`. It generalizes `std::pair` and can store several values of different types. Here is an example:

```cpp
#include <iostream>
#include <tuple>
#include <vector>

constexpr auto expr = 4 - 1;  // expr = 3

int main() {
  std::vector<int> vec = {1, 9, 2, 6, 0};
  std::tuple<int, int, std::string, std::vector<int>> tup =
      std::make_tuple(817, 114, "514", vec);

  // use get<> to get a sub-element; the value in the angle brackets must be an integral constant expression
  for (auto i : std::get<expr>(tup)) std::cout << i << " ";
  // the first element is numbered 0, so std::get<3> gives us a std::vector<int>
  return 0;
}
```

Since C++17, you can use structured bindings to extract the values, like this:

```cpp
std::vector<int> vec = {1, 9, 2, 6, 0};
std::tuple<int, int, std::string, std::vector<int>> tup =
    std::make_tuple(817, 114, "514", vec);

auto& [a, b, c, d] = tup;  // C++17 Structured binding
std::cout << a << ' ' << b << c << std::endl;
std::cout << d.size() << ' ' << d[2] << std::endl;
```

### Member functions

| Function    | Purpose                                      |
| ----------- | -------------------------------------------- |
| `operator=` | Assigns the contents of one `tuple` to another |
| `swap`      | Swaps the contents of two `tuple`s           |

Example:

```cpp
constexpr std::tuple<int, int> tup = {1, 2};
std::tuple<int, int> tupA = {2, 3}, tupB;
tupB = tup;
tupB.swap(tupA);
```

### Non-member functions

| Function            | Purpose                                                              |
| ------------------- | -------------------------------------------------------------------- |
| `make_tuple`        | Creates a `tuple` object whose type is determined by the argument types |
| `std::get`          | Tuple-style access to a given element                                |
| `std::tie`          | Assigns the values in a tuple to existing variables                  |
| `operator==` etc.   | Compares the values in `tuple`s lexicographically                    |
| `std::swap`         | Specialization of the `std::swap` algorithm                          |

Example:

```cpp
std::tuple<int, int> tupA = {2, 3}, tupB;
tupB = std::make_tuple(1, 2);
std::swap(tupA, tupB);
std::cout << std::get<1>(tupA) << std::endl;
int x;
std::tie(x, std::ignore) = tupB;
std::cout << x << std::endl;
```

`std::tie` assigns tuple elements to existing variables, and you can use `std::ignore` to skip elements you don't need. A structured binding declares new variables directly (by value or by reference) and must take all the elements.

## Function objects

An object that can be used with the function call operator `operator()` is called a function object (FunctionObject).

It is not a language feature but a [concept, or requirement](https://zh.cppreference.com/w/cpp/named_req/FunctionObject), and it is used widely in the standard library.

Function objects fall roughly into two kinds:

1.  Function pointers
2.  Objects of classes that overload `operator()`

A [lambda](./lambda.md) is a typical function object of the second kind. It stores what it captures in member variables and overloads the function call operator.

## Lambda expressions

> See the [Lambda expressions](lambda.md) page.

## std::function

???+ warning "Watch out for the performance cost"
    `std::function` adds some performance overhead. In [benchmarks](./lambda.md#recursion-in-lambdas), it usually makes code 2 to 3 times slower or worse.
    
    This is because it uses type erasure, which is usually implemented with virtual functions, and calling a virtual function adds extra [overhead](https://stackoverflow.com/questions/5057382/what-is-the-performance-overhead-of-stdfunction).
    
    Consider using a [**lambda expression**](./lambda.md) or a [**function object**](#function-objects) instead.

`std::function` is a general-purpose function wrapper, defined in the header `<functional>`.

An instance of `std::function` can store, copy and call any [**callable**](https://zh.cppreference.com/w/cpp/named_req/Callable) object, including [**lambda expressions**](./lambda.md), pointers to member functions, and other [**function objects**](#function-objects).

If a `std::function` holds no callable object (for example, when it is default-constructed), calling it throws a [`std::bad_function_call`](https://zh.cppreference.com/w/cpp/utility/functional/bad_function_call) exception.

```cpp
#include <functional>
#include <iostream>

struct Foo {
  Foo(int num) : num_(num) {}

  void print_add(int i) const { std::cout << num_ + i << '\n'; }

  int num_;
};

void print_num(int i) { std::cout << i << '\n'; }

struct PrintNum {
  void operator()(int i) const { std::cout << i << '\n'; }
};

int main() {
  // store a free function
  std::function<void(int)> f_display = print_num;
  f_display(-9);

  // store a lambda
  std::function<void()> f_display_42 = []() { print_num(42); };
  f_display_42();

  // store a call to a member function
  std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;
  const Foo foo(314159);
  f_add_display(foo, 1);
  f_add_display(314159, 1);

  // store a call to a data member accessor
  std::function<int(Foo const&)> f_num = &Foo::num_;
  std::cout << "num_: " << f_num(foo) << '\n';

  // store a call to a function object
  std::function<void(int)> f_display_obj = PrintNum();
  f_display_obj(18);
}
```

## Variadic function templates

Before C++11, class templates and function templates could only take a fixed number of template parameters. C++11 allows template parameters of **any number and any type**.

Here we only briefly introduce variadic **function** templates.

The function template `fun` declared below can take any number of template arguments of any type as its template parameters.

```cpp
template <typename... Clazz>
void fun(Clazz... paras) {}
```

`paras` is a function parameter pack, which accepts zero or more function arguments. `Clazz` is a template parameter pack, which accepts zero or more template arguments (non-types, types or templates); when marked with `typename`, it only accepts types.

You can think of it simply like this:

-   A template parameter pack is usually a list of type names (but it can also hold compile-time constants or template names)
-   A function parameter pack is usually a list of variable names

Now you can call `fun` like this:

```cpp
fun();
fun(1);
fun(1, 2, 3);
fun(1, 0.0, "abc");
```

### Pack expansion

#### Pack expansion syntax

Expanding a pack is very simple: just use `...`, and the elements are automatically separated by `,`. For example:

```cpp
template <class A, class... C>
void func(A arg1, C... arg2) {
  // C is a template parameter pack
  tuple<A, C...>();  // expands to tuple<int, int, double, bool>();

  // arg2 is a function parameter pack
  func(arg2...);  // expands to func( 2, 1.1, true );
}

func(1, 2, 1.1, true);
```

You can also apply an operation while expanding a pack, for example:

```cpp
template <class A, class... C>
void func(A arg1, C... arg2) {
  func((arg2 + 1)...);
  // expands to func( (2+1) , (1.1+1), (2.1f+1) );
}

func(1, 2, 1.1, 2.1f);
```

#### Terminating function

The function above cannot work: the number of arguments keeps shrinking until there are none, and then there is an error.

We need a stopping condition. We can provide an ordinary function, like this:

```cpp
void func() {}

template <class A, class... C>
void func(A arg1, C... arg2) {
  std::cout << arg1 << std::endl;
  func((arg2 + 1)...);
}

func(1, 2, 1.1, 2.1f);
```

Now, when there is at least one argument the template is called, and with no arguments the ordinary function is called, so it works.

### Fold expressions (C++17)

C++17 provides a convenient syntax for working with **function parameter packs**. Its syntax is as follows (it must be wrapped in parentheses):

1.  `( pack op ... )` becomes `(E1 op (... op (EN-1 op EN)))`
2.  `( ... op pack )` becomes `(((E1 op E2) op ...) op EN)`
3.  `( pack op ... op init )` becomes `(E1 op (... op (EN−1 op (EN op I))))`
4.  `( init op ... op pack )` becomes `((((I op E1) op E2) op ...) op EN)`

A short demo makes it easy to understand:

```cpp
template <class... C>
void func(C... args) {
  (std::cout << ... << args) << std::endl;
  // form 4, equivalent to ↓
  // ( ( ( std::cout << 1 ) << 2.1 ) << true ) << std::endl;
  // output: 12.11  note that true is printed as 1, since boolalpha is not set here

  std::cout << (args && ...) << std::endl;
  // form 1, equivalent to ↓
  // std::cout << ( 1 && ( 2.1 && true ) ) ) << std::endl;
  // output: 1
}

func(1, 2.1, true);
```

### Abbreviated function templates (C++20)

Since C++20 you can use `auto ...` directly as a parameter type, which gives a shorthand for function templates:

```cpp
void func(auto... args) { (std::cout << ... << args) << std::endl; }
```

Note that this is still a function template. It is equivalent to:

```cpp
template <class... T>
void func(T... args) {
  (std::cout << ... << args) << std::endl;
}
```

## Ranges library (C++20)

> The ranges library is an extension of the iterator and generic algorithm libraries. It makes iterators and algorithms more powerful by letting you compose them, and less error-prone.

A range is a sequence you can iterate over, including arrays, containers, views and so on.

When you need to do complex operations on ranges such as containers, the [ranges library](https://zh.cppreference.com/w/cpp/ranges) makes writing algorithms easier and clearer.

### Views

A view is a lightweight object that implements some algorithm through a particular mechanism (such as a custom iterator), giving a range more ways to be traversed.

The ranges library already implements some common views. They fall roughly into two kinds:

1.  **Range factories**, which build special ranges. Using a factory saves you from building a container by hand, lowers the cost, and produces a range directly.
2.  **Range adaptors**, which provide many kinds of traversal. They can be called like functions, or joined with the pipe operator `|` to form a chain of calls.

As [**range adaptor closure objects**](https://zh.cppreference.com/w/cpp/named_req/RangeAdaptorClosureObject), **range adaptors** are also [**function objects**](#function-objects). They overload `operator|` so they can be put together like a pipeline.

??? note "The pipe operator"
    Here `|` should be read as the pipe operator, not the bitwise OR operator. This usage comes from the [pipe](https://zh.wikipedia.org/wiki/%E7%AE%A1%E9%81%93_%28Unix%29) in Linux.

Even with complex operations, the code stays readable. It has the following property:

If A, B and C are range adaptor closure objects, R is a range, and the other letters are possible valid arguments, then the expression

    R | A(a) | B(b) | C(c, d)

is equivalent to

    C(B(A(R, a), b), c, d)

Below we use `ranges::take_view` and `ranges::iota_view` as an example:

```cpp
#include <iostream>
#include <ranges>

int main() {
  const auto even = [](int i) { return 0 == i % 2; };

  for (int i : std::views::iota(0, 6) | std::views::filter(even))
    std::cout << i << ' ';
}
```

1.  The range factory `std::views::iota(0, 6)` produces a range of the integers from 0 to 5
2.  The range adaptor `std::views::filter(even)` filters the previous range, producing a range of only the even numbers
3.  The two operations are joined with the pipe operator

The code above does not need to allocate extra heap space to store the range produced at each step. The actual generating and filtering happens during iteration (more precisely, in the construction, increment and dereference of the internal iterators). In other words, it has zero overhead.

At the same time, the lifetime of the outside range passed in is the lifetime of the elements inside the **range adaptor**. If the outside range (such as a container or a range factory) has already been destroyed, iterating over views of it has the same effect as dereferencing a dangling pointer, which is undefined behavior.

To avoid this, make sure an adaptor's lifetime always lies within the lifetime of every range it uses.

???+ note "When the range is destroyed, all elements in the view dangle"
    ```cpp
    #include <iostream>
    #include <ranges>
    #include <vector>
    
    using namespace std;
    
    int main() {
      auto view = [] {
        vector<int> vec{1, 2, 3, 4, 5};
        return vec | std::views::filter([](int i) { return 0 == i % 2; });
      }();
    
      for (int i : view) cout << i << ' ';  // runtime undefined behavior
    
      return 0;
    }
    ```

### Constrained algorithms

> C++20 provides constrained versions of most algorithms in the namespace std::ranges. You can specify a range with either an iterator-sentinel pair or a single range argument, and projections and pointer-to-member callables are supported. The return types of most algorithms were also changed to return all potentially useful information computed while the algorithm runs.

You can think of these algorithms as improved versions of the old standard library algorithms. They are all function objects and provide friendlier overloads and argument type checking (based on [`concept`](https://zh.cppreference.com/w/cpp/language/constraints)). Let's start by comparing `std::sort` and `ranges::sort`:

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> vec{4, 2, 5, 3, 1};

  sort(vec.begin(), vec.end());  // {1, 2, 3, 4, 5}

  for (const int i : vec) cout << i << ", ";
  cout << '\n';

  ranges::sort(vec, ranges::greater{});  // {5, 4, 3, 2, 1}

  for (const int i : vec) cout << i << ", ";

  return 0;
}
```

`ranges::sort` uses the same algorithm as `sort`, but it offers a range-based overload that makes passing arguments simpler. Most other algorithms in the `std` namespace also have range overloads in the `ranges` namespace.

Using these range arguments together with the views from the previous section lets us do complex operations while keeping the code readable. Let's look at an example:

```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <ranges>

using namespace std;

int main() {
  const auto& inputs = views::iota(0u, 9u);  // produce the integers 0 to 8
  const auto& chunks = inputs | views::chunk(3);  // split the sequence into chunks of 3 elements
  const auto& cartesian_product =
      views::cartesian_product(chunks, chunks);  // take the Cartesian product of the chunks with themselves

  for (const auto [l_chunk, r_chunk] : cartesian_product)
    // compute the sum of the integers in the two chunks of each pair in the product
    cout << ranges::fold_left(l_chunk, 0u, plus{}) +
                ranges::fold_left(r_chunk, 0u, plus{})
         << ' ';
}
```

???+ note "Output:"
    6 15 24 15 24 33 24 33 42

## References

1.  [C++ reference](https://zh.cppreference.com/)
