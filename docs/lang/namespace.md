## Overview

C++'s **namespace** mechanism helps solve name conflicts in complex projects.

For example, everything in the C++ standard library is defined in the `std` namespace. If you define a variable called `cin`, you can access your own variable with `cin` and the standard library's `cin` object with `std::cin`, without worrying about a conflict.

## Declaration

The following code declares a namespace named `A`:

```cpp
namespace A {
int cnt;

void f(int x) { cnt = x; }
}  // namespace A
```

After this declaration, outside the namespace you can call the function `f` inside namespace `A` with `A::f(x)`, and access the variable `cnt` inside namespace `A` with `A::cnt`.

Namespace declarations can be nested, so the following code is also allowed:

```cpp
namespace A {
namespace B {
void f() { ... }
}  // namespace B

void f() {
  B::f();  // this actually calls A::B::f(); since we are inside namespace A,
           // the leading A:: can be omitted
}
}  // namespace A

void f()  // this defines f in the global namespace; it conflicts with neither A::f
          // nor A::B::f
{
  A::f();
  A::B::f();
}
```

## The `using` directive

Once a namespace is declared, accessing its members from outside requires putting `namespace::` before the member name.

Is there a more convenient way to access members of a namespace directly by name? Yes. We can use the `using` directive.

The `using` directive has two forms:

1.  `using namespace_name::member_name;`: lets us drop the namespace before that one member name and access it directly by name. It is like importing this member into the current scope.
2.  `using namespace namespace_name;`: lets us access **any** member of the namespace directly by name. It is like importing all members of the namespace into the current scope.

So if you write `using namespace std;`, all the names in `std` are brought into the global namespace in the current scope. Then we can write `cin` instead of `std::cin` and `cout` instead of `std::cout`.

??? warning "The `using` directive can cause name conflicts!"
    Since `using namespace std;` brings in **all the names** in `std`, if you declare a variable or function with the same name as something in `std`, you may get a compile error because of the name conflict.
    
    For this reason, the `using namespace namespace_name;` directive is not recommended in real-world projects.

With the `using` directive, the code in [C++ basics](./basic.md#cin-and-cout) can be written in these two equivalent ways:

```cpp
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() {
  int x, y;
  cin >> x >> y;
  cout << y << endl << x;
  return 0;
}
```

```cpp
#include <iostream>

using namespace std;

int main() {
  int x, y;
  cin >> x >> y;
  cout << y << endl << x;
  return 0;
}
```

## Unnamed namespaces

When we only define a namespace in a scope to prevent name conflicts, its definition and use can be made very short. We can use an unnamed namespace.

A namespace defined as `namespace { /* something ... */ } ` (with the name left out) is called an unnamed namespace. An unnamed namespace in a file is treated as having its own unique name, different from every other namespace, but multiple unnamed namespaces in the same scope are treated as the same namespace. After an unnamed namespace is defined, the names in it can be found by lookup in the enclosing scope, as if a `using namespace` directive had been added right after the unnamed namespace's definition.

## Applications

### Preventing name conflicts between subtasks

In some problems with several subtasks, we can define a namespace for each subtask and put the variables and functions needed for that subtask inside it. Then even if two subtasks declare the same names, they won't conflict. The subtasks don't interfere with each other, which makes debugging somewhat easier and also improves the program's readability.

### Preventing conflicts with names from the standard library and the environment

Namespaces can also prevent some names commonly used in contests from conflicting with the standard, as in this example:

```cpp
#include <math.h>

#include <vector>

using namespace std;

namespace Sol {
int end;  // std::end is brought in by using namespace std;

int y1;  // y1 is the Bessel function of the second kind defined by POSIX

// so usually there is a conflict on Linux but not on Windows

void solve() {
  // Inside Sol::solve(), using our declared end and y1 unqualified (without ::)
  // does not cause a name conflict. If the code above were in the global namespace, it would conflict: end
  // only conflicts with std::end at name lookup (i.e. when compiling code that uses it), while y1
  // conflicts as soon as it is declared. And since the y1 conflict depends on the environment, it may not even show up on Windows
  // but will cause a compile error on a Linux judge.
}
}  // namespace Sol

int main() { Sol::solve(); }
```

## References

-   [Namespaces - cppreference.com](https://en.cppreference.com/w/cpp/language/namespace)
