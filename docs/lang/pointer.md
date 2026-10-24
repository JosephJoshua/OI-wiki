author: tsagaanbar, Enter-tainer, Xeonacid

## Addresses of variables and pointers

In a program, every piece of data is stored at some address. Each time the program actually runs, a variable may be stored at a different place in physical memory. Still, when writing code we can use certain statements to get the address of data in memory.

An address is also data. The variable type used to hold an address has a special name: a "pointer variable", sometimes just called a "pointer".

???+ note "Size of a pointer variable"
    The size of a pointer variable depends on the environment. On a 32-bit machine, an address is a 32-bit binary integer, so a pointer takes 4 bytes. On a 64-bit machine, an address is a 64-bit binary integer, so a pointer takes 8 bytes.

An address is just a number, like a mark on a ruler. To deal with different types of data, "pointer variables" also come in different types. For example, there are `int` pointer variables, whose stored address (that is, the value stored in the pointer variable) is the start of a 32-bit block of memory; and there are `char` pointer variables, whose stored address is the start of an 8-bit block of memory.

In fact, you can also declare pointer variables that point to pointer variables.

Suppose you define a struct:

```cpp
struct ThreeInt {
  int a;
  int b;
  int c;
};
```

Then a pointer variable of type `ThreeInt` corresponds to a block of 3 × 32 = 96 bits.

## Declaring and using pointers

In C/C++, the type of a pointer variable is the type name followed by an asterisk `*`. For example, the type of an `int` pointer variable is `int*`.

We can get the address of a variable with the `&` operator.

To access the memory at the address stored in a pointer variable (also called the memory the pointer **points to**), you **dereference** the pointer variable with the `*` operator.

```cpp
int main() {
  int a = 123;  // a: 123
  int* pa = &a;
  *pa = 321;  // a: 321
}
```

Struct variables work the same way. To access a member of the struct a pointer points to, you can first dereference the pointer and then use the `.` member access operator. However, the simpler "arrow" operator `->` is recommended.

```cpp
struct ThreeInt {
  int a;
  int b;
  int c;
};

int main() {
  ThreeInt x{1, 2, 3}, y{6, 7, 8};
  ThreeInt* px = &x;
  (*px) = y;    // x: {6,7,8}
  (*px).a = 4;  // x: {4,7,8}
  px->b = 5;    // x: {4,5,8}
}
```

## Pointer offsets

You can also add an **integer** to a pointer variable or subtract one from it. For an `int` pointer, each time you add 1 (increment by 1), the address it points to moves by 32 bits (4 bytes); if you add 2, the address moves by 2 × 32 = 64 bits. Likewise, for a `char` pointer, each increment moves the address by 8 bits (1 byte).

### Accessing arrays with pointer offsets

As we said before, an array is a contiguous block of memory. In C/C++, using the array name by itself gives the starting address of the array.

```cpp
int main() {
  int a[3] = {1, 2, 3};
  int* p = a;  // p points to a[0]
  *p = 4;      // a: [4, 2, 3]
  p = p + 1;   // p points to a[1]
  *p = 5;      // a: [4, 5, 3]
  p++;         // p points to a[2]
  *p = 6;      // a: [4, 5, 6]
}
```

When you access array elements through a pointer, you usually use "pointer offsets". In other words, you access an element by adding an offset to a base address (the starting address of the array).

We often use the `[]` operator to access the element at a given offset in an array, such as `a[3]` or `p[4]`. This is the same as doing pointer arithmetic and then dereferencing: `p[4]` and `*(p + 4)` are two equivalent ways of writing it.

## Null pointers

Before C++11, C++, like C, used the `NULL` macro for the null pointer constant. In C++, `NULL` is usually implemented like this:

```cpp
// before C++11
#define NULL 0
```

???+ note "How C defines `NULL`"
    Before C23, C had two definitions of `NULL` that differ only in type: one is an integer constant expression, and the other is a constant expression cast to `void *`. Both have the value 0, and the compiler may choose either one.

Mixing up the null pointer and the integer `0` causes many problems in C++. For example:

```cpp
int f(int x);
int f(int* p);
```

When you call `f(NULL)`, the function actually called has type `int(int)`, not `int(int *)`.

???+ note "Problems `NULL` causes in C"
    Because there are two definitions, `NULL` causes even worse problems in C than in C++. Suppose a function takes variadic arguments, and its author expects a pointer, but the caller passes a `NULL` that is defined as an integer. This is undefined behavior, because when the function uses the variadic argument it has to convert its type, and converting from an integer type to a pointer type is undefined behavior.[^note1]

To solve these problems, C++11 introduced the `nullptr` keyword as the null pointer constant.

C++ specifies that `nullptr` can be implicitly converted to any pointer type, and the result of the conversion is the null pointer value of that type.

The type of `nullptr` is `std::nullptr_t`, called the null pointer type. A possible implementation is:

```cpp
namespace std {
typedef decltype(nullptr) nullptr_t;
}
```

Also, since C++11, the `NULL` macro has been changed to:

```cpp
// since C++11
#define NULL nullptr
```

???+ note "C's improvement to the null pointer constant"
    For similar reasons, C23 also introduced `nullptr` as the null pointer constant, along with `nullptr_t` as its type[^note1].

## Advanced use of pointers

Pointers let programmers work with data anywhere in the running program, without being limited by scope.

### Using pointer parameters

In C/C++, arguments passed to a function (procedure) are all copied into it (except references, which are covered later). By default, a function can only send its result back to the caller through its return value. But if a function wants to modify data outside it, or a struct/class holds a lot of data and should not be copied, you can pass the address of the outside data. Then the function can access and even modify that data.

The `my_swap` function below takes two `int` pointers and uses a temporary variable to swap the values of two `int` variables.

```cpp
void my_swap(int *a, int *b) {
  int t;
  t = *a;
  *a = *b;
  *b = t;
}

int main() {
  int a = 6, b = 10;
  my_swap(&a, &b);
  // after the call, a in main becomes 10 and b becomes 6
}
```

C++ introduced references, which are easier and safer to use than pointers. For details, see [C++: References](./reference.md) and [Differences between C and C++: pointers and references](./cpp-other-langs.md#指针与引用).

### Dynamic allocation

Besides this, programs often need dynamic memory allocation: while running, the program asks the operating system for memory to store data, or gives it back. When the program requests memory through an operating system interface, the operating system returns the address of the requested memory. To use that memory, we store its address in a pointer variable.

In C++, we use the `new` operator to get a block of memory and the `delete` operator to free the memory a pointer points to.

```cpp
int* p = new int(1234);
/* ... */
delete p;
```

The statement above uses the `new` operator to request an `int`-sized block of memory from the operating system, initializes its value to 1234, and declares an `int` pointer `p` that points to that memory.

Similarly, you can use `new` to create new objects:

```cpp
class A {
  int a;

 public:
  A(int a_) : a(a_) {}
};

int main() {
  A* p = new A(1234);
  /* ... */
  delete p;
}
```

As shown above, a "`new` expression" tries to allocate a block of memory of the right size, tries to construct the object in that memory, and returns the address of that memory.

```cpp
struct ThreeInt {
  int a;
  int b;
  int c;
};

int main() {
  ThreeInt* p = new ThreeInt{1, 2, 3};
  /* ... */
  delete p;
}
```

???+ note "List initialization"
    The `{}` syntax can initialize structs that have no constructor. It also lets you initialize variables in a uniform way. See "[list initialization (since C++11)](https://en.cppreference.com/w/cpp/language/list_initialization)".

Note that when memory obtained with `new` is no longer needed, you must free it with `delete`. You must not free the same memory twice or more. Using `delete` on the null pointer `nullptr` is legal, though.

### Creating arrays dynamically

You can also create an array with the `new[]` operator. In that case `new[]` returns the starting address of the array, that is, the address of its first element, and we can store this address in a pointer of the matching type. To free it, use the `delete[]` operator.

```cpp
size_t element_cnt = 5;
int *p = new int[element_cnt];
delete[] p;
```

Array elements are stored contiguously, so `p + 1` points to the element right after `p`.

### Two-dimensional arrays

When storing data in matrix form, you may use a "two-dimensional array". Semantically, a 2D array is an array of arrays. Computer memory, on the other hand, can be seen as one very long 1D array. So when a 2D array is stored in memory, there is the question of whether it is "contiguous".

"Contiguous" means that the end of any row of the 2D array is physically right next to the start of the next row. In other words, the whole 2D array can be seen as one 1D array. Otherwise, the rows are not necessarily next to each other in memory.

For a "contiguous" 2D array, you can visit all its data with a single loop, using one pointer that keeps incrementing. For a non-contiguous 2D array, since the rows are not contiguous, you first need to get the starting address of a row and then access the elements in that row.

???+ note "How 2D arrays are stored"
    Storing data row by row like this is called row-major order. You can also store data column by column. Because of how computer memory access works, accessing contiguous data is usually faster. So you should choose "row-major" or "column-major" storage based on how the data is likely to be used.

### Creating 2D arrays dynamically

In C/C++, we can declare a 2D array with N rows and M columns using a statement like the one below. Its memory is physically contiguous.

???+ note "Describing array dimensions"
    A more general way is to talk about the n-th dimension. For "row-major" storage, the first dimension of the array has length N and the second has length M.

```cpp
int a[N][M];
```

This kind of declaration requires N and M to be constant expressions known at compile time.

In C/C++, the first element of an array has index 0, so `a[r][c]` is the (c + 1)-th element of row r + 1 of the 2D array a. We also say this element has index `(r,c)`.

In practice, however, the size of a (2D) array may not be fixed, so you need dynamic memory allocation.

A common approach is to declare a **1D array** of length N × M and access the element at index `(r, c)` of the 2D array through the index `r * M + c`.

```cpp
int* a = new int[N * M];
```

This guarantees that the 2D array is **contiguous**.

???+ note "Arrays are stored linearly at the physical level"
    In fact, all data in memory can be seen as stored linearly. So by following certain rules, you can store an n-dimensional array in a dynamically allocated 1D array.

You can also allocate and use memory based on the idea of an "array of arrays". An array that stores several arrays is really an array that stores the starting addresses of those arrays, that is, an array of pointer variables.

We need a variable to hold the starting address of this "array of arrays", that is, the address of a pointer. This variable is a "pointer to a pointer", sometimes called a "double pointer", for example:

```cpp
int** a = new int*[5];
```

Next, we allocate memory for each array:

```cpp
for (int i = 0; i < 5; i++) {
  a[i] = new int[5];
}
```

Now the memory has been allocated. To free memory obtained this way, do the reverse: first free each array, then free the array that stores their starting addresses, for example:

```cpp
for (int i = 0; i < 5; i++) {
  delete[] a[i];
}
delete[] a;
```

Note that a 2D array obtained this way is not guaranteed to be contiguous in memory.

There is one more approach, which uses a "pointer to an array".

???+ note "The difference between an array name and the address of its first element"
    We said earlier that in C/C++, using the array name by itself gives a value equal to the address of the array's first element. But the type of the variable the array name denotes is actually the whole array, not a single element.
    
    ```cpp
    int main() { int a[5] = {1, 2, 3, 4, 5}; }
    ```
    
    Conceptually, the type of the identifier `a` in this code is `int[5]`. In practice, the address `a + 1` points to is offset from the address `a` points to by the size of 5 `int` variables.

```cpp
int main() {
  int(*a)[5] = new int[5][5];
  int* p = a[2];
  a[2][1] = 1;
  delete[] a;
}
```

This approach also gives contiguous memory, and `a[n]` directly gives the starting address of row n + 1 of the array. So `a[r][c]` accesses the element at index `(r, c)`.

Since a pointer to an array is a specific data type, every dimension except the first must have a length that is a constant known at compile time. Otherwise, the compiler cannot translate an expression like `a[n]` (where `a` is a pointer to an array).

## Pointers to functions

For an introduction to functions, see the [C++ functions](./func.md) section.

Put simply, to call a function you need to know the types and number of its parameters and its return type. Together these are called its interface type.

You can call a function through a function pointer. Sometimes several functions have the same interface type, and a function pointer lets the program choose which one to call **dynamically** at run time. In other words, you can change how a function behaves without modifying it, just by changing the argument (a function pointer) passed to it.

Suppose we have several binary operations on `int`. Each takes 2 `int` parameters and returns an `int`. Here is an example that uses a function pointer:

```cpp
#include <iostream>

int (*binary_int_op)(int, int);

int foo1(int a, int b) { return a * b + b; }

int foo2(int a, int b) { return (a + b) * b; }

int main() {
  int choice;
  std::cin >> choice;
  if (choice == 1) {
    binary_int_op = foo1;
  } else {
    binary_int_op = foo2;
  }

  int m, n;
  std::cin >> m >> n;
  std::cout << binary_int_op(m, n);
}
```

???+ note "`&`, `*` and function pointers"
    In C, writing `void (*p)() = foo;`, `void (*p)() = &foo;`, `void (*p)() = *foo;`, `void (*p)() = ***foo` and so on all give the same result.
    
    A function (such as `foo`) can be implicitly converted to a pointer to the function, so `void (*p)() = foo;` works.
    
    The `&` operator takes the address of an object, and this also works for functions, so `void (*p)() = &foo;` works too.
    
    Applying the `*` operator to a function pointer gives the function it points to. For something like `**foo`, `*foo` gives the function `foo`, which is then implicitly converted back to a pointer to `foo`. And so on: `**foo` still ends up as a function pointer to `foo`. You can use as many `*` as you like, and the result is the same.
    
    Likewise, when calling, `(*p)()` and `p()` are the same; you can leave out the `*` operator.
    
    Reference: [Why do function pointer definitions work with any number of ampersands '&' or asterisks '\*'? - stackoverflow.com](https://stackoverflow.com/questions/6893285/why-do-function-pointer-definitions-work-with-any-number-of-ampersands-or-as)

You can declare a function pointer type with the `typedef` keyword.

```cpp
typedef int (*p_bi_int_op)(int, int);
```

Then we can use the type `p_bi_int_op` later, meaning a pointer to a function that "takes 2 `int` parameters and returns an `int`".

You can use `std::function` to refer to functions more conveniently. (To be continued)

With function pointers, you can implement "callback functions". (To be continued)

## References and notes

[^note1]: See [Introduce the nullptr constant](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3042.htm)
