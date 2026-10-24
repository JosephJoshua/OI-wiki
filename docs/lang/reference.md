> Declares a named variable as a reference, that is, an alias to an already-existing object or function.

You can think of a reference as a non-null pointer wrapped up by C++. It can be used to pass around the object it refers to, and it must refer to an object when it is declared.

A reference is not an object. So there are no arrays of references, you cannot take a pointer to a reference, and there are no references to references.

??? note "Reference types are not object types"
    If you want references that support ordinary copying, assignment and so on, for example to use them as container elements, you need [`reference_wrapper`](https://zh.cppreference.com/w/cpp/utility/functional/reference_wrapper), which is usually implemented by storing a non-null pointer.

There are two main kinds of references: lvalue references and rvalue references.

??? note "Lvalues and rvalues"
    For an explanation of lvalues and rvalues, see the [Value categories](./value-category.md) page.

## Lvalue references T&

The references we usually deal with are lvalue references, that is, references bound to lvalues. A `const`-qualified lvalue reference can also bind to an rvalue. Here is some example code from the [reference manual](https://zh.cppreference.com/w/cpp/language/reference).

```cpp
#include <iostream>
#include <string>

int main() {
  std::string s = "Ex";
  std::string& r1 = s;
  const std::string& r2 = s;

  r1 += "ample";  // modifying r1 modifies s
  // r2 += "!"; // error: cannot modify through a reference to const
  std::cout << r2 << '\n';  // printing r2 accesses s, prints "Example"
}
```

The most common use of lvalue references is as function parameters, to avoid unnecessary copies.

```cpp
#include <iostream>
#include <string>

// s in the parameter list is a reference, so no copy happens when the function is called
char& char_number(std::string& s, std::size_t n) {
  s += s;  // 's' is the same object as 'str' in main();
           // this also shows that an lvalue can appear on the right of =
  return s.at(n);  // string::at() returns a reference to char
}

int main() {
  std::string str = "Test";
  char_number(str, 1) = 'a';  // the function returns an lvalue, which can be assigned to
  std::cout << str << '\n';   // prints "TastTest" here
}
```

## Rvalue references T&& (C++ 11)

An rvalue reference is a reference bound to an rvalue. It is used to move objects, and it can also **extend the lifetime of a temporary object**.

```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
  string s1 = "Test";
  // string&& r1 = s1; // error: cannot bind to an lvalue; needs std::move or static_cast

  const string& r2 = s1 + s1;  // OK: an lvalue reference to const extends the lifetime
  // r2 += "Test"; // error: cannot modify through a reference to const
  cout << r2 << '\n';

  string&& r3 = s1 + s1;  // OK: an rvalue reference extends the lifetime
  r3 += "Test";
  cout << r3 << '\n';

  const string& r4 = r3;  // an rvalue reference can be converted to a const-qualified lvalue
  cout << r4 << '\n';

  string& r5 = r3;  // an rvalue reference can be converted to an lvalue
  cout << r5 << '\n';
}
```

## Dangling references

When the object a reference refers to has been destroyed, the reference becomes a dangling reference. Accessing a dangling reference is undefined behavior and may crash the program.

Here are some common examples of dangling references:

-   Referring to a local variable

    ```cpp
    #include <iostream>

    int& foo() {
      int a = 1;
      return a;
    }

    int main() {
      int& b = foo();
      std::cout << b << std::endl;  // undefined behavior
    }
    ```

-   Dangling reference caused by deallocation

    ```cpp
    #include <iostream>

    int main() {
      int* ptr = new int(10);
      int& ref = *ptr;
      delete ptr;

      std::cout << ref << std::endl;  // undefined behavior
    }
    ```

-   Dangling reference caused by memory reallocation

    ```cpp
    #include <iostream>

    int main() {
      std::string str = "hello";

      const char& ref = str.front();

      str.append("world");  // may reallocate memory, freeing the memory ref points to

      std::cout << ref << std::endl;  // undefined behavior
    }
    ```

    Insertions into containers such as `std::vector` and `std::unordered_map` may all cause memory to be reallocated.

When you use references, always keep track of the lifetime of the object a reference refers to, so you don't end up with dangling references.

Static analysis tools and good coding habits usually help us avoid dangling references.

## Optimization tricks with references

### Avoiding the cost of copying heavyweight parameters

Common **heavyweight objects** include:

-   containers such as `vector`, `array` and `map`
-   `string`
-   other types that define or inherit custom special functions such as copy constructors and move constructors

Using references for **lightweight objects** brings no benefit. A reference parameter may even take up more space than the type itself.

This can add some performance overhead, and it may also prevent compiler optimizations.

The following are **lightweight objects**:

-   basic types such as `int` and `float`
-   small [aggregate types](https://zh.cppreference.com/w/cpp/language/aggregate_initialization)
-   iterators of standard library containers

### Converting lvalues into rvalues

Use `std::move` to [transfer](./value-category.md#stdmove) ownership of an object. This is common between local variables, or between a parameter and a local variable:

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string world(string str) { return std::move(str) += " world!"; }

int main() {
  // 1
  cout << world("hello") << '\n';

  vector<string> vec0;

  // 2
  {
    string&& size = to_string(vec0.size());

    size += ", " + to_string(size.size());

    vec0.emplace_back(std::move(size));
  }

  cout << vec0.front();
}
```

But you don't always need to do this; see for example [return value optimization](./value-category.md#common-pitfalls).

### Extending the lifetime of temporaries with rvalue references

Semantically, temporaries may cause extra copies or moves. In most cases the compiler can optimize them away with [copy elision](./value-category.md#copy-elision), but a reference forces the compiler not to do these extra operations, which removes the uncertainty.

## References

1.  [C++ language documentation: Reference declaration](https://zh.cppreference.com/w/cpp/language/reference)
2.  [C++ language documentation: Value categories](https://zh.cppreference.com/w/cpp/language/value_category)
3.  [Does const ref lvalue to non-const func return value specifically reduce copies?](https://stackoverflow.com/questions/38909228/does-const-ref-lvalue-to-non-const-func-return-value-specifically-reduce-copies)
