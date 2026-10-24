## Code skeleton

If you don't want to dig into the details behind it yet, when you're starting out you can simply memorize this "skeleton":

```cpp
#include <cstdio>
#include <iostream>

int main() {
  // do something...
  return 0;
}
```

??? note "What is include?"
    `#include` is actually a preprocessor directive. It means "put" a file at the place of this statement; the file being "put" there is called a header file. In other words, during compilation the compiler "copies" the contents of the header file `iostream` and "pastes" them where the statement `#include <iostream>` is. That way you can use the objects provided by `iostream`, such as `std::cin`, `std::cout` and `std::endl`.
    
    If you have learned C, you will notice that the C++ header files we have seen so far usually have no `.h` suffix, and the C header files `xx.h` have become `cxx`; for example, `stdio.h` became `cstdio`. To stay compatible with C, C++ uses the C header files directly, and it adds a `c` prefix to tell C++ headers apart from C headers.
    
    In general, you should decide which header files to `#include` based on what your C++ program needs. But if you `#include` extra header files, it only increases compile time and has almost no effect on running time. So far we have only seen the two header files `iostream` and `cstdio`. If you only need `scanf` and `printf`, you can leave out `#include <iostream>`.
    
    Can you `#include` a header file you wrote yourself? Yes, you can.
    
    You can write your own header file, such as `myheader.h`. Then put it in the same directory as your code and write `#include "myheader.h"`. Note that your own header files must use quotes instead of angle brackets. Of course, you can also use the compiler option `-I <header_file_path>` to tell the compiler where to look for header files, and then you don't need to put the header file in the same directory as your code.

??? note "What is `main()`?"
    You can think of it this way: when the program runs, it executes the code in `main()`.
    
    In fact, the `main` function is called by the system or by an external program. For example, when you run your program from the command line, you are calling the `main` function in your program (before that, the global [variables](./var.md) are constructed).
    
    The final `return 0;` means the program ran successfully. By default, returning 0 when the program ends means everything is fine; otherwise the return value is an error code (on Windows, you can look up the hexadecimal value of this error code on the [Windows Error Codes website](https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-erref/)). Who receives this value? It is the system or external program that called your program; it receives this return value when your program ends. If you don't write a `return` statement, the default return value when the program ends normally is also 0.
    
    In C or C++, a nonzero return value from the program causes a runtime error (RE).

## Comments

In C++ code, there are two ways to write comments:

1.  Line comments

    They start with `//`, and everything after it on that line is a comment.

2.  Block comments

    They start with `/*` and end with `*/`. Everything between them is a comment, and it can span several lines.

Comments have no effect on how the program runs. You can use them to explain what the program means, or to keep a piece of code from running (while still keeping it in the source file).

In software engineering, comments make the code easier to maintain later and easier for others to read.

In OI, few people write a lot of comments. Still, comments can help you sort out your ideas while writing code, or help you review later. And if you write editorials or tutorials, a reasonable number of comments helps readers follow the code and understand what it is meant to do. We hope everyone gets into the good habit of writing comments.

## Input and output

### `cin` and `cout`

```cpp
#include <iostream>

int main() {
  int x, y;                          // Declare variables
  std::cin >> x >> y;                // Read x and y
  std::cout << y << std::endl << x;  // Print y, a newline, then x
  return 0;                          // End the main function
}
```

???+ note "What is a variable?"
    See the [Variables](./var.md) page.

???+ note "What is `std`?"
    std is the **namespace** used by the C++ standard library. Namespaces are used to avoid name clashes.
    
    For details about namespaces, see the [Namespaces](./namespace.md) page.

### `scanf` and `printf`

`scanf` and `printf` are actually functions provided by C. In most cases they are faster than `cin` and `cout`, and they make it easy to control the input and output format.

???+ note "Fast input and output"
    For the exact differences between `cin`/`cout` and `scanf`/`printf`, and for fast I/O techniques, see the [Fast I/O](../contest/io.md) page.

```cpp
#include <cstdio>

int main() {
  int x, y;
  scanf("%d%d", &x, &y);   // Read x and y
  printf("%d\n%d", y, x);  // Print y, a newline, then x
  return 0;
}
```

Here, `%d` means the variable being read or printed is a signed integer (of type `int`).

Similarly:

1.  `%s` means a string.
2.  `%c` means a character.
3.  `%lf` means a double-precision floating-point number (`double`).
4.  `%lld` means a long integer (`long long`). Depending on the system, it may also be `%I64d`.
5.  `%u` means an unsigned integer  (`unsigned int`).
6.  `%llu` means an unsigned long integer (`unsigned long long`); it may also be `%I64u`.

Besides type specifiers, there are also ways to control the format. Most of them are rarely used; here are two common ones:

1.  `%1d` means an integer of length 1. When reading, it can read a number one digit at a time even without spaces. When printing, if the given length is larger than the number of digits, the number is padded with spaces in front. If the given length is smaller than the number of digits, it has no effect.
2.  `%.6lf` is used for output and keeps six digits after the decimal point.

You can put other numbers in the corresponding places of these two specifiers. For example, `%.3lf` keeps three digits after the decimal point.

??? note "What are \"double-precision floating-point number\" and \"long integer\"?"
    These are types of variables. As above, they will be explained together in [Variables](./var.md).

??? note "Why is there an `&` operator in `scanf`?"
    Here `&` is the address-of operator; it returns the address of the variable in memory. The arguments scanf takes are the addresses of the variables. A complete and clear explanation may have to wait until [Pointers](./pointer.md); for now, just remember it.

??? note "What is `\n`?"
    `\n` is an **escape character**; it means a newline.
    
    Escape characters represent characters that cannot be typed directly: for example, the newline, which cannot be typed because a string literal cannot span lines; quotes, which cannot be typed because they have a special meaning; and the backslash, which cannot be typed because it marks escape characters.
    
    Common escape characters are:
    
    1.  `\t` means a tab.
    
    2.  `\\` means `\`.
    
    3.  `\"` means `"`.
    
    4.  `\0` means the null character, which marks the end of a C-style string.
    
    5.  `\r` means a carriage return. On Linux the line break is `\n`, and on Windows it is `\r\n`. In OI, if your output needs a line break, just use `\n`. When reading input character by character, however, line breaks may cause problems, so be careful. For example, `gets` treats `\n` as the end of the string; if the line break is `\r\n`, the `\r` stays at the end of the string.
    
    6.  As a special case, `%%` means `%`. It is only used in `printf` or `scanf`; in other string literals you simply write `%`.
    
    ??? note "What is a literal?"
        A "literal" is a piece of code that is used directly as a value. For example, `3` is an `int` literal and `'c'` is a char literal. The `"hello world"` in the program we wrote above is also a string literal.
        
        Literals that appear without explanation or reason are also called "magic numbers". If other people need to read your code, this practice is strongly discouraged.

## Some extra topics

### Whitespace in C++

In C++, all whitespace characters (spaces, tabs, newlines), whether one or many, are treated the same. (Of course, this does not apply to whitespace inside quotes that is part of a string.)

So you can use any code style you like (except that line comments, string literals and preprocessor directives must stay on a single line). For example:

```cpp
--8<-- "docs/lang/code/basic/basic_1.cpp:main"
```

Of course, doing this is not recommended.

Here is a code style that is also widely used, but differs from the style required by **OI Wiki**:

```cpp
--8<-- "docs/lang/code/basic/basic_2.cpp:main"
```

### The `#define` directive

`#define` is a preprocessor directive used to define macros. In essence it is text replacement. For example:

```cpp
#include <iostream>
#define n 233

// n is not a variable; the compiler replaces every n text in the code with 233.
// But n as part of an identifier is not replaced: fn does not become f233. Likewise, n inside strings is not replaced

int main() {
  std::cout << n;  // Prints 233
  return 0;
}
```

??? note "What is an identifier?"
    An identifier is a sequence of characters that can be used as a variable name. For example, `abcd` and `abc1` are valid identifiers, while `1a` and `c+b` are not.
    
    An identifier starts with an English letter or an underscore, and may only contain English letters, underscores and digits. Note that keywords (such as `int`, `for`, `if`) cannot be used as identifiers.

??? note "What is a preprocessor directive?"
    A preprocessor directive is a command accepted by the preprocessor. It performs an initial text transformation of the code, such as file inclusion with `#include` and macro handling with `#define`. GCC does not keep the output of the preprocessing stage (the `.i` file) by default; you can use the `-E` option to keep it.

Macros can take parameters, and a macro with parameters can be used like a function:

```cpp
#include <iostream>
#define sum(x, y) ((x) + (y))
#define square(x) ((x) * (x))

int main() {
  std::cout << sum(1, 2) << ' ' << 2 * sum(3, 5) << std::endl;  // Prints 3 16
}
```

But a macro with parameters is different from a function. Because a macro is text replacement, it causes many problems. For example:

```cpp
#include <iostream>
#define sum(x, y) x + y
// This should be #define sum(x, y) ((x) + (y))
#define square(x) ((x) * (x))

int main() {
  std::cout << sum(1, 2) << ' ' << 2 * sum(3, 5) << std::endl;
  // Prints 3 11, because #define is text replacement: the second expression becomes 2 * 3 + 5
  int i = 1;
  std::cout << square(++i) << ' ' << i;
  // The output is undefined, because ++i is executed twice,
  // and modifying the same variable more than once in one statement is undefined behavior (with exceptions)
}
```

Using `#define` is risky (the scope of `#define` is the whole program, so text may be replaced by accident, and you need to cancel the definition with `#undef` in time), so use it with care. The recommended approach is to declare constants with the `const` qualifier and use functions instead of macros.

In OI, however, `#define` still has its uses (the two below are discouraged because they make the code less clean):

1.  `#define int long long`+`signed main()`. This is usually used to avoid bugs from forgetting to use long long, or to rule out that possibility while debugging. (It may also increase the constant factor and even cause TLE, or use too much memory and cause MLE.)
2.  `#define For(i, l, r) for (int i = (l); i <= (r); ++i)`, `#define pb push_back`, `#define mid ((l + r) / 2)`, used to make code shorter.

Still, `#define` also has advantages. For example, combined with preprocessor directives such as `#ifdef` it works very well:

```cpp
#ifdef LINUX
// code for linux
#else
// code for other OS
#endif
```

You can control which code gets compiled with `-DLINUX` at compile time, without changing the source file. This has another advantage: an executable compiled with `-DLINUX` contains no code for other operating systems, because that code was already removed during preprocessing.

`#define` can also use the `#` and `##` operators, which make debugging much easier.
