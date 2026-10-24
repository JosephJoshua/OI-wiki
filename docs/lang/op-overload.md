Operator overloading means redefining an operator so that it supports operations on specific data types. Overloading an operator is a special case of overloading a function.

> When an operator appears in an expression, and at least one of its operands has a class or enumeration type, overload resolution is used to determine which user-defined function matching the corresponding declarations should be called.[^ref1]

Put simply: think of using an "operator" as calling a special function (for example, `1+2` as calling `add(1, 2)`). If at least one argument (operand) of that function has a `class`, `struct` or `enum` type, the compiler has to decide which user-defined function to call based on the operand types.

In C++, we can overload almost every available operator.

???+ note "Some overloadable operators"
    Unary: `+` (unary plus); `-` (negation); `~` (bitwise NOT); `++`; `--`; `!` (logical NOT); `*` (dereference); `&` (address-of); `->` (member access) and so on.
    
    Binary: `+`; `-`; `&` (bitwise AND); `[]` (subscript); `==`; `=` (assignment) and so on.
    
    Others: `()` (function call); `""` (literal suffix[^ref1], since C++11); `new` (memory allocation); `,` (comma operator); `<=>` (three-way comparison[^ref2], since C++20) and so on.

## Restrictions

Operator overloading has the following restrictions:

-   You can only overload existing operators. You cannot define new ones.
-   The following operators cannot be overloaded: `::` (scope resolution), `.` (member access), `.*` (member access through a pointer to member), `?:` (the ternary operator).
-   An overloaded operator keeps its original precedence, number of operands and associativity; these cannot be changed.
-   Overloads of `&&` (logical AND) and `||` (logical OR) lose short-circuit evaluation.

## Implementation

An operator can be overloaded in two ways: as a member function or as a non-member function.

When overloaded as a member function, there is an implicit `this` pointer to the current object as a parameter, so the function has one fewer parameter than the operator has operands.

When overloaded as a non-member function, the function has as many parameters as the operator has operands.

The basic form is (say the operator to overload is `@`):

```cpp
class Example {
  // member function example
  return_type operator@(parameters other than the object itself) { /* ... */ }
};

// non-member function example
return_type operator@(all operands) { /* ... */ }
```

Below are a few examples of operator overloading.

### Basic arithmetic operators

The code below defines a 2D vector struct `Vector2D` and overloads addition and the dot product for it.

??? note "Example of overloading arithmetic operators"
    ```cpp
    struct Vector2D {
      double x, y;
    
      Vector2D(double a = 0, double b = 0) : x(a), y(b) {}
    
      Vector2D operator+(Vector2D v) const { return Vector2D(x + v.x, y + v.y); }
    
      // note that the return type does not have to be this class
      double operator*(Vector2D v) const { return x * v.x + y * v.y; }
    };
    ```

### Increment and decrement operators

Increment and decrement operators come in two kinds: prefix (`++a`) and postfix (`a++`). To tell them apart, the postfix overload takes an extra unused parameter of type `int`.

You can think of prefix increment as calling `operator++(a)` or `a.operator++()`, and postfix increment as calling `operator++(a, 0)` or `a.operator++(0)`.

??? note "Example of overloading prefix and postfix increment separately"
    ```cpp
    struct MyInt {
      int x;
    
      // prefix, corresponds to ++a
      MyInt &operator++() {
        x++;
        return *this;
      }
    
      // postfix, corresponds to a++
      MyInt operator++(int) {
        MyInt tmp;
        tmp.x = x;
        x++;
        return tmp;
      }
    };
    ```

Also, among the built-in increment and decrement operators, the prefix ones return a reference while the postfix ones return a value. Overloaded operators don't have to follow this rule, but in terms of meaning, overloaded operators are still expected to return the same kinds of types as the built-in ones.

For a type T, the typical overloaded increment operators are defined as follows:

| Overload (using `++` as an example) | Member function         | Non-member function        |
| ----------------------------------- | ----------------------- | -------------------------- |
| Prefix                              | `T& T::operator++();`   | `T& operator++(T& a);`     |
| Postfix                             | `T T::operator++(int);` | `T operator++(T& a, int);` |

### The function call operator

The function call operator `()` can only be overloaded as a member function. By overloading `()` for a class, objects of that class can be called like functions.

A common use of overloading `()` is to pass a struct that overloads `()` as a custom comparison function to STL containers such as a priority queue.

Here is an example: given the names and scores of $n$ students, sort them by score in descending order, breaking ties by name in ascending lexicographic order, and output the name and score of the top-ranked student.

The code below defines a comparison struct that gives the priority queue a custom ordering.

??? note "Example of overloading the function call operator"
    ```cpp
    struct student {
      string name;
      int score;
    };
    
    struct cmp {
      bool operator()(const student& a, const student& b) const {
        return a.score < b.score || (a.score == b.score && a.name > b.name);
      }
    };
    
    // note that the template argument is the struct's name, not an instance
    priority_queue<student, vector<student>, cmp> pq;
    ```

### Comparison operators

`std::sort` and some STL containers need the `<` operator. For a custom type, we have to overload it ourselves.

Here is an example that does the same thing as in the previous section

??? note "Example of overloading a comparison operator"
    ```cpp
    struct student {
      string name;
      int score;
    
      // overload the < operator
      bool operator<(const student& a) const {
        return score < a.score || (score == a.score && name > a.name);
        // the this pointer is omitted above; the full expression is:
        // this->score<a.score||(this->score==a.score&&this->name>a.name);
      }
    };
    
    priority_queue<student> pq;
    ```

The code above overloads the less-than operator as a member function. Overloading it as a non-member function works too.

??? note "Overloading as a non-member function"
    ```cpp
    struct student {
      string name;
      int score;
    };
    
    bool operator<(const student& a, const student& b) {
      return a.score < b.score || (a.score == b.score && a.name > b.name);
    }
    
    priority_queue<student> pq;
    ```

In fact, once you have the `<` operator, the other five comparison operators are easy to overload as well.

```cpp
/* clang-format off */

// all implementations below overload the less-than operator as a non-member function

bool operator<(const T& lhs, const T& rhs) { /* overload the less-than operator here */ }
bool operator>(const T& lhs, const T& rhs) { return rhs < lhs; }
bool operator<=(const T& lhs, const T& rhs) { return !(lhs > rhs); }
bool operator>=(const T& lhs, const T& rhs) { return !(lhs < rhs); }
bool operator==(const T& lhs, const T& rhs) { return !(lhs < rhs) && !(lhs > rhs); }
bool operator!=(const T& lhs, const T& rhs) { return !(lhs == rhs); }
```

??? note "About the three-way comparison operator in C++20"
    If you use C++20 or later, you can simplify the code with the defaulted three-way comparison operator.[^ref3]
    
    ```cpp
    auto operator<=>(const T &lhs, const T &rhs) = default;
    ```
    
    The default comparison compares member variables one by one in the order they are declared.[^ref4]
    
    You can also write a custom three-way comparison. In that case you must choose the ordering it implies (`std::strong_ordering`, `std::weak_ordering` or `std::partial_ordering`), or return an object such that:
    
    -   if `a < b`, then `(a <=> b) < 0`;
    -   if `a > b`, then `(a <=> b) > 0`;
    -   if `a` and `b` are equal or equivalent, then `(a <=> b) == 0`.
    
    For implementation details, see [Comparison operators #Three-way comparison - cppreference](https://zh.cppreference.com/w/cpp/language/operator_comparison#Three-way_comparison).

References and notes:

[^ref1]: [Operator overloading - cppreference](https://zh.cppreference.com/w/cpp/language/operators)

[^ref2]: [User-defined literals - cppreference](https://zh.cppreference.com/w/cpp/language/user_literal)

[^ref3]: [Comparison operators #Three-way comparison - cppreference](https://zh.cppreference.com/w/cpp/language/operator_comparison#.E4.B8.89.E8.B7.AF.E6.AF.94.E8.BE.83)

[^ref4]: [Default comparisons - cppreference](https://zh.cppreference.com/w/cpp/language/default_comparisons)
