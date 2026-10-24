author: Ir1d, tsagaanbar, yang-lile

## Declaring a function

In programming, a function is usually a group of statements. We can also call it a "**subroutine**". When some process is repeated in a program, we can pull it out into a function. A function can take some values, called its parameters. A function can also return a value, called its return value.

To declare a function, we need its return type, its name and its parameter list.

```cpp
// return type: int
// function name: some_function
// parameter list: int, int
int some_function(int, int);
```

Above, we declared a function named `some_function`. It takes two parameters of type `int`, and its return type is also `int`. You can think of it as a function that does something with the two integers passed in and returns a result of the same type.

## Implementing a function: writing the definition

A declaration alone is not enough. It only tells the caller the function's **interface** (what data it takes and what data it returns), but it has no actual implementation inside. That implementation is the function's **definition**. We can **implement** the function by writing code **somewhere after the declaration** (it can also be in another file, but then the separately compiled files must all be given together at link time).

If the function has a return value, a `return` statement sends the value back to the caller. As soon as the function reaches a `return` statement, it ends right away and does not run any further statements.

```cpp
int some_function(int, int);  // declaration

/* some other code here... */

int some_function(int x, int y) {  // definition
  int result = 2 * x + y;
  return result;
  result = 3;  // this statement is never executed
}
```

In the definition, we gave names to the variables in the parameter list. That way we can use those variables inside the definition.

Within the same file, we can also **combine the declaration and the definition**. In other words, we define the function at the same time as we declare it.

```cpp
int some_function(int x, int y) { return 2 * x + y; }
```

If a function does not need to return a value, mark its return type as `void`. If a function does not need parameters, leave the parameter list empty. A function with no return value also stops when it reaches a `return;` statement.

```cpp
void say_hello() {
  cout << "hello!\n";
  cout << "hello!\n";
  cout << "hello!\n";
  return;
  cout << "hello!\n";  // this statement is never executed
}
```

## Calling a function

Like variables, functions must be declared before they can be used. Using a function is called a "call". We can call other functions from inside any function, including the function itself. A function calling itself is called **recursion**.

In most languages, you call a function by writing **its name followed by a pair of parentheses** `()`, as in `foo()`. If the function needs arguments, write them in order inside the parentheses, separated by commas, as in `foo(1, 2)`. A function call is also an expression, and **the function's return value** is **the value of the expression**.

The parameters written in the declaration can be thought of as variables that exist **inside the current call** of the function. Their values are initialized from the values passed in by the caller. Look at this example:

```cpp
void foo(int, int);

/* ... */

void foo(int x, int y) {
  x = x * 2;
  y = y + 3;
}

/* ... */

a = 1;
b = 1;
// before the call: a = 1, b = 1
foo(a, b);  // call foo
            // after the call: a = 1, b = 1
```

In this example, `foo(a, b)` is a call to `foo`. During the call, the variables `x` and `y` in `foo` are initialized from the values of `a` and `b` at the call site. So changing `x` and `y` inside `foo` **does not change the variables at the call site**.

If we need a function (subroutine) to change a variable's value, we must "pass by reference".

```cpp
void foo(int& x, int& y) {
  x = x * 2;
  y = y + 3;
}

/* ... */

a = 1;
b = 1;
// before the call: a = 1, b = 1
foo(a, b);  // call foo
            // after the call: a = 2, b = 4
```

In this code, an "`&`" (ampersand) is added after "`int`" in the parameter list. It means a **reference** to an `int`. When `foo` is called, the variables `a` and `b` at the call site initialize the two `int` references `x` and `y` in `foo`. You can think of `x` and `y` in `foo` as "aliases" for `a` and `b` at the call site: anything done to `x` and `y` in `foo` is done to `a` and `b` at the call site.

## The `main` function

In particular, every C/C++ program must have a function named `main`. Every program starts running from `main`.

> The `main` function can also take parameters. Through them, we can get instructions passed to the program from outside (the "command-line arguments") and respond differently to them.

Here is some code that calls a function (subroutine):

```cpp
// hello_subroutine.cpp

#include <iostream>

void say_hello() {
  std::cout << "hello!\n";
  std::cout << "hello!\n";
  std::cout << "hello!\n";
}

int main() {
  say_hello();
  say_hello();
}
```
