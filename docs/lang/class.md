author: Ir1d, cjsoft, Lans1ot, JasonkayZK

A class is an extension of a struct: besides member elements, it can also have member functions.

In object-oriented programming (OOP), an object is an instance of a class, that is, a variable.

In C++, the `struct` keyword also defines a class. The definition of **struct** above comes from C. For historical reasons, C++ kept `struct` and extended it.

## Defining a class

A class is defined with the keyword `class` or `struct`. The examples below use `class`.

```cpp
class ClassName {
  ...
};

// Example:
class Object {
 public:
  int weight;
  int value;
} e[array_length];

const Object a;
Object b, B[array_length];
Object *c;
```

This is much the same as using `struct`. This example defines a class named `Object`. The class has two member elements, `weight,value`, and after the `}` it uses the type to define an array `e`.

Pointers to a class are defined the same way as for [`struct`](./struct.md).

### Access specifiers

Unlike the examples for [`struct`](./struct.md), this example contains `public`, which is an access specifier.

-   `public`: members after this access specifier can be accessed publicly. Simply put, they can be accessed both **inside the class** and **outside the class**.
-   `protected`: members after this access specifier can be accessed by members **inside the class**, by derived classes, or by members of friends, but they **cannot be accessed** from outside the class.
-   `private`: members after this access specifier can **only** be accessed by members **inside the class** or by members of friends. They **cannot** be accessed from outside the class or from derived classes.

For `struct`, all members are `public` by default. For `class`, all members are `private` by default.

??? note "Basic ideas of friends and derived classes"
    Friend (`friend`): you mark a function or class with the `friend` keyword. This lets the **marked function or class** access the class's private (`private`) or protected (`protected`) members without being a member function or member class. Simply put, anything with this class's `friend` mark can access private or protected member elements.
    
    Derived class (`derived class`): C++ lets you use a class as a **base class** and **derive** a **derived class** from it. The derived class inherits (by certain rules) the member variables and member functions of the base class. This makes code more reusable.
    
    Derivation is like an "is" relationship. For example, a cat (derived class) "is" a mammal (base class).
    
    As for the difference between `private` and `protected` above, you can think of it as: a derived class can access the base class's `protected` elements (and `public` ones too), but not its `private` elements.

## Accessing and modifying member elements

This works the same as for [`struct`](./struct.md):

-   For variables, use the `.` operator.
-   For pointers, use the `->` operator.

## Member functions

Member functions are exactly what the name says: functions contained in a class.

??? note "Examples of common member functions"
    ```cpp
    vector.push_back();
    set.insert();
    queue.empty();
    ```

```cpp
class Class_Name {
  ... type Function_Name(...) { ... }
};

// Example:
class Object {
 public:
  int weight;
  int value;

  void print() {
    cout << weight << endl;
    return;
  }

  void change_w(int);
};

void Object::change_w(int _weight) { weight = _weight; }

Object var;
```

This class has a function that prints the member element of `Object`, and a function that changes the member element `weight`.

As with ordinary functions, a member function can be declared first and defined later, as on line 14 (the declaration) and after line 17 (the definition).

To call the `print` member function of `var`, write `var.print()`.

### Operator overloading

??? note "What is overloading?"
    C++ lets you give different definitions to functions or operators with the same name. This is called **overloading**.
    
    Functions with the same name are treated as different if they differ in one or more of the types and the number of their parameters.
    
    Note: if two functions with the same name differ only in their return type, they cannot be overloaded, and the compiler will refuse to compile!
    
    If a call is not ambiguous (ambiguous means that when calling functions with the same name, the called function cannot be determined uniquely from the types and number of arguments; this often happens with functions that have default arguments), the compiler decides which function to call based on the arguments given in the call.
    
    This process is called overload resolution.

Overloaded operators can partly replace functions and make code simpler.

Here is an example of operator overloading.

```cpp
class Vector {
 public:
  int x, y;

  Vector() : x(0), y(0) {}

  Vector(int _x, int _y) : x(_x), y(_y) {}

  int operator*(const Vector& other) const { return x * other.x + y * other.y; }

  Vector operator+(const Vector&) const;
  Vector operator-(const Vector&) const;
};

Vector Vector::operator+(const Vector& other) const {
  return Vector(x + other.x, y + other.y);
}

Vector Vector::operator-(const Vector& other) const {
  return Vector(x - other.x, y - other.y);
}

// Lines 4 and 5 assign values to x and y; see below for how this works.
```

This example defines a vector class and overloads the `* + -` operators, which mean the dot product, vector addition and vector subtraction.

The template for operator overloading roughly has the following parts.

```text
/*Overloaded inside the class definition*/ ReturnType operatorSymbol(parameters){...}

/*Declared inside the class definition, defined outside*/ ReturnType ClassName::operatorSymbol(parameters){...}
```

For your own class, if you overload certain operators (usually you only need to overload the comparison operator `<`), you can use the matching STL containers or algorithms, such as [`sort`](../basic/stl-sort.md).

To learn more, see item 4 in "References".

??? note "Operators that can be overloaded"
    ```text
    +       -       *       /       %       ^       &
    |       ~       !       =       <       >       +=
    -=      *=      /=      %=      ^=      &=      |=
    <<      >>      >>=     <<=     ==      !=      <=
    >=      &&      ||      ++      --      ,       ->*
    ->      ()      []      new     new []  delete  delete []
    ```

### Setting initial values when creating variables

To do this, you need to define a **default constructor**.

```cpp
class ClassName {
  ... ClassName(...)... { ... }
};

// Example:
class Object {
 public:
  int weight;
  int value;

  Object() {
    weight = 0;
    value = 0;
  }
};
```

This example defines the default constructor of `Object`. When we create a variable of type `Object`, this function initializes all member elements to `0`.

If there is no explicit constructor, the compiler treats the class as having an implicit default constructor. In other words, if you define no constructor at all, the compiler generates a default constructor automatically, and member elements are initialized according to their types (the same as when defining variables of built-in types).

In that case, the member elements are uninitialized, and the result of reading an uninitialized variable is undefined (that is, you don't know what value you will get).

If you need custom initial values, you can define (or overload) more constructors.

??? note "About defining (or overloading) constructors"
    In general, a default constructor takes no parameters, which is what distinguishes it from other constructors. Constructors and default constructors are defined in much the same way; they differ only in the number of parameters.
    
    Constructors can be overloaded (the first one is of course called a definition). Note that once you have defined a constructor, the compiler no longer generates a parameterless default constructor. This may make an attempt to construct a variable the default way (without giving initialization arguments) fail to compile.

With C++11 or later, you can use `{}` to initialize variables.

??? note "About `{}`"
    Initializing with `{}` uses the lightweight proxy object std::initializer\_list.
    
    The initialization steps are roughly:
    
    1.  Look for a default constructor that takes a `std::initializer_list` parameter; if there is one, call it (once a call is made, the search below stops; the same applies below).
    2.  Try to fill the elements in `{}` into the other constructor parameters. If the parameters can be filled in order (default arguments count too), call that default constructor.
    3.  If there are no `private` member elements, try to assign the values one by one **from outside the class** in the order the elements are defined or in index order.
    
    *The process above is only a simplified version of the full process; for details, see "Reference 9".*

```cpp
class Object {
 public:
  int weight;
  int value;

  Object() {
    weight = 0;
    value = 0;
  }

  Object(int _weight = 0, int _value = 0) {
    weight = _weight;
    value = _value;
  }

  // the same as
  // Object(int _weight,int _value):weight(_weight),value(_value) {}
};

// the same as
// Object::Object(int _weight,int _value){
//   weight = _weight;
//   value = _value;
// }
//}

Object A;        // ok
Object B(1, 2);  // ok
Object C{1, 2};  // ok,(C++11)
```

??? note "About implicit type conversion"
    Sometimes you may write code like this:
    
    ```cpp
    class Node {
     public:
      int var;
    
      Node(int _var) : var(_var) {}
    };
    
    Node a = 1;
    ```
    
    It looks illogical: an `int` cannot possibly be converted to a `node`. Yet the compiler does not report an `error`.
    
    The reason is that during the assignment, `node::node(int)` is first called with `1` as the argument, and then the default copy function is called to do the assignment.
    
    In most cases, though, you would want the compiler to report an error. You can then add the `explicit` keyword before the constructor. This tells the compiler that the constructor must be called explicitly.
    
    ```cpp
    class Node {
     public:
      int var;
    
      explicit Node(int _var) : var(_var) {}
    };
    ```
    
    That is, `node a=1` will give an error, but `node a=node(1)` will not, because the latter calls the constructor explicitly. Of course, most people would not write the latter, but this example is enough to show what explicit does.
    
    *In competitive programming, however, the usual way to avoid such cases is to "write more disciplined code", avoiding the problem at its source.*

### Destruction

This cannot be avoided: every variable is destroyed when its scope ends.

But for a pointer that points to dynamically allocated memory, destroying the pointer does not automatically free the memory it points to. You need to free the dynamic memory by hand.

If the member elements of a struct include pointers, you run into the same problem. You need a destructor to free the dynamic memory by hand.

The **destructor** is called when the variable is destroyed. You overload it the same way as a constructor, but with a `~` in front.

*The default destructor is usually good enough for competitive programming. We usually only overload the destructor when member elements include pointers.*

```cpp
class Object {
 public:
  int weight;
  int value;
  int* ned;

  Object() {
    weight = 0;
    value = 0;
  }

  ~Object() { delete ned; }
};
```

### Assigning to class variables

By default, assignment assigns each corresponding member element. You can also use `ClassName()` or `ClassName{}` as a temporary variable for assignment.

The former only calls the copy constructor, while the latter calls the default constructor before calling the copy constructor.

Also, by default, assignment does a **shallow copy** between corresponding elements. If a member element is a pointer, then after the assignment the member pointers of the two variables hold the same address.

```cpp
// A, tmp1, tmp2, tmp3 have type Object
tmp1 = A;
tmp2 = Object(...);
tmp3 = {...};
```

To fix the pointer problem or do more, you need to overload the corresponding constructors.

*For more about constructors, see item 6 in "References".*

## References

1.  [cppreference class](https://zh.cppreference.com/w/cpp/language/class)
2.  [cppreference access](https://zh.cppreference.com/w/cpp/language/access)
3.  [cppreference default\_constructor](https://zh.cppreference.com/w/cpp/language/default_constructor)
4.  [cppreference operator](https://zh.cppreference.com/w/cpp/language/operators)
5.  [cplusplus Data structures](http://www.cplusplus.com/doc/tutorial/structures/)
6.  [cplusplus Special members](http://www.cplusplus.com/doc/tutorial/classes2/)
7.  [C++11 FAQ](http://www.stroustrup.com/C++11FAQ.html)
8.  [cppreference Friendship and inheritance](http://www.cplusplus.com/doc/tutorial/inheritance/)
9.  [cppreference value initialization](https://zh.cppreference.com/w/cpp/language/value_initialization)
