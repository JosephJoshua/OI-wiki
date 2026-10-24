**Note**: Given what actually matters in competitive programming, this article does not cover the full syntax. It only describes the parts you are likely to use in contests.

The syntax in this article follows the **C++11** standard. Syntax from newer standards is mentioned where relevant and clearly marked.

## Lambda expressions

Lambda expressions are named after the $\lambda$ calculus in mathematics and correspond directly to its lambda abstraction. At compile time, the compiler uses the syntax to generate an anonymous [**function object**](./new.md#函数对象). The captured variables become its members, and the parameters and function body are used to implement the `operator()` overload.

??? note "Function object"
    A function object is an object of a class, usually made by overloading `operator()`, so it can be called like a function. Compared with ordinary functions, function objects have many advantages. For example, they can store state, and they can be passed as arguments to other functions.

Here is one form of the lambda syntax:

```text
[capture] (parameters) mutable -> return-type {statement}
```

A lambda expression is itself a class. Expanded, it looks like this:

<!-- scripts.linter.preprocess.fix_details off -->

```text
class Lambda_1 {
 private:
  Lambda_1() : capture-list(init-value) { }

 public:
  return-type operator()(parameters) const { statement }

 private:
  mutable capture-list
};
```

<!-- scripts.linter.preprocess.fix_details on -->

A lambda with an empty capture can be implicitly converted to a function pointer, for example:

```cpp
void (*f)(int, int) = [](int, int) -> void {};
```

Below we introduce each part of the syntax in turn.

### statement: function body

The body of a lambda expression is like the body of an ordinary function. Besides parameters, global variables and so on, it can also access [captured](#capture-capture-clause) variables.

### capture: capture clause

A lambda starts with the capture clause, which says which variables are captured. The capture list can be empty, or it can say how each variable is captured: a variable prefixed with `&` is accessed by [reference](./reference.md), and one without the prefix is accessed by value.

We can also use a default capture mode, which captures every variable mentioned in the lambda: `&` means all captured variables are accessed by reference, and `=` means all captured variables are accessed by value.

After the default capture, you can still **explicitly** give a capture mode for specific variables.

If you want to access the outer variable `a` by reference and the outer variable `b` by value, any of the following capture clauses works:

-   `[&a, b]`
-   `[b, &a]`
-   `[&, b]`
-   `[b, &]`
-   `[=, &a]`

The capture list can also declare variables. Their types are deduced from the initializer, much like declaring a variable with `auto`.

Here are some common examples:

```cpp
int a = 0;
auto f0 = []() { return a * 9; };   // Error, cannot access 'a'
auto f1 = [a]() { return a * 9; };  // OK, 'a' is "captured" by value
auto f2 = [&a]() { return a++; };   // OK, 'a' is "captured" by reference
auto f3 = [v = a + 1]() {
  return v + 1;
};  // OK, declares variable v with an initializer; its type is the same as a

// Note: when capturing by reference, make sure a has not been destroyed when the lambda is called
auto b = f2();  // f2 gets the value of a from its capture list; no need to pass a as an argument
```

#### generalized capture: capture with an initializer (C++14)

Since C++14, the capture can not only capture outer variables but also declare and initialize new variables, for example:

```cpp
auto f1 = [val = 520]() {
  return val;
};  // OK, val has type int, initial value 520; return type int

auto f2 = [val = 520LL]() {
  return val;
};  // OK, val has type long long, initial value 520; return type long long

auto f3 = [val = "520"]() {
  return val;
};  // OK, val has type const char*, initial value "520"; return type const char*

auto f4 = [val = "520"s]() {
  return val;
};  // OK, since C++14; needs using namespace std; or using namespace std::literals;
    // val has type std::string, initial value std::string("520"); return type
    // std::string

auto f5 = [val = std::string("520")]() {
  return val;
};  // OK, val has type std::string, initial value std::string("520"); return type
    // std::string

auto f6 = [val = std::vector<int>(3, 6)]() {
  return val;
};  // OK, val has type std::vector<int>, size 3, filled with 6; return type
    // std::vector<int>

auto f7 = [val = 520]() -> int {
  return val;
};  // OK, val has type int, initial value 520; return type int

auto f8 = [val = 520]() -> long long {
  return val;
};  // OK, val has type int, initial value 520; return type long long
```

When defining a new variable, you cannot leave out the initial value. The variable's type is determined by the type of the initial value. It is equivalent to:

```text
auto val = init-value;
```

The following is wrong:

```cpp
auto f = [val]() { return val; };  // Error: 'val' was not declared in this
                                   // scope, identifier "val" is undefined
```

The initial value can also be an outer variable, for example:

```cpp
int value = 520;
auto f = [val = value]() { return val; };
std::cout << f();  // Output: 520
```

`val` can also be a reference type that refers to an outer variable. This way you can give an alias to an outer variable captured by reference, for example:

```cpp
int value = 520;

auto f = [&val = value]() {
  return val;
};  // OK, val has type int&, return type int; equivalent to int& val = value;

std::cout << f() << '\n';  // Output: 520

value = 1314;

std::cout << f() << '\n';  // Output: 1314
```

You can capture outer variables and define new variables at the same time.

If you want to modify a new variable defined in the capture inside the lambda body, you need the `mutable` keyword. References don't need it. For example:

```cpp
int value = 520;

{
  auto f = [val = value]() mutable -> int {
    return val = 1314;
  };  // needs mutable
  auto val_f = f();
  std::cout << value << ' ' << val_f << std::endl;  // Output: 520 1314
}

{
  auto f = [&val = value]() -> int { return val = 1314; };  // no mutable needed
  auto val_f = f();
  std::cout << value << ' ' << val_f << std::endl;  // Output: 1314 1314
}
```

See [mutable specification](#mutable-mutable-specification) for details.

A variable defined in the capture lives as long as the object that receives the lambda expression, which is the variable $f$ in the examples above. This is because a lambda is really a class, and everything in the capture is a `private` member variable of that class, for example:

```cpp
int main() {
  auto f = [val = 0]() mutable -> int { return ++val; };  // val is constructed and initialized

  std::cout << f() << '\n';  // Output: 1
  std::cout << f() << '\n';  // Output: 2
  std::cout << f() << '\n';  // Output: 3
}  // val is destroyed along with f
```

### parameters: parameter list

In most cases this is just like a function's parameter list, for example:

```cpp
int x[] = {5, 1, 7, 6, 1, 4, 2};
std::sort(x, x + 7, [](int a, int b) { return (a > b); });
for (auto i : x) std::cout << i << " ";
```

This prints the array `x` sorted from largest to smallest.

Since the **parameter list** is optional, you can leave out the empty parentheses if the lambda takes no arguments, its declaration does not contain [mutable](#mutable-mutable-specification), and it has no trailing return type.

??? note "Parameters declared with `auto`"
    Since **C++14**, if a parameter's type is declared with `auto`, you get a [generic lambda expression](#generic-lambdas-c14).

#### Explicit object parameter (C++23)

Since **C++23**, an [explicit object parameter](https://zh.cppreference.com/w/cpp/language/function#.E5.BD.A2.E5.8F.82.E5.88.97.E8.A1.A8) can be used in a lambda's parameters.

```cpp
auto nth_fibonacci = [](this auto self, unsigned n) -> unsigned {
  return n < 2 ? n : self(n - 1) + self(n - 2);
};

cout << nth_fibonacci(10u);
```

### mutable: mutable specification

It lets the function body modify variables captured by value.

```cpp
int a = 0;
auto by_value = [a]() mutable { ++a; };
auto by_ref = [&a] { ++a; };

by_value();
by_ref();
```

After `by_value()` runs, the captured member `a` of `by_value` is 1, but the outer variable `a` is still 0.
After `by_ref()` runs, the outer `a` becomes 1.

### return-type: return type

This specifies the return type of the lambda expression. If it is omitted, the return type is deduced automatically (the same way as for a function whose return type is declared with `auto`).

If there are several `return` statements and their deduced types don't match, you get a compile error.

```cpp
auto lam = [](int a, int b) -> int { return 0; };

auto x1 = [](int i) { return i; };

auto x2 = [](bool condition) {
  if (condition) return 1;
  return 1.0;
};  // Error, deduced types don't match
```

### Generic lambdas (C++14)

Using `auto` as a parameter type gives you a generic lambda.

```cpp
auto add = [](auto a, auto b) { return a + b; };
```

On [cpp insights](https://cppinsights.io) you can see the `lambda` class definition the compiler generates:

```cpp
class add_lambda {
 public:
  template <class T, class U>
  auto operator()(T a, U b) const {
    return a + b;
  }
};

add_lambda add{};
```

Both parameters of `add` are declared with `auto`. They correspond to the two template parameters `T` and `U` of the `operator()` function template in the `add_lambda` class.

### Recursion in lambdas

First, here is an example that fails to compile:

```cpp
int n = 10;

auto dfs = [&](int i) -> void {
  if (i == n)
    return;
  else
    dfs(i + 1);  // Error: a variable declared with an auto type specifier
                 // cannot appear in its own initializer
};
```

Here we try to capture $dfs$ in the capture list, but there is a problem. The type of $dfs$ is `auto`, so it is only known after the type of the right-hand side has been deduced. But for the lambda to capture $dfs$, it must know the type of $dfs$ before it can create a reference to it. This is a circular dependency.

How do we fix this?

1.  Give the type of $dfs$ explicitly. You can use `std::function` instead.

    ???+ example "Change the code above to:"
        ```cpp
        int n = 10;
        
        std::function<void(int)> dfs = [&](int i) -> void {
          if (i == n)
            return;
          else
            dfs(i + 1);  // OK
        };
        
        dfs(1);
        ```

    ??? warning "Recursion with [`std::function`](./new.md#stdfunction) is not recommended"
        The type erasure in `std::function` usually needs extra memory allocation, and the indirect call adds pointer lookups that lower performance further.
        
        In a [benchmark](https://quick-bench.com/q/U5qf_dHHKsSyVU83jmt0p_U541c) using the Clang 17 compiler with libc++ as the standard library, the `std::function` version of the recursion was about 2.5 times slower than the lambda version.
        
        ??? note "Benchmark code"
            ```cpp
            #include <algorithm>
            #include <functional>
            #include <numeric>
            #include <random>
            
            using namespace std;
            
            const auto& nums = [] {
              random_device rd;
              mt19937 gen{rd()};
              array<unsigned, 32> arr{};
            
              std::iota(arr.begin(), arr.end(), 0u);
              ranges::shuffle(arr, gen);
            
              return arr;
            }();
            
            static void std_function_fib(benchmark::State& state) {
              std::function<int(int)> fib;
            
              fib = [&](int n) { return n <= 2 ? 1 : fib(n - 1) + fib(n - 2); };
            
              unsigned i = 0;
            
              for (auto _ : state) {
                auto res = fib(nums[i]);
                benchmark::DoNotOptimize(res);
            
                ++i;
            
                if (i == nums.size()) i = 0;
              }
            }
            
            BENCHMARK(std_function_fib);
            
            static void template_lambda_fib(benchmark::State& state) {
              auto n_fibonacci = [](const auto& self, int n) -> int {
                return n <= 2 ? 1 : self(self, n - 1) + self(self, n - 2);
              };
            
              unsigned i = 0;
            
              for (auto _ : state) {
                auto res = n_fibonacci(n_fibonacci, nums[i]);
                benchmark::DoNotOptimize(res);
            
                ++i;
            
                if (i == nums.size()) i = 0;
              }
            }
            
            BENCHMARK(template_lambda_fib);
            ```
2.  Don't get $dfs$ through a capture. Pass it in as a function argument instead.

    ???+ example "Change the code above to:"
        ```cpp
        int n = 10;
        
        // If a parameter in the list has type auto, operator() of this lambda class
        // is defined as a function template, which is instantiated later when it is called
        auto dfs = [&](auto& self,
                       int i) -> void  // [&] only captures variables that are used, so it won't capture auto dfs
        {
          if (i == n)
            return;
          else
            self(self, i + 1);  // OK
        };
        
        dfs(dfs, 1);
        ```

    ???+ note "The difference between `auto self`, `auto& self` and `auto&& self`:"
        In theory, `auto& self` and `auto&& self` only pass $8$ bytes (the size of a pointer) and make no other copies. The details depend on how the compiler implements lambdas and how it optimizes them.
        With `auto self`, the object is copied. The size of the copy depends on the elements in the capture list, since they are all private member variables of the lambda class.
3.  You can expand the lambda class by hand, or write something similar, so that you can declare the type of $dfs$ directly.

    ???+ example "Change the code above to:"
        ```cpp
        int n = 10;
        
        class Lambda_1 {
         public:
          auto operator()(int i) const -> void {
            if (i == n)
              return;
            else
              (*this)(i + 1);  // OK
          }
        
          explicit Lambda_1(int& __n) : n(__n) {}
        
         private:
          int& n;
        } dfs(n);
        
        dfs(1);
        ```
4.  If the lambda captures no variables, we can also use a function pointer.

    If a lambda captures no variables, it can be implicitly converted to a function pointer. In that case the lambda can also be declared `static`, and so can the function pointer. This way, the lambda can access the function pointer without capturing it, which makes recursion possible.

    ???+ example "Example"
        ```cpp
        static unsigned (*fptr)(unsigned);
        
        static const auto lambda = [](const unsigned a) {
          return a < 2 ? a : (*fptr)(a - 2) + (*fptr)(a - 1);
        };
        
        static auto init = [] {
          fptr = +lambda;
          // Or
          // fptr = static_cast<unsigned (*)(unsigned)>(lambda);
          return 0;
        }();
        
        cout << lambda(10);
        ```

### Applications of lambda expressions

#### As a predicate for standard library algorithms

Sorting from largest to smallest:

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
```

Using [std::find\_if](https://zh.cppreference.com/w/cpp/algorithm/find) to find the first element greater than 3:

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
auto it = std::find_if(v.begin(), v.end(), [](int a) { return a > 3; });
```

#### Controlling the lifetime of intermediate variables

In contests, we sometimes run into this situation: initializing a variable needs variables declared earlier, and the initialization creates large intermediate variables that take up a lot of memory.

We want these intermediate variables destroyed as soon as possible to reduce memory use. Here we can use a lambda to control their lifetime.

```cpp
void solution(const vector<int>& input) {
  int b = [&] {
    vector<int> large_objects(input.size());
    int c = 0;

    for (int i = 0; i < large_objects.size(); ++i)
      large_objects[i] = i + input[i];

    for (int i = 0; i < input.size(); ++i) c += large_objects[input[i]];

    return c;
  }();

  // ...
}
```

Compared with a block scope, a lambda lets us use a return value, which makes the code simpler. Compared with a separate function, we don't need to come up with a name or declare all the captured values as parameters, which keeps the code compact.

## References

-   [cppreference-lambda](https://en.cppreference.com/w/cpp/language/lambda)
-   [Stackoverflow: Overhead with std::function](https://stackoverflow.com/a/33881130/11120338)
