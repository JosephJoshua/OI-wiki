Value categories are a very important concept in C++. They may not be very useful in competitive programming, but understanding them helps us spot and avoid unnecessary copies, which makes code faster and more efficient.

The idea of value categories evolved several times through C, C++98, C++11 and C++17, and gradually became a fairly complicated concept.

## Unnecessary copies

Consider putting strings into a vector:

```cpp
int main() {
  std::vector<std::string> vec;
  vec.reserve(3);
  for (int i = 0; i < 3; ++i) {
    std::string str;
    std::cin >> str;
    vec.push_back(str);
  }
  return 0;
}
```

You can see that while the string is being transferred, one copy is kept in `str` and another in `vec`, so the memory use doubles.

If we really want to save this memory, we can implement a crude move operation: define a custom `MyString` struct that holds a pointer to our string. Then we only need to copy the pointer over, and carefully clear the original object's pointer so the data is not wrongly destroyed.

```cpp
struct MyString {
  char *beg, *end;
  // ...
};

void move_to(MyString &src, MyString &dst) {
  dst.beg = src.beg;
  dst.end = src.end;
  src.beg = src.end = nullptr;
}
```

Because this need to transfer objects efficiently is quite common, and because it is hard to make it work together with C++ construction, destruction and so on, C++11 brought move semantics into the core language.

## Value categories in C

In the C standard, an object is a more general concept than a variable. It refers to a region of memory that has a memory address. The main attributes of an object are: size, effective type, value and identifier. The identifier is the variable name, and the value is what that memory means when interpreted as its type. For example, `int` and `float` both take 4 bytes, but the same piece of memory means different things depending on which type we interpret it as.

In C, every expression has a type and a value category. There are three main value categories:

-   Lvalue: an expression that implicitly designates an object. That is, we can take the address of the expression.
-   Rvalue: an expression that does not designate an object, that is, a value with no storage location. We cannot take its address.
-   Function designator: an expression of function type.

So only modifiable lvalues (lvalues that are not `const`-qualified and are not arrays) can appear on the left side of an assignment.

For an operator that requires an rvalue as its operand, whenever an lvalue is used as the operand, the lvalue-to-rvalue, array-to-pointer or function-to-pointer standard conversion is applied to turn it into an rvalue.

Common misconceptions:

-   Further operations on an rvalue expression can produce an lvalue. For example, with `int *a`, the expression `a + 1` is an rvalue, but `*(a + 1)` is an lvalue.
-   Only expressions have value categories; variables do not. For example, with `int *a`, you cannot say the variable `a` is an lvalue. You can say it acts as an lvalue in the expression `a`.

## Value categories in C++98

C++98 is almost the same as C when it comes to value categories, but it adds a few new rules:

-   Functions are lvalues, because you can take their address.
-   Lvalue references (T&) are lvalues, because you can take their address.
-   Only `const T&` can bind to an rvalue.

### Copy elision

C++ allows the compiler to perform copy elision, which reduces the number of temporary objects created and destroyed.

For example, the code below triggers return value optimization (RVO), a form of copy elision. You will see only one construction and one copy construction, even though construction and destruction have side effects.

```cpp
struct X {
  X() { std::puts("X::X()"); }

  X(const X &) { std::puts("X::X(const X &)"); }

  ~X() { std::puts("X::~X()"); }
};

X get() {
  X x;
  return x;
}

int main() {
  X x = get();
  X y = X(X(X(X(x))));
  return 0;
}
```

## Value categories in C++11

C++11 introduced move semantics and rvalue references (`T&&`), including move constructors and move assignment functions. This gives us a way to make use of temporary objects.

Our `move_to` from above can be rewritten as:

```cpp
struct MyString {
  // ...
  MyString(MyString&& other) {
    beg = other.beg;
    end = other.end;
    other.beg = other.end = nullptr;
  }
};
```

We now care about one more property of expressions:

-   Whether it has identity: whether it designates an object, that is, whether it has an address.
-   Whether it can be moved from: whether it has move constructors, move assignment and similar functions, which give us a way to make use of these temporary objects.

So we have three value categories:

-   Has identity, cannot be moved from: lvalue.
-   Has identity, can be moved from: xvalue (expiring value).
-   No identity, can be moved from: prvalue (pure rvalue).
-   No identity, cannot be moved from: expressions like this are unusable.

C++11 also introduced two mixed categories:

-   Has identity: glvalue (generalized lvalue), that is, lvalues and xvalues.
-   Can be moved from: rvalue, that is, prvalues and xvalues.

### std::move

To go with move semantics, C++11 also introduced the utility function `std::move`. It casts an lvalue to an rvalue so that move semantics kick in.

```cpp
int main() {
  std::vector<int> a = {1, 2, 3};
  std::cout << "a: " << a.data() << std::endl;
  std::vector<int> b = a;
  std::cout << "b: " << b.data() << std::endl;
  std::vector<int> c = std::move(b);
  std::cout << "c: " << c.data() << std::endl;
}
```

So we only need to change `push_back(str)` to `push_back(std::move(str))` to avoid the copy.

```cpp
int main() {
  std::vector<std::string> vec;
  vec.reserve(3);
  for (int i = 0; i < 3; ++i) {
    std::string str;
    std::cin >> str;
    vec.push_back(std::move(str));
    // another neat way to write it, requires C++17
    // std::cin >> vec.emplace_back();
  }
  return 0;
}
```

> Because `std::string` has small string optimization (SSO), short strings are stored directly inside the object. You may need to enter a fairly long string to see that the `data` pointer stays the same.

## Value categories in C++17

C++17 further simplified value categories:

-   Lvalue: has identity, cannot be moved from.
-   Xvalue: has identity, can be moved from.
-   Prvalue: the initialization of an object.

C++11 extended copy elision to moves. In the code below, `urvo` involves no move when the compiler has RVO enabled.

C++17 requires that a prvalue is not materialized unless necessary; it is constructed directly into the storage of its final destination, and the object does not exist before it is constructed. So in C++17 there is no "return" step at all, and we don't need to rely on RVO. You can also think of it as making URVO (Unnamed RVO) mandatory, while NRVO (Named RVO) is still not mandatory.

```cpp
std::string urvo() { return std::string("123"); }

std::string nrvo() {
  std::string s;
  s = "123";
  std::cout << s;
  return s;
}

int main() {
  std::string str = urvo();  // constructed directly
  std::string str = nrvo();  // not necessarily constructed directly; depends on optimization
}
```

C++17 also introduced temporary materialization. When a glvalue is needed, such as when accessing a member variable or calling a member function, a prvalue can be implicitly converted to an xvalue.

### Common pitfalls

In the example below:

-   In `f1`, returning `std::move(x)` is redundant. It brings no performance gain and actually gets in the way of the compiler's NRVO.
-   In `f2`, returning `std::move(x)` is dangerous. The function returns an rvalue reference to the local variable `s`, which has already been destroyed, so you get a dangling reference.

```cpp
std::string f1() {
  std::string s = "123";
  // equivalent to return std::string(std::move(s))
  return std::move(s);
}

std::string&& f2() {
  std::string s = "123";
  return std::move(s);
}
```

## References and further reading

1.  [Value categories](https://en.cppreference.com/w/cpp/language/value_category)
2.  [Wording for guaranteed copy elision through simplified value categories](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0135r1.html)
3.  [Value categories in C++](https://paul.pub/cpp-value-category/)
4.  [C++ rvalue references, moves and the value category system: everything you need](https://zclll.com/index.php/cpp/value_category.html)
5.  [Copy elision](https://en.cppreference.com/w/cpp/language/copy_elision)
