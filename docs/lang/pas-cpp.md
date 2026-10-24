author: kexplorning, Ir1d, lvneg1

## Quick C++ installation and environment setup

All of the following is done on Windows.

### Using an IDE

See the following pages:

-   [Dev-C++](../tools/editor/devcpp.md)
-   [Code::Blocks](../tools/editor/codeblocks.md)

### Using a code editor + compiler + debugger

See the [VS Code](../tools/editor/vscode.md) page. The official Visual Studio Code website has documentation on how to set up C++. In general, VS Code is more convenient with extensions; see the [official VS Code website](https://code.visualstudio.com/).

## A quick overview of C++ syntax

Every C++ program starts running from the `main` part.

Braces mark the start and end of a block statement: `{` is like `begin` in Pascal, and `}` is like `end`.

Note that, as in Pascal, each C++ statement ends with a semicolon `;`. However, a closing brace doesn't need a semicolon, and the program doesn't end with a full stop `.`.

For comments, `//` starts a line comment and `/* */` is a block comment.

As is tradition, let's look at Hello World.

### Hello World: your first C++ program

```cpp
#include <iostream>  // include the iostream library

int main()  // the main part
{
  std::cout << "Hello World!" << std::endl;

  return 0;
}
```

Then compile and run it to see the result.

#### Brief explanation

The first line, `#include <iostream>`, means to include the `iostream` library.

??? note "Pascal's library files"
    Pascal actually does have library files; it's just that many students have never used them...

See `main` on the third line? The program starts running from `main`.

The most important line comes next:

```cpp
std::cout << "Hello World!" << std::endl;
```

`std::cout` is the output command. You may have seen some C++ programs that just write `cout`.

??? note "About the std:: prefix"
    For the `std::` prefix, see the note "What is std?" at the bottom of [this section](basic.md#cin-and-cout).

The `<<` in the middle is a vivid picture of flow; it shows how the output "flows". This line means that `"Hello World!"` is pushed to the output stream first, and then `std::endl` is pushed to the output stream.

`std::endl` is the command to **output** a newline. It is similar to Pascal's `writeln`, but C++ has no `coutln`. The difference between Pascal and C++ is that `write('Hello World!')` is equivalent to `std::cout << "Hello World!"`, while `writeln('Hello World!')` is equivalent to `std::cout << "Hello World!" << std::endl`.

Here `"Hello World!"` is a string. In Pascal, strings use single quotes `'` and cannot use double quotes, while C++ strings must use double quotes. In C++, a character in single quotes means something else, which we'll come back to later.

Well, that's about all there is to explain about Hello World.

Some of you may ask: what does the `return 0` at the end mean? What does `int main()` mean? **Don't worry about it for now.** When you start writing programs, just treat it as a template (this example was written from a template too). Since beginners don't use the parameters of `main`, there is no need to write `int main(int argc, char const *argv[])`.

#### Simple exercises

1.  Try printing a different string.
2.  Try to learn about escape characters.

### A+B Problem: your second C++ program

The classic A+B Problem.

```cpp
#include <iostream>

int main() {
  int a, b, c;

  std::cin >> a >> b;

  c = a + b;

  std::cout << c << std::endl;

  return 0;
}
```

Note: the code has a lot of blank lines; remove them if you don't like them.

#### Brief explanation

`std::cin` reads input (`cin` means C-in), and `>>` works similarly to the output syntax.

Of the new statements here, two are the most important. One is the variable declaration.

```cpp
int a, b, c;
```

You may be used to declaring variables in Pascal:

```pas
var
a, b, c: integer;
```

A C++ declaration starts directly with the name of the data type. Here, starting with `int` (integer) means we are about to declare variables.

The other most important statement is the assignment.

```cpp
c = a + b;
```

This is a big syntax difference between Pascal and C++: assignment in Pascal is `:=`, while in C++ it is `=`; and in C++, testing for equality is `==`.

C++ also lets you initialize variables directly when declaring them.

```cpp
int a = 0, b = 0, c = 0;
```

#### Simple exercises

1.  Rewrite the code, submit it to an OJ, and get AC.
2.  For more input/output syntax, see [this section](basic.md#scanf-and-printf), and try to learn about formatted output in C++.

### Wrap-up and next steps

Well, by now you have learned some of the most basic things. What's left is to find the matching syntax and the differences between Pascal and C++.

Before that, though, we strongly recommend reading [Variable scope: global and local variables](#variable-scope-global-and-local-variables) first.

Use <kbd>Alt</kbd>+<kbd>←</kbd> and <kbd>Alt</kbd>+<kbd>→</kbd> to jump back and forth.

## Syntax

### Variables

#### Basic data types

C++ is basically the same as Pascal here. Common types are

-   `bool`: Boolean
-   `int`: integer
-   `float`: single-precision floating point
-   `double`: double-precision floating point
-   `char`: character
-   `void`: no type

In C++, single quotes are used only for single characters (the character type), such as `'a'`, while strings (character arrays) must use double quotes.

C++ has many more data types; see [Fundamental types - cppreference.com](https://zh.cppreference.com/w/cpp/language/types).

#### Constant declarations

```cpp
const double PI = 3.1415926;
```

If you're not sure about the issues with macro expansion, use constants instead of macros.

### Operators

See the [operators](./op.md) article directly. The appendix also has a comparison table of operator and math function syntax.

### Conditions

#### The `if` statement

```pas
if (a = b) and (a > 0) and (b > 0) then
    begin
        b := a;
    end
else
    begin
        a := b;
    end;
```

```cpp
if (a == b && a > 0 && b > 0) {
  b = a;
} else {
  a = b;
}
```

Boolean operations and comparisons

-   `and -> &&`
-   `or -> ||`
-   `not -> !`
-   `= -> ==`
-   `<> -> !=`

Notes:

1.  Pascal's `and` and C++'s `&&` have different precedence, so in C++ you don't need to put parentheses around each condition.
2.  In Pascal, testing equality is `=` and assignment is `:=`; in C++, testing equality is `==` and assignment is `=`.
3.  If you write `a = b` instead of `a == b` inside the parentheses of an `if` statement, the program doesn't report an error. Instead it assigns `b` to `a`, and the whole assignment expression `a = b` takes the value of `a` after the assignment.
4.  In C++ you don't need to think about whether to put a semicolon after `end`.
5.  In C++ Boolean operations, non-Boolean values are automatically converted to Boolean values.

???+ warning "Common mistake"
    Be especially careful: **don't write `==` as `=`!**
    
    Since C/C++ syntax is more flexible than Pascal's, if you write `if (a=b)` in a condition, the program will happily keep running, because in C++ `a=b` has a value.

#### `case` and `switch`

These aren't used much, so we won't go into detail here.

Note: C++ has no `1..n`, and no chained inequalities (like `1 < x < 2`).

### Loops

The three kinds of loops and six pieces of code below all do the same thing.

#### The `while` loop

`while` is very similar. (The C++ here is not a complete program; some boilerplate is left out. The same applies below.)

```pas
var i: integer;

begin
    i := 1;
    while i <= 10 do
        begin
            write(i,' ');
            inc(i); // or i := i + 1;
        end;
end.
```

```cpp
int i = 1;
while (i <= 10) {
  std::cout << i << " ";
  i++;
}
```

#### The `for` loop

The C++ `for` statement is very different.

```pas
var i: integer;

begin
    for i:= 1 to 10 do
        begin
            write(i, ' ');
        end;
end.
```

```cpp
for (int i = 1; i <= 10; i++) {
  std::cout << i << " ";
}
```

Notes:

1.  The line `for (int i = 1; i <= 10; i++){` has a lot in it: there are three statements inside the `for`.
2.  The first statement, `int i = 1;`, declares a local variable `i` and initializes it. (This design is much more sensible than Pascal's.)
3.  The second statement, `i <= 10;`, is the condition for deciding whether the loop continues.
4.  The third statement, `i++`, runs at the end of each iteration. It means roughly the same as `inc(i)` in Pascal; writing `++i` here works the same way. For the difference between `i++` and `++i`, see other materials.

#### `repeat until` and `do while` loops

Note that `repeat until` and `do while` are different. Compare the following code

```pas
var i: integer;

begin
    i := 1;
    repeat
        write(i, ' ');
        inc(i);
    until i = 11;
end.
```

```cpp
int i = 1;
do {
  std::cout << i << " ";
  i++;
} while (i <= 10);
```

#### Loop control

In C++, `break` does the same thing as in Pascal: it exits the loop.

`continue` is also the same: it skips the rest of the current iteration and moves on to the next one (back to the start).

### Arrays and strings

#### Variable-length arrays: the standard library type vector

See the [sequence containers](csl/sequence-container.md) page.

The C++ standard library provides `vector`, which is like a variable-length array. You need to include its header before using it.

```cpp
#include <iostream>
#include <vector>  // include the vector library

int main() {
  std::vector<int> a;  // declare vector a and define a as an empty vector object
  int n;

  std::cin >> n;
  // read a
  for (int i = 0; i < n; i++) {
    int t;
    std::cin >> t;
    a.push_back(t);  // put the number t that was read at the end of vector a; this takes O(1)
    /* You can't assign by index here, because a is still empty after its declaration,
    so writing `a[i] = t;` here is wrong.
    */
  }

  // print all the numbers read into a
  for (int i = 0; i < n; i++) {
    std::cout << a[i] << ", ";  // !note: the first number in a is a[0];
    // if the index is out of range, it returns an unknown value (overflow) instead of reporting an error
  }
  std::cout << std::endl;

  return 0;
}
```

Accessing array elements in C++ is similar to Pascal, with one important difference: the first element of an array is `a[0]`, whereas in Pascal you can choose the starting index yourself.

#### Strings: the standard library type string

See the [string](csl/string.md) page.

The C++ standard library provides `string`. It supports some of the same operations as `vector`, and you also need to include its header.

```cpp
#include <iostream>
#include <string>

int main() {
  std::string s;  // declare string s

  std::cin >> s;  // read s;
  // reading skips all leading whitespace (spaces, newlines, tabs), and the string read stops at the next whitespace character.

  std::cout << s << std::endl;

  return 0;
}
```

#### C-style arrays

See the [arrays](array.md) page.

If you need a variable-length array, use `vector`, not a C-style array.

C-style arrays are closely tied to pointers, so we won't go into them here.

## Important differences

### Variable scope: global and local variables

In C++ you can declare variables almost **anywhere**. See [variable scope](var.md#variable-scope).

When writing Pascal procedures/functions, it is easy to forget to declare local variables `i` or `j`. The main program usually has loops, so in most cases `i` and `j` end up being global variables, and operating on `i` inside a procedure/function then very easily goes wrong. Worse, if you forget to declare such a local variable, the compiler doesn't report an error and the program runs. (Many hard-to-find bugs come from this.)

So in C++, when declaring variables, such as an `i` used in a loop, **don't use global variables; use local variables whenever you can**. If you do this, you don't need to worry about variable names (such as `i`) clashing inside functions.

??? note "Extra note"
    Pascal can avoid this problem to some extent by copying the C++ approach: the main program only calls procedures/functions and doesn't declare global variables like `i` and `j` that clash very easily. If a loop is needed, write a separate procedure and call it.

### C++ can convert types automatically

```cpp
int i = 2;
if (i) {  // i = 0 gives false; anything else gives true
  std::cout << "true";
} else {
  std::cout << "false";
}
```

It's not just `int` to `bool`; `int` and `float` also convert to each other. In Pascal you can assign an integer to a floating-point variable but not the other way around. C++ doesn't have this problem.

```cpp
int a;
a = 3.2;      // now a = 3
float b = a;  // now b = 3.0
```

Whether `/` is integer division or floating-point division is decided by the types of the dividend and the divisor

```cpp
float a = 32 / 10;    // 32/10 gives 3 (integer division); a = 3.0
float b = 32.0 / 10;  // 32.0/10 gives 3.2; b = 3.2
```

`pow(a, b)` computes $a^b$. It returns a floating-point value, but if you use it directly to compute a power of integers, the automatic conversion means you don't need to worry about errors

```cpp
int a = pow(2, 3);  // compute 2^3
```

`char` and `int` also convert to each other.

```cpp
char a = 48;              // ASCII 48 is '0'
int b = a + 1;            // b = 49
std::cout << (a == '0');  // true, prints 1
```

In fact, `char` and `bool` in C++ are really integer types.

For details, see [Implicit conversions - cppreference.com](https://zh.cppreference.com/w/cpp/language/implicit_conversion).

### Many C++ statements have values: reading an unknown amount of data as an example

Sometimes you need to read until the data runs out. For example, to sum a group of numbers whose count is not given (the data may span several lines) until the end of the file, you can do this

??? note "End of file (EOF)"
    EOF is the end-of-file marker. On the command line, on Windows you enter it with <kbd>Ctrl</kbd>+<kbd>Z</kbd> (then press <kbd>Enter</kbd>); on Unix-like systems you enter it with <kbd>Ctrl</kbd>+<kbd>D</kbd>.

```cpp
#include <iostream>

int main() {
  int sum = 0, a = 0;

  while (std::cin >> a) {
    sum += a;
  }
  std::cout << sum << std::endl;

  return 0;
}
```

How it works: in `while (std::cin >> a)`, if there is a problem with the input or the end of the file is reached, `std::cin >> a` returns `false`, which ends the loop.

### Functions

C++ only has functions, not procedures, but it has `void`. It has no function-result variable, but it has `return`.

A comparison of a Pascal function and a C++ function:

```pas
function abs(x:integer):integer;
begin
    if x < 0 then
        begin
            abs := -x;
        end
    else
        begin
            abs := x;
        end;
end;
```

```cpp
int abs(int x) {
  if (x < 0) {
    return -x;
  } else {
    return x;
  }
}
```

In C++, the declaration `int abs` defines the function `abs()` with return type `int` (integer). The function's return value is the value given by the `return` statement.

If you don't want a return value (a "procedure" in Pascal), use `void`. `void` means "empty": it returns nothing.

```pas
var ans: integer;

procedure printAns(ans:integer);
begin
    writeln(ans);
end;

begin
    ans := 10;
    printAns(ans);
end.
```

```cpp
#include <iostream>

void printAns(int ans) {
  std::cout << ans << std::endl;

  return;
}

int main() {
  int ans = 10;
  printAns(ans);

  return 0;
}
```

C++'s `return` differs from assigning to the function variable in Pascal in one very big way. C++'s `return` returns a value, and once this statement runs, the function ends. In Pascal, assigning to the function variable does not leave the function; execution continues. So if Pascal needs to stop a function/procedure somewhere, it needs an extra command, `exit`. C++ doesn't: if you need to stop somewhere, you can just use `return`. For example (we couldn't think of short and practical code, so this will have to do)

```cpp
#include <iostream>

void printWarning(int x) {
  if (x >= 0) {
    return;  // here this statement is equivalent to `exit;` in Pascal
  }
  std::cout << "Warning: input a negative number.";
}

int main() {
  int a;

  std::cin >> a;
  printWarning(a);

  return 0;
}
```

In a sense, this is what the earlier `abs` function is strictly equivalent to

```pas
function abs(x:integer):integer;
begin
    if x < 0 then
        begin
            abs := -x; exit; // !note this
        end
    else
        begin
            abs := x;  exit; // !note this
        end;
end;
```

```cpp
int abs(int x) {
  if (x < 0) {
    return -x;
  } else {
    return x;
  }
}
```

???+ note "Special reminder"
    In C++, `exit` exits the whole program. Don't type `exit` out of habit; use `return`!

C++ treats both functions and procedures as functions, and even `main` is no exception. When you write `int main`, C++ treats `main` as a function returning an integer, here `0`. It's a convention: returning `0` means the program exited normally.

As you may have guessed, the parameters in `main(int argc, char const *argv[])` are `int argc` and `char const *argv[]`. For what they mean, see other materials.

### Passing parameters to functions

C++ has no `var` keyword like Pascal for changing the arguments passed in, but C++ can achieve the same effect with references and pointers.

```pas
var a, b: integer;

procedure swap(var x,y:integer);
var temp:integer;
begin
    temp := x;
    x := y;
    y := temp;
end;

begin
    a := 10; b:= 20;    
    swap(a, b);
    writeln(a, ' ', b);
end.
```

```cpp
// code using pointers
#include <iostream>

void swap(int* x, int* y) {
  int temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

int main() {
  int a = 10, b = 20;
  swap(&a, &b);
  std::cout << a << " " << b;

  return 0;
}
```

Note that this C++ code **involves pointers**. Pointers can be quite tricky; we suggest reading related materials.

```cpp
// code using references
#include <iostream>

void swap(int& x, int& y) {
  int temp;
  temp = x;
  x = y;
  y = temp;
}

int main(int argc, char const* argv[]) {
  int a = 10, b = 20;
  swap(a, b);
  std::cout << a << " " << b;

  return 0;
}
```

Note that this C++ code involves **reference types**. When using references with some STL or template libraries, you may run into problems, and then you need to declare the types manually. You can look up the details in *C++ Primer* (5th edition) or online.

There are other ways to pass parameters to functions in C++. One is to **pass them through global variables**. If you don't know how to use pointers yet, you can use this method for now. Its drawback is that there is no stack to save the data, so **you can't pass parameters this way in recursive functions**. (Unless you write your own stack. Note that a hand-written stack is also a way to get around the system stack limit.)

## The C++ standard library and references

Never reinvent the wheel (unless it's for practice). Before writing some feature yourself, check whether a function or data structure for it already exists.

### The C++ standard library

`<algorithm>` in the C++ standard library has many useful functions, such as quicksort and binary search, which you can call directly. See the [STL algorithms](csl/algorithm.md) page.

There are also STL containers, such as arrays, vectors (resizable arrays), queues and stacks, which come with many functions. See the [Introduction to STL containers](csl/container.md) page.

For string manipulation functions, see

-   [std::basic\_string - cppreference.com](https://zh.cppreference.com/w/cpp/string/basic_string)
-   [`<string>`- C++ Reference](https://www.cplusplus.com/reference/string/)

Pointers in C/C++ are very flexible; see the [pointers](pointer.md) page. If you want to fully understand pointers, we suggest reading a book or reference manual carefully.

### Debugging and tips

-   [Common mistakes](../contest/common-mistakes.md)
-   [Common tricks](../contest/common-tricks.md)

### C++ language resources

-   [Learning resources](../contest/resources.md)
-   [cppreference.com](https://zh.cppreference.com/): the most important C/C++ reference
-   [C++ Tutorial - Runoob](https://www.runoob.com/cplusplus/cpp-tutorial.html)
-   [C++ Language - C++ Tutorials](https://www.cplusplus.com/doc/tutorial/)
-   [Reference - C++ Reference](https://www.cplusplus.com/reference/)
-   [C++ Standard Library - Wikipedia](https://en.wikipedia.org/wiki/C%2B%2B_Standard_Library)
-   [The Ultimate Question of Programming, Refactoring, and Everything](https://www.gitbook.com/book/alexastva/the-ultimate-question-of-programming-refactoring-/details)
-   [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

## Afterword

At this point, many of you may feel this isn't much of a crash course at all, and that lots of things weren't mentioned. That can't be helped.

Although this is meant as a crash course, many things, such as how to convert a string to a number or how to search for a character in a string, don't fit in a short and focused crash-course post. If we wrote all of them down, it would become an introductory C++ tutorial. So please make good use of this wiki, reference manuals and search engines.

One thing worth pointing out: much of what we called C++ syntax above actually comes from the C language, so a better title would be "A Crash Course for Switching from Pascal to C/C++".

Pascal was a very popular language in the second half of the last century, and it predates C. But as UNIX spread and Microsoft used C, Pascal has now become history. Pascal did keep developing later, for example with the open-source compiler project Free Pascal and the addition of object-oriented features (the Delphi language). Apart from informatics olympiads, Pascal today has one feature other languages lack: its compilers support a huge number of old machines, such as the Game Boy, a Nintendo console from the last century. Another use is as pseudocode (Pascal-style pseudocode) in all kinds of textbooks.

Finally, the Pascal community is actually very small, while the C/C++ community is huge, with many complete help manuals and tutorials. Be sure to get good at English. There are many, many other programming languages in the world, and computer science as a subject and technology is about much more than informatics olympiads and programming languages.

### References for Pascal in this article

-   [Lazarus wiki](https://wiki.freepascal.org/)
-   [Free Pascal Reference guide](https://freepascal.org/docs-html/current/ref/ref.html)

## Appendix: comparison of Pascal and C++ operator and math function syntax

Only the most common operators and functions are included.

### Basic arithmetic

|                         | Pascal    | C++     |
| ----------------------- | --------- | ------- |
| Addition                | `a + b`   | `a + b` |
| Subtraction             | `a - b`   | `a - b` |
| Multiplication          | `a * b`   | `a * b` |
| Integer division        | `a div b` | `a / b` |
| Floating-point division | `a / b`   | `a / b` |
| Modulo                  | `a mod b` | `a % b` |

### Logic

|     | Pascal    | C++                   |
| --- | --------- | --------------------- |
| NOT | `not(a)`  | `!a`                  |
| AND | `a and b` | `a && b`              |
| OR  | `a or b`  | <code>a \|\| b</code> |

### Comparison

|                          | Pascal   | C++      |
| ------------------------ | -------- | -------- |
| Equal                    | `a = b`  | `a == b` |
| Not equal                | `a <> b` | `a != b` |
| Greater than             | `a > b`  | `a > b`  |
| Less than                | `a < b`  | `a < b`  |
| Greater than or equal to | `a >= b` | `a >= b` |
| Less than or equal to    | `a <= b` | `a <= b` |

### Assignment

| Pascal                         | C++      |
| ------------------------------ | -------- |
| `a := b`                       | `a = b`  |
| `a := a + b`                   | `a += b` |
| `a := a - b`                   | `a -= b` |
| `a := a * b`                   | `a *= b` |
| `a := a div b` or `a := a / b` | `a /= b` |
| `a := a mod b`                 | `a %= b` |

### Increment/decrement

|           | Pascal   | C++   |
| --------- | -------- | ----- |
| Increment | `inc(a)` | `a++` |
| Increment | `inc(a)` | `++a` |
| Decrement | `dec(a)` | `a--` |
| Decrement | `dec(a)` | `--a` |

### Math functions

You need to include the `<cmath>` library to use these.

|                      | Pascal     | C++                          |
| -------------------- | ---------- | ---------------------------- |
| Absolute value       | `abs(a)`   | `abs(a)` (integers)          |
| Absolute value       | `abs(a)`   | `fabs(a)` (floating point)   |
| $a^b$                | N/A[^ref1] | `pow(a, b)`                  |
| Truncate             | `trunc(a)` | `trunc(a)`                   |
| Round to nearest     | `round(a)` | `round(a)`                   |

[^ref1]: Extended Pascal has `a**b`, but you need to include the `Math` library.

For other functions, see:

-   [Common mathematical functions - cppreference.com](https://zh.cppreference.com/w/cpp/numeric/math)
