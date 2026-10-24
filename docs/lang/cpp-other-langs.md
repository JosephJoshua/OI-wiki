This page covers the differences between C++ and other common languages, focusing on differences between C and C++ that are important or easy to overlook. C++ is almost a superset of C, and mixing C/C++ code usually works fine, but knowing the more important differences between C and C++ can help you avoid some strange bugs. If C is your main language as an OIer, this page can also help you get started with C++ more smoothly. For the features C++ adds on top of C, read the tutorials in the [Advanced C++](./class.md) section. This page also briefly covers the differences between Python, Java and C++.

## Differences between C and C++

### Macros and templates

One of the original purposes of C++ templates was to replace macros. Learning template programming is an important step in moving from C to C++. Unlike the text replacement done by macros, templates are checked more thoroughly by the compiler, which makes it easier to write robust code. Since C++11, templates support variable-length template parameter lists, which can replace variadic functions in C while keeping type safety.

### Pointers and references

You can still use C-style pointers in C++, but for passing variables it is better to use C++ [references](./reference.md) to achieve similar effects. Since the object a reference refers to cannot be null, this avoids some null-address access problems. Pointers are still useful, though, because they are more flexible. It is worth mentioning that C's null pointer `NULL` has a type-safe replacement, `nullptr`, since C++11. You can convert between references and pointers with the [`*` and `&` operators](./op.md).

### bool

See also [Boolean type](var.md#boolean-type).

Unlike C++, C originally had no boolean type.

The C99 standard added the `_Bool` keyword (and the equivalent `bool` macro), along with the two macros `true` and `false`. To use the three macros `bool`, `true` and `false`, you need to include the `stdbool.h` header in your program. Using `_Bool` does not require any extra header.

```c
bool x = true;  // Requires including stdbool.h
_Bool x = 1;    // Does not require including stdbool.h
```

Since C23, `true`, `false` and `bool` are keywords in C, so you no longer need to include the `stdbool.h` header to use them, and `_Bool` is kept as an alternative spelling of `bool`[^boolean-keyword].

The table below shows how support for the bool type changed across C standards (C++ support is included for comparison):

| Language standard          | `bool`                                                         | `true`/`false`                                                                                   | `_Bool`                                    |
| -------------------------- | -------------------------------------------------------------- | ------------------------------------------------------------------------------------------------ | ------------------------------------------ |
| C89                        | /                                                              | /                                                                                                | Reserved[^reserved-identifiers]            |
| Since C99, before C23      | Macro, equivalent to `_Bool`, requires the `stdbool.h` header | Macros, `true` equivalent to `1`, `false` equivalent to `0`, require the `stdbool.h` header      | Keyword                                    |
| Since C23                  | Keyword                                                        | Keywords                                                                                         | Keyword, alternative spelling of `bool`    |
| C++                        | Keyword                                                        | Keywords                                                                                         | Reserved[^reserved-identifiers]            |

### struct

Although both C and C++ have the concept of struct, what they refer to cannot be mixed! In C, a struct describes a fixed memory layout, while in C++ a struct is a class. **Its only difference from a class is that its members and inheritance are public by default**, whereas a class's members are private by default. This can be especially deadly when writing mixed C/C++ code.

Also, declaring a struct in C++ is not as verbose as in C. The C version:

```c
typedef struct Node_t {
  struct Node_t *next;
  int key;
} Node;
```

The C++ version:

```cpp
struct Node {
  Node *next;
  int key;
};
```

### const

In C, const only marks a variable as unmodifiable. In C++, with the arrival of many new features, const has been given more uses. The successor of C's const in C++ is constexpr; for the uses of const in C++, see the [Constants](./const.md) page.

### Memory allocation

C++ adds the `new` and `delete` keywords for allocating space in the "free store", which can be the heap or the static storage area; they were introduced to work with "classes". `delete[]` can also free the memory of a dynamic array directly, which is very convenient. The `new` and `delete` keywords call the constructor and destructor of the type. Compared with C's `malloc()`, `realloc()` and `free()` functions, they support types more fully, but they are less efficient than these C functions.

In short, if the objects you need to allocate dynamically are of basic types or arrays of them, you can use `malloc()` for more efficient allocation. But if the objects you create are not of basic types, it is better to use `new` to get safety checks. Note that although `new` and `malloc()` both return pointers, a pointer from `new` can **only** be freed with `delete`, and a pointer from `malloc()` can only be freed with `free()`; otherwise you risk memory leaks.

### Variable declarations

Before C99, variable declarations in C had to be at the start of a block. C++, and C since C99, have no such restriction.

### Variable-length arrays

Since C99, C supports VLAs (variable-length arrays). C++ has never supported them.

### Struct initialization

Since C99, C supports [designated initializers](https://en.cppreference.com/w/c/language/struct_initialization) for structs (though they are an optional feature in C11). C++ only supports designated initializers, with an ordering requirement, starting from C++20, and C++ does not support the C features of out-of-order, nested, mixed with ordinary initializers, or array designated initializers[^cpp-designated-init].

### Comment syntax

C did not support C++-style single-line comments `//` before C99.

## Differences between Python and C++

Python is currently the most widely used language in machine learning. Compared with C++, Python's advantage is that it is easy to learn and easy to use in practice. Python has simpler and more direct syntax; for example, you don't need to declare a variable's type in advance when defining it. But this simplicity comes at a cost: Python gives up performance compared with C++. C++ works on almost every platform, including embedded systems, and runs faster, while Python can only be used on platforms that support high-level languages. C++ is closer to the hardware, so it can be used to write operating systems.

## Differences between Java and C++

Java and C++ are both object-oriented languages and both use object-oriented ideas (encapsulation, inheritance, polymorphism). Because object orientation has many very good properties (inheritance, composition, etc.), both are highly reusable. So compared with Python, Java and C++ are more alike.

The biggest difference between them is that Java has the JVM. JVM stands for Java Virtual Machine. A very important feature of Java is platform independence, and the Java Virtual Machine is the key to achieving it. An ordinary high-level language must at least be compiled into different target code to run on different platforms. With the Java virtual machine, Java does not need to be recompiled to run on different platforms. Java uses the Java virtual machine to hide platform-specific details, so the Java compiler only needs to generate target code (bytecode) that runs on the Java virtual machine, and it can run on many platforms without changes.

Because of this, Java is often used to develop programs that need to be ported to different platforms. But since running a Java program starts from bytecode, Java does not perform as well as C++.

## References

[^cpp-designated-init]: <https://en.cppreference.com/w/cpp/language/aggregate_initialization>

[^boolean-keyword]: <https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3054.pdf>.

[^reserved-identifiers]: Both C and C++ specify that identifiers starting with an underscore followed by an uppercase letter are reserved. See <https://en.cppreference.com/w/c/language/identifier>.
