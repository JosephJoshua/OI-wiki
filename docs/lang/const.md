C++ has a complete system for defining read-only values. Every variable marked with `const` is read-only. The compiler checks for conflicts at compile time to prevent read-only values from being modified, and it may also perform some optimizations.

In general, you should mark variables and parameters with `const` whenever you can, to make your code more robust.

## The `const` type qualifier

### Constants

A variable marked with const cannot change its value after initialization.

```cpp
const int a = 0;  // a has type const int

// a = 1; // A constant cannot be modified
```

### References to const and pointers to const

Both references to const and pointers to const prevent modifying the value they refer to.

```cpp
int a = 0;
const int b = 0;

int *p1 = &a;
*p1 = 1;
const int *p2 = &a;
// *p2 = 2; // Cannot modify a variable through a pointer to const
// int *p3 = &b; // Cannot point an int* at a const int variable
const int *p4 = &b;

int &r1 = a;
r1 = 1;
const int &r2 = a;
// r2 = 2; // Cannot modify a variable through a reference to const
// int &p3 = b; // Cannot bind an int& to a const int variable
const int &r4 = b;
```

You also need to tell apart a pointer to const (`const t*`) and a const pointer (`t* const`). For example, in the declarations below:

```cpp
int* const p1;  // Const pointer: after initialization the address it points to cannot change, but the pointed-to value can
const int* p2;  // Pointer to const: the dereferenced value cannot change, but it can point to other int variables
const int* const p3;  // Const pointer to const: neither the value nor the address it points to can change

// Using aliases makes this more readable
using const_int = const int;
using ptr_to_const_int = const_int*;
using const_ptr_to_const_int = const ptr_to_const_int;
```

Using `const` to qualify parameter types in function parameters prevents variables from being modified by mistake, and also makes the code more readable.

```cpp
void sum(const std::vector<int> &data, int &total) {
  for (auto iter = data.begin(); iter != data.end(); ++iter)
    total += *iter;  // iter is an iterator; its dereferenced type is const int
}
```

## `const` member functions

A member function marked `const` in a class can be used to prevent changes to members.

```cpp
#include <iostream>

struct ConstMember {
  int s = 0;

  void func() { std::cout << "General Function" << std::endl; }

  void constFunc1() const { std::cout << "Const Function 1" << std::endl; }

  void constFunc2(int ss) const {
    // func(); // A const member function cannot call a non-const member function
    constFunc1();

    // s = ss; // A const member function cannot modify member variables
  }
};

int main() {
  int b = 1;
  ConstMember c{};
  const ConstMember d = c;
  // d.func(); // A constant cannot call a non-const member function
  d.constFunc2(b);
  return 0;
}
```

## Constant expressions: `constexpr` (C++11)

A constant expression is an expression whose result can be computed at compile time. `constexpr` requires that the compiler can compute the value of a function or variable at compile time.

Computing at compile time allows better optimization, such as hard-coding the result into the assembly and removing the cost of computing it at runtime. Unlike the optimizations `const` may bring, when a variable marked `constexpr` meets the conditions of a constant expression, the compiler is required to compute the result at compile time rather than at runtime.

???+ note "A more intuitive way to think about it: `const` means \"read-only\" and `constexpr` means \"immutable\""
    ```cpp
    constexpr int a = 10;  // Define a constant directly
    
    constexpr int FivePlus(int x) { return 5 + x; }
    
    void test(const int x) {
      std::array<int, x> c1;            // Error: x is not known at compile time
      std::array<int, FivePlus(6)> c2;  // OK: FivePlus is known at compile time
    }
    ```

The following example shows the difference between `const` and `constexpr` well. The code computes the Fibonacci sequence recursively and prints it with a stream.

???+ note "Implementation"
    ```cpp
    #include <iostream>
    
    using namespace std;
    
    constexpr unsigned fib0(unsigned n) {
      return n <= 1 ? 1 : (fib0(n - 1) + fib0(n - 2));
    }
    
    unsigned fib1(unsigned n) { return n <= 1 ? 1 : (fib1(n - 1) + fib1(n - 2)); }
    
    int main() {
      constexpr auto v0 = fib0(9);
      const auto v1 = fib1(9);
    
      cout << v0;
      cout << ' ';
      cout << v1;
    }
    ```

???+ note "Possible assembly after compiling (using Compiler Explorer, Clang 19)"
    ```nasm
    fib1(unsigned int):
            push    r14
            push    rbx
            push    rax
            mov     ebx, 1
            cmp     edi, 2
            jb      .LBB0_4
            mov     r14d, edi
            xor     ebx, ebx
    .LBB0_2:
            lea     edi, [r14 - 1]
            call    fib1(unsigned int)
            add     r14d, -2
            add     ebx, eax
            cmp     r14d, 1
            ja      .LBB0_2
            inc     ebx
    .LBB0_4:
            mov     eax, ebx
            add     rsp, 8
            pop     rbx
            pop     r14
            ret
    
    main:
            push    r14
            push    rbx
            push    rax
            mov     edi, 9
            call    fib1(unsigned int) # Initializing `v1` makes a function call
            mov     ebx, eax
            mov     r14, qword ptr [rip + std::__1::cout@GOTPCREL]
            mov     rdi, r14
            mov     esi, 55 # `v0` is replaced by the final result
            call    std::__1::basic_ostream<char, std::__1::char_traits<char>>::operator<<(unsigned int)@PLT
            mov     byte ptr [rsp + 7], 32
            lea     rsi, [rsp + 7]
            mov     edx, 1
            mov     rdi, r14
            call    std::__1::basic_ostream<char, std::__1::char_traits<char>>& std::__1::__put_character_sequence[abi:ne200000]<char, std::__1::char_traits<char>>(std::__1::basic_ostream<char, std::__1::char_traits<char>>&, char const*, unsigned long)
            mov     rdi, r14
            mov     esi, ebx # Reads the variable's value
            call    std::__1::basic_ostream<char, std::__1::char_traits<char>>::operator<<(unsigned int)@PLT
            xor     eax, eax
            add     rsp, 8
            pop     rbx
            pop     r14
            ret
    ```

The `constexpr` function `fib0` is called in only one place, with a constant argument, so the whole function runs only at compile time. Since the function never runs at runtime, the compiler decides it does not need to generate assembly for it.

Notice also that in the assembly there is no initialization code for `v0`. In the code that calls `cout` to print `v0`, `v0` has already been replaced by the final result. This shows that the value was computed at compile time and the runtime computation was optimized away.
The initialization of `v1`, on the other hand, is still an ordinary recursive call to `fib1`.

So `constexpr` can replace constants defined with macros and avoid the [risks of macros](./basic.md#define-命令).

In algorithm problems you can use `constexpr` to store variables for small data sizes, removing the corresponding runtime computation cost. This is especially common with the "[precomputed table](../contest/dictionary.md)" trick, where answers are stored in arrays or other containers marked `constexpr`.

???+ note "Too much compile-time computation causes a compile error"
    Compilers limit how much computation can be done at compile time. If there is too much, the code will fail to compile, and you should consider using `const` instead.
    
    ```cpp
    #include <iostream>
    
    using namespace std;
    
    constexpr unsigned long long fib(unsigned long long i) {
      return i <= 2 ? i : fib(i - 2) + fib(i - 1);
    }
    
    int main() {
      // constexpr auto v = fib(32); evaluation exceeded maximum depth
      const auto v = fib(32);
      cout << v;
      return 0;
    }
    ```

???+ note "The compile error Clang gives when using constexpr"
    ```text
    <source>:10:20: error: constexpr variable 'v' must be initialized by a constant expression
        10 |     constexpr auto v = fib(32);
        |                    ^   ~~~~~~~~~~~~
    <source>:6:25: note: constexpr evaluation exceeded maximum depth of 512 calls
        6 |     return i <= 2 ? i : fib(i - 2) + fib(i - 1);
        |                         ^
    <source>:6:25: note: in call to 'fib(32)'
        6 |     return i <= 2 ? i : fib(i - 2) + fib(i - 1);
        |                         ^~~~~~~~~~
    <source>:6:25: note: in call to ...
    ```

## References

-   [C++ keywords: const](https://zh.cppreference.com/w/cpp/keyword/const)
-   [C++ keywords: constexpr](https://zh.cppreference.com/w/cpp/keyword/constexpr)
