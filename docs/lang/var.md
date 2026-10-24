## Data types

The C++ type system is made up of the following parts:

1.  Fundamental types (representative keywords/types in parentheses)
    1.  The void type/`void` (`void`)
    2.  (since C++11) The null pointer type (`std::nullptr_t`)
    3.  Arithmetic types
        1.  Integer types (`int`)
        2.  The Boolean type/`bool` (`bool`)
        3.  Character types (`char`)
        4.  Floating-point types (`float`,`double`)
2.  Compound types[^note11]

### Boolean type

A variable of type `bool` can only hold one of two values: `true` and `false`.

Usually, a `bool` variable takes up $1$ byte of space (usually, $1$ byte = $8$ bits).

???+ tip "Tip"
    You can get the number of bits in a byte from the macro constant `CHAR_BIT` in the header `<climits>` (C++)/`<limits.h>` (C).

???+ note "The Boolean type in C"
    See also [Differences between C++ and other common languages - bool](./cpp-other-langs.md#bool).
    
    C originally had no Boolean type. C99 introduced the keyword `_Bool` as the Boolean type, and it is treated as an unsigned integer type.
    
    ???+ note "Note"
        Since C23, the C `bool` type is no longer defined in terms of the integer values zero and non-zero. Instead, it is defined as a type large enough to store the two constants `true` and `false`.
    
    For convenience, `stdbool.h` provides three macros `bool`, `true` and `false`, defined as follows:
    
    ```c
    #define bool _Bool
    #define true 1
    #define false 0
    ```
    
    These macros were removed in C23. Since C23, `true`, `false` and `bool` are keywords, and `_Bool` is kept as an alternative spelling[^note10].
    
    Also, since C23 you can get the bit width of the Boolean type from the macro constant `BOOL_WIDTH` in `<limits.h>`.

### Integer types

Integer types store integers. The most basic integer type is `int`.

???+ warning "Warning"
    For historical reasons, the Boolean type and the character types are treated as special integer types in C++.
    
    In almost all cases you should **not** use character types other than `signed char` and `unsigned char` as integers.

Integer types usually come in 5 levels of bit width: `char`, `short`, `int`, `long`, `long long`.

The C++ standard guarantees `1 == sizeof(char) <= sizeof(short) <= sizeof(int) <= sizeof(long) <= sizeof(long long)`

For historical reasons, there are several popular models for the bit widths of integer types. To solve this problem, C99/C++11 introduced [fixed-width integer types](#fixed-width-integer-types).

???+ note "The size of `int`"
    The C++ standard requires `int` to have **at least** $16$ bits.
    
    In fact, on nearly all platforms today, `int` has $32$ bits.

The `int` keyword can be combined with the following modifier keywords:

Signedness:

-   `signed`: a signed integer (the default);
-   `unsigned`: an unsigned integer.

Size:

-   `short`: an integer of **at least** $16$ bits;
-   `long`: an integer of **at least** $32$ bits;
-   (since C++11) `long long`: an integer of **at least** $64$ bits.

The table below shows the bit width and range of each integer type **in the usual case** (on a few platforms, some types may have different ranges from those in the table):

| Type name                                                             | Equivalent type          | Bit width (C++ standard) | Bit width (common) | Bit width (less common)              |
| --------------------------------------------------------------------- | ------------------------ | ---------- | ------ | -------------------------- |
| `signed char`                                                         | `signed char`            | $8$        | -      | -                          |
| `unsigned char`                                                       | `unsigned char`          | $8$        | -      | -                          |
| `short`,`short int`,`signed short`,`signed short int`                 | `short int`              | $\geq 16$  | $16$   | -                          |
| `unsigned short`,`unsigned short int`                                 | `unsigned short int`     | $\geq 16$  | $16$   | -                          |
| `int`,`signed`,`signed int`                                           | `int`                    | $\geq 16$  | $32$   | $16$ (common in the Win16 API)        |
| `unsigned`,`unsigned int`                                             | `unsigned int`           | $\geq 16$  | $32$   | $16$ (common in the Win16 API)        |
| `long`,`long int`,`signed long`,`signed long int`                     | `long int`               | $\geq 32$  | $32$   | $64$ (common on 64-bit Linux and macOS) |
| `unsigned long`,`unsigned long int`                                   | `unsigned long int`      | $\geq 32$  | $32$   | $64$ (common on 64-bit Linux and macOS) |
| `long long`,`long long int`,`signed long long`,`signed long long int` | `long long int`          | $\geq 64$  | $64$   | -                          |
| `unsigned long long`,`unsigned long long int`                         | `unsigned long long int` | $\geq 64$  | $64$   | -                          |

When the bit width is $x$, a signed type can represent $-2^{x-1}\sim 2^{x-1}-1$[^note16], and an unsigned type can represent $0 \sim 2^x-1$. Specifically:

| Bit width | Range                                              |
| ---- | ------------------------------------------------- |
| $8$  | Signed: $-2^{7}\sim 2^{7}-1$, unsigned: $0 \sim 2^{8}-1$    |
| $16$ | Signed: $-2^{15}\sim 2^{15}-1$, unsigned: $0 \sim 2^{16}-1$ |
| $32$ | Signed: $-2^{31}\sim 2^{31}-1$, unsigned: $0 \sim 2^{32}-1$ |
| $64$ | Signed: $-2^{63}\sim 2^{63}-1$, unsigned: $0 \sim 2^{64}-1$ |

???+ note "Equivalent ways to write a type"
    As long as it causes no ambiguity, you may leave out some modifier keywords or change their order. This means the same type can be written in several equivalent ways.
    
    For example, `int`, `signed`, `int signed` and `signed int` all name the same type, and `unsigned long` and `unsigned long int` name the same type.

Also, some compilers provide extended integer types. For example, GCC provides 128-bit integers: the signed `__int128_t` and the unsigned `__uint128_t`. If you want to use these types in a contest, **read the contest rules carefully** to make sure extended integer types are allowed and supported.

???+ warning "Warning"
    The STL does not necessarily support extended integer types well, so be extra careful when you use them.
    
    ???+ note "Example code"
        ```cpp
        #include <cmath>
        #include <iostream>
        
        int f1(int n) {
          return abs(n);  // Good
        }
        
        int f2(int n) {
          return std::abs(n);  // Good
        }
        
        __int128_t f3(__int128_t n) {
          return abs(n);  // Bad
        }
        
        // Wrong
        // __int128_t f4(__int128_t n) {
        //   return std::abs(n);
        // }
        
        int main() {
          std::cout << "f1: " << f1(-42) << std::endl;
          std::cout << "f2: " << f2(-42) << std::endl;
          // std::cout << "f3: " << f3(-42) << std::endl; // Wrong
          // std::cout << "f4: " << f4(-42) << std::endl; // Wrong
          return 0;
        }
        ```
    
    The example code above has the following problems:
    
    1.  `__int128_t f3(__int128_t)` uses the C-style absolute value function, whose signature is `int abs(int)`. So `n` is first cast to `int`, and only then is `abs` called.
    2.  `__int128_t f4(__int128_t)` uses the C++-style absolute value function, but there is no overload with the signature `__int128_t std::abs(__int128_t)`, so it does not compile.
    3.  C++ stream output does not support `__int128_t` and `__uint128_t`.
    
    Here is one way to fix it:
    
    ??? note "Fixed code"
        ```cpp
        #include <cmath>
        #include <iostream>
        
        __int128_t abs(__int128_t n) { return n < 0 ? -n : n; }
        
        std::ostream &operator<<(std::ostream &os, __uint128_t n) {
          if (n > 9) os << n / 10;
          os << (int)(n % 10);
          return os;
        }
        
        std::ostream &operator<<(std::ostream &os, __int128_t n) {
          if (n < 0) {
            os << '-';
            n = -n;
          }
          return os << (__uint128_t)n;
        }
        
        int f1(int n) { return abs(n); }
        
        int f2(int n) { return std::abs(n); }
        
        __int128_t f3(__int128_t n) { return abs(n); }
        
        int main() {
          std::cout << "f1: " << f1(-42) << std::endl;
          std::cout << "f2: " << f2(-42) << std::endl;
          std::cout << "f3: " << f3(-42) << std::endl;
        }
        ```

### Character types

Character types are divided into "narrow character types" and "wide character types". Wide character types are almost never used in competitive programming, so only narrow character types are covered here.

A narrow character type usually has $8$ bits. Under the hood it is still stored as an integer, and characters are usually mapped one-to-one to integers through the [ASCII encoding](http://www.asciitable.com/). There are three of them:

-   `signed char`: a signed character type, with range $-128 \sim 127$.
-   `unsigned char`: an unsigned character type, with range $0 \sim 255$.
-   `char` has the same representation and alignment as one of `signed char` or `unsigned char`, but it is always a distinct type.

    Whether `char` is signed depends on the compiler and target platform: the default on ARM and PowerPC is usually unsigned, while the default on x86 and x64 is usually signed.

    In GCC, you can add `-fsigned-char` or `-funsigned-char` to the compiler flags to make `char` behave as `signed char` or `unsigned char`. For other compilers, see their documentation. Note that choosing a signedness different from the architecture's default may break the ABI and make the program stop working correctly.

???+ warning "Warning"
    Unlike the other integer types, `char`, `signed char` and `unsigned char` are **three different types**.
    
    In general, `signed char` and `unsigned char` should not be used to store characters. In the vast majority of cases, both are treated as integer types.

### Floating-point types

Floating-point types store "real numbers" (strictly speaking they are not real numbers, but approximations of real numbers under certain rules). There are three of them:

-   `float`: single-precision floating-point type. If supported, it matches the IEEE-754 binary32 format.
-   `double`: double-precision floating-point type. If supported, it matches the IEEE-754 binary64 format.
-   `long double`: extended-precision floating-point type. If supported, it matches the IEEE-754 binary128 format; otherwise, if supported, it matches the IEEE-754 binary64 extended format; otherwise it matches some non-IEEE-754 extended floating-point format whose precision is better than binary64 and whose range is at least as good as binary64; otherwise it matches the IEEE-754 binary64 format.

| Floating-point format              | Bit width | Largest positive value     | Decimal digits of precision |
| ---------------------- | --------- | -------------------------- | ---------------- |
| IEEE-754 binary32 format   | $32$      | $3.4\times 10^{38}$        | $6\sim 9$        |
| IEEE-754 binary64 format   | $64$      | $1.8\times 10^{308}$       | $15\sim 17$      |
| IEEE-754 binary64 extended format | $\geq 80$ | $\geq 1.2\times 10^{4932}$ | $\geq 18\sim 21$ |
| IEEE-754 binary128 format  | $128$     | $1.2\times 10^{4932}$      | $33\sim 36$      |

> In IEEE-754 floating-point formats, the smallest negative value is the negative of the largest positive value.

Because `float` has a small range and low precision, in practice `double` is usually used for floating-point numbers.

Floating-point types can also hold some special values:

-   Infinity (positive or negative): `INFINITY`.
-   Negative zero: `-0.0`. For example, `1.0 / 0.0 == INFINITY`, `1.0 / -0.0 == -INFINITY`.
-   Not-a-number (NaN): `std::nan`, `NAN`. It is usually produced by operations such as `0.0 / 0.0`. It compares unequal to every value, including itself. Since C++11, you can use `std::isnan` to check whether a floating-point number is NaN.

### The void type

The `void` type means "no type". Unlike the types above, you cannot declare a variable of type `void`. However, a function's return type may be `void`, which means the function returns no value.

### The null pointer type

See the [corresponding section](./pointer.md#空指针) on pointers.

## Fixed-width integer types

Since C++11, fixed-width integers are supported as follows:

-   `<cstdint>`: provides a number of fixed-width integer types, and macro constants such as the maximum and minimum value of each fixed-width integer type.
-   `<cinttypes>`: provides format macro constants for fixed-width integer types, for use with the `std::fprintf` family and the `std::fscanf` family of functions.

The fixed-width integer types are:

-   `intN_t`: a signed integer type with width **exactly** $N$ bits, such as `int32_t`.
-   `int_fastN_t`: the **fastest** signed integer type with width **at least** $N$ bits, such as `int_fast32_t`.
-   `int_leastN_t`: the **smallest** signed integer type with width **at least** $N$ bits, such as `int_least32_t`.

For the unsigned versions, just add the letter u in front of the signed name, such as `uint32_t`, `uint_least8_t`.

The standard requires the following 16 types to be provided:

`int_fast8_t`,`int_fast16_t`,`int_fast32_t`,`int_fast64_t`,

`int_least8_t`,`int_least16_t`,`int_least32_t`,`int_least64_t`,

`uint_fast8_t`,`uint_fast16_t`,`uint_fast32_t`,`uint_fast64_t`,

`uint_least8_t`,`uint_least16_t`,`uint_least32_t`,`uint_least64_t`.

Almost all compilers also provide the following 8 types:

`int8_t`,`int16_t`,`int32_t`,`int64_t`,

`uint8_t`,`uint16_t`,`uint32_t`,`uint64_t`.

When a type is provided, the C++ standard requires macro constants for its maximum value, minimum value and bit width. The macro name is the type name with the trailing `_t` removed, converted to uppercase, plus a suffix:

-   `_MAX` is the maximum value. For example, `INT32_MAX` is the maximum value of `int32_t`.
-   `_MIN` is the minimum value. For example, `INT32_MIN` is the minimum value of `int32_t`.

???+ warning "Warning"
    Fixed-width integer types are really just type aliases of ordinary integer types. So mixing fixed-width integer types with ordinary integer types can cause cross-platform compilation problems. For example:
    
    ???+ note "Example code"
        ```cpp
        #include <algorithm>
        #include <cstdint>
        #include <iostream>
        
        int main() {
          long long a;
          int64_t b;
          std::cin >> a >> b;
          std::cout << std::max(a, b) << std::endl;
          return 0;
        }
        ```
    
    On 64-bit Windows, `int64_t` is usually `long long int`, while on 64-bit Linux it is usually `long int`. Since `std::max` requires both arguments to have the same type, this code fails to compile with GCC on 64-bit Linux, but compiles with MSVC on 64-bit Windows.

In addition, since C++17, `<limits>` provides the class template `std::numeric_limits`, which lets you query properties of the arithmetic types, such as the maximum value, the minimum value, whether the type is an integer type, whether it is signed, and so on.

```cpp
#include <cstdint>
#include <limits>

std::numeric_limits<int32_t>::max();  // maximum value of int32_t, 2'147'483'647
std::numeric_limits<int32_t>::min();  // minimum value of int32_t, -2'147'483'648

std::numeric_limits<double>::min();  // minimum value of double, about 2.22507e-308
std::numeric_limits<double>::epsilon();  // difference between 1.0 and the next representable double,
                                         // about 2.22045e-16
```

## Type conversion

Sometimes (for example, when a function takes an `int` parameter but you pass a `double` variable), a value of one type needs to be converted to another type.

Type conversion in C++ is fairly complicated. Here we mainly cover two kinds of conversion between fundamental types: numeric promotion and numeric conversion.

### Numeric promotion

During numeric promotion, the value itself does not change.

???+ note "Note"
    In C-style variadic arguments, default argument promotion is applied when the values are passed. For example:
    
    ???+ note "Example code"
        ```c
        #include <stdarg.h>
        #include <stdio.h>
        
        void test(int tot, ...) {
          va_list valist;
          int i;
        
          // initialize the variadic argument list
          va_start(valist, tot);
        
          for (i = 0; i < tot; ++i) {
            // get the value of the i-th argument
            double xx = va_arg(valist, double);  // Correct
            // float xx = va_arg(valist, float); // Wrong
        
            // print the underlying bytes of the i-th argument
            printf("i = %d, value = 0x%016llx\n", i, *(long long *)(&xx));
          }
        
          // clean up the memory of the variadic argument list
          va_end(valist);
        }
        
        int main() {
          float f;
          double fd, d;
          f = 123.;   // 0x42f60000
          fd = 123.;  // 0x405ec00000000000
          d = 456.;   // 0x407c800000000000
          test(3, f, fd, d);
        }
        ```
    
    When `test` is called, `f` is promoted to `double`, so its underlying bytes become the same as those of `fd`. The output is
    
    ```text
    i = 0, value = 0x405ec00000000000
    i = 1, value = 0x405ec00000000000
    i = 2, value = 0x407c800000000000
    ```
    
    If you change `double xx = va_arg(valist, double);` to `float xx = va_arg(valist, float);`, GCC should give a warning similar to this:
    
    ```text
    In file included from test.c:2:
    test.c: In function 'test':
    test.c:14:35: warning: 'float' is promoted to 'double' when passed through '...'
      14 |         float xx = va_arg(valist, float);
         |                                   ^
    test.c:14:35: note: (so you should pass 'double' not 'float' to 'va_arg')
    test.c:14:35: note: if this code is reached, the program will abort
    ```
    
    The program will then abort before printing anything.
    
    This also explains why `%f` in `printf` matches both `float` and `double`.

#### Integral promotion

A prvalue of a small integer type (such as `char`) can be converted to a prvalue of a larger integer type (such as `int`).

Specifically, arithmetic operators do not accept types smaller than `int` as operands. After lvalue-to-rvalue conversion, integral promotion is applied automatically where it applies.

The exact rules are:

-   If the source type is `signed char` or `signed short / short`, it can be promoted to `int`.
-   If the source type is `unsigned char` or `unsigned short`, it can be promoted to `int` if `int` can hold the whole range of the source type; otherwise it can be promoted to `unsigned int`. (Since `C++20`, this rule also applies to `char8_t`.)
-   The promotion rule for `char` depends on whether its underlying type is `signed char` or `unsigned char`.
-   `bool` can be converted to `int`: `false` becomes `0`, and `true` becomes `1`.
-   If the range of the target type contains that of the source type, and the range of the source type cannot be contained in `int` or `unsigned int`, then the source type can be promoted to the target type.[^note12]

???+ warning "Warning"
    `char`->`short` is not a numeric promotion. `char` is promoted to `int / unsigned int` first, and then `int / unsigned int`->`short` does not meet the conditions for a numeric promotion.

For example (assuming `int` is 32 bits, `unsigned short` is 16 bits, `signed char` and `unsigned char` are 8 bits, and `bool` is 1 bit):

-   `(signed char)'\0' - (signed char)'\xff'` first promotes `(signed char)'\0'` to `(int)0` and `(signed char)'\xff'` to `(int)-1`, then computes in `int`. The final result is `(int)1`.
-   `(unsigned char)'\0' - (unsigned char)'\xff'` first promotes `(unsigned char)'\0'` to `(int)0` and `(unsigned char)'\xff'` to `(int)255`, then computes in `int`. The final result is `(int)-255`.
-   `false - (unsigned short)12` first promotes `false` to `(int)0` and `(unsigned short)12` to `(int)12`, then computes in `int`. The final result is `(int)-12`.

#### Floating-point promotion

A floating-point number with a smaller bit width can be promoted to one with a larger bit width (for example, when a `float` variable and a `double` variable are used in an arithmetic operation, the `float` variable is promoted to `double`). The value does not change.

### Numeric conversion

During numeric conversion, the value may change.

???+ warning "Warning"
    Numeric promotion takes priority over numeric conversion. For example, `bool`->`int` is a numeric promotion, not a numeric conversion.

#### Integral conversion

<!-- scripts.linter.preprocess.fix_details off -->

-   If the target type is an unsigned integer type of bit width $x$, the result is the original value $\bmod 2^x$.

    -   If the target type is wider than the source type:

        -   If the source type is signed, the value is usually sign-extended first and then converted.

            For example:

            -   When converting `(short)-1` (`(short)0b1111'1111'1111'1111`) to `unsigned int`, sign extension first gives `0b1111'1111'1111'1111'1111'1111'1111'1111`, and integral conversion then gives `(unsigned int)4'294'967'295` (`(unsigned int)0b1111'1111'1111'1111'1111'1111'1111'1111`).
            -   When converting `(short)32'767` (`(short)0b0111'1111'1111'1111`) to `unsigned int`, sign extension first gives `0b0000'0000'0000'0000'0111'1111'1111'1111`, and integral conversion then gives `(unsigned int)32'767` (`(unsigned int)0b0000'0000'0000'0000'0111'1111'1111'1111`).

        -   If the source type is unsigned, the value is zero-extended first and then converted.

            For example, when converting `(unsigned short)65'535` (`(unsigned short)0b1111'1111'1111'1111`) to `unsigned int`, zero extension first gives `0b0000'0000'0000'0000'1111'1111'1111'1111`, and integral conversion then gives `(unsigned int)65'535` (`(unsigned int)0b0000'0000'0000'0000'1111'1111'1111'1111`).

    -   If the target type is not wider than the source type, the value is truncated first and then converted.

        For example, when converting `(unsigned int)4'294'967'295` (`(unsigned int)0b1111'1111'1111'1111'1111'1111'1111'1111`) to `unsigned short`, truncation first gives `0b1111'1111'1111'1111`, and integral conversion then gives `(unsigned short)65'535` (`(unsigned short)0b1111'1111'1111'1111`).

-   If the target type is a signed integer type of bit width $x$, then **in the usual case** the result can be taken as the original value $\bmod 2^x$.[^note13]

    For example, converting `(unsigned int)4'294'967'295` (`(unsigned int)0b1111'1111'1111'1111'1111'1111'1111'1111`) to `short` gives `(short)-1` (`(short)0b1111'1111'1111'1111`).

-   If the target type is `bool`, this is a [Boolean conversion](#boolean-conversion).

-   If the source type is `bool`, `false` becomes 0 of the target type, and `true` becomes 1 of the target type.

<!-- scripts.linter.preprocess.fix_details on -->

#### Floating-point conversion

When a wider floating-point number is converted to a narrower one, it is rounded to the nearest value representable in the target type.

#### Floating–integral conversion

-   When a floating-point number is converted to an integer, its whole fractional part is discarded.

    If the target type is `bool`, this is a [Boolean conversion](#boolean-conversion).

-   When an integer is converted to a floating-point number, it is rounded to the nearest value representable in the target type.

    If the value does not fit in the target type, the behavior is undefined.

    If the source type is `bool`, `false` becomes zero and `true` becomes one.

#### Boolean conversion

When another type is converted to `bool`, a zero value becomes `false` and a non-zero value becomes `true`.

## Defining variables

Simply put[^note14], to define a variable you need a type specifier (which gives the variable's type) and the name of the variable.

For example, each of the following statements defines a variable.

```cpp
int oi;
double wiki;
char org = 'c';
```

In the code we have seen so far, variables defined inside curly braces are local variables, and variables defined outside any curly braces are global variables. There are exceptions, but you don't need to know them for now.

A global variable defined without an initial value is initialized to $0$. Local variables do not have this property. You must give them an initial value yourself, or you may get bugs that are hard to find.

## Variable scope

The scope of a variable is the block of code in which the variable can be used.

The scope of a global variable starts where it is defined[^note15] and ends at the end of the file.

The scope of a local variable starts where it is defined and ends at the end of its code block.

A code block is a group of statements enclosed in a pair of curly braces.

```cpp
int g = 20;  // define a global variable

int main() {
  int g = 10;         // define a local variable
  printf("%d\n", g);  // print g
  return 0;
}
```

If a nested block defines a variable with the same name as one in an outer block, the inner block can no longer access the outer variable with that name.

For example, in the code above, the printed value of $g$ is $10$. So to avoid unexpected mistakes, try not to give local variables the same names as global variables.

## Constants

A constant is a fixed value that does not change while the program runs.

The value of a constant cannot be changed after it is defined. To define one, just add the `const` keyword.

```cpp
const int a = 2;
a = 3;
```

If you try to change the value of a constant, you get an error at compile time: `error: assignment of read-only variable 'a'`.

## References and notes

1.  [Working Draft, Standard for Programming Language C++](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/n4917.pdf)
2.  [Types - cppreference.com](https://zh.cppreference.com/w/cpp/language/type)
3.  [Arithmetic types - cppreference.com](https://zh.cppreference.com/w/c/language/arithmetic_types) in C
4.  [Fundamental types - cppreference.com](https://zh.cppreference.com/w/cpp/language/types)
5.  [Fixed-width integer types (since C++11) - cppreference.com](https://zh.cppreference.com/w/cpp/types/integer)
6.  William Kahan (1 October 1997).["Lecture Notes on the Status of IEEE Standard 754 for Binary Floating-Point Arithmetic"](https://people.eecs.berkeley.edu/~wkahan/ieee754status/IEEE754.PDF).
7.  [Implicit conversions - cppreference.com](https://zh.cppreference.com/w/cpp/language/implicit_conversion)
8.  [Declarations - cppreference](https://zh.cppreference.com/w/cpp/language/declarations)
9.  [Scope - cppreference.com](https://zh.cppreference.com/w/cpp/language/scope)

[^note10]: See <https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3054.pdf>

[^note11]: These include array types, reference types, pointer types, class types, function types and so on. This article is written for beginners, so they are not covered in detail here. For details, see [Types - cppreference.com](https://zh.cppreference.com/w/cpp/language/type)

[^note12]: Not including wide character types, bit-fields and enumeration types. For details, see [Integral conversions - cppreference](https://zh.cppreference.com/w/cpp/language/implicit_conversion#.E6.95.B4.E5.9E.8B.E8.BD.AC.E6.8D.A2).

[^note13]: This applies since C++20. Before C++20, the result is implementation-defined. For details, see [Integral conversions - cppreference](https://zh.cppreference.com/w/cpp/language/implicit_conversion#.E6.95.B4.E5.9E.8B.E8.BD.AC.E6.8D.A2).

[^note14]: When defining a variable, you can also use other specifiers besides the type specifier. For details, see [Declarations - cppreference](https://zh.cppreference.com/w/cpp/language/declarations).

[^note15]: More precisely, the [point of declaration](https://zh.cppreference.com/w/cpp/language/scope#.E5.A3.B0.E6.98.8E.E7.82.B9).

[^note16]: Before C++20, signed integers were only required to cover at least the range of [ones' complement](../math/bit.md#整数与位序列) (that is, $-2^{x-1}+1\sim 2^{x-1}-1$), but in practice nearly all implementations use [two's complement](../math/bit.md#整数与位序列). Since C++20, signed integers are required to use two's complement. For details, see [Range of values - cppreference](https://en.cppreference.com/w/cpp/language/types.html#Range_of_values).
