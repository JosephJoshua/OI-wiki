author: inclyc

The most common programming language in the OI world is C++. Once you use this language, you are bound to deal with compilers and language standards. As everyone knows, C++ is very messy and evil. This article aims to give practical knowledge about compilers, enough for contest use.

## Introduction to compiler optimization

### What is optimization

Under the [as-if rule](https://en.cppreference.com/w/cpp/language/as_if), optimization means improving a program's running speed or the size of its executable while keeping its meaning unchanged.

<!-- ### Which contests enable optimization? -->

<!-- TODO: contests that enable O2 -->

## Common compiler optimizations

### Constant folding

Constant folding, also called constant propagation: if an expression can be determined to be a constant, that constant can be propagated until the next definition of the variable.

```cpp
int x = 1;
int y = x;  // x = 1, => y = 1
x = 3;
int z = 2 * y;   // z => 2 * y = 2 * 1 = 2
int y2 = x * 2;  // x = 3, => y2 = 6
```

At compile time this code can be turned into:

```cpp
int x = 1;
int y = 1;
x = 3;
int z = 2;
int y2 = 6;
```

Example: <https://godbolt.org/z/oEfY35TTd>

### Dead code elimination

As the name says, code that is never used gets removed.

```cpp
int test() {
  int a = 233;
  int b = a * 2;
  int c = 234;
  return c;
}
```

becomes

```cpp
int test() { return 234; }
```

Note that constant folding is done first here, so the return value is known to be 234. a and b are dead variables, so they are removed.

### Loop rotation

This turns a loop from "for" form into "do-while" form, with an extra condition check in front. This transformation mainly prepares for other transformations.

```cpp
for (int i = 0; i < n; ++i) {
  auto v = *p;
  use(v);
}
```

becomes

```cpp
if (0 < n) {
  do {
    auto v = *p;
    use(v);
    ++i;
  } while (i < n);
}
```

### Loop invariant code motion

Based on alias analysis, code in a loop that is proven to be invariant (it may include memory accesses, i.e. loads/stores, which is why alias analysis is needed) is moved out of the loop body. This leaves less code inside the loop.

```cpp
for (int i = 0; i < n; ++i) {
  auto v = *p;
  use(v);
}
```

Intuitively, this code could be hoisted to:

```cpp
auto v = *p;
for (int i = 0; i < n; ++i) {
  use(v);
}
```

But in fact, if `n <= 0`, the loop is never entered, yet we have executed an extra instruction (which might have side effects!). So the loop is usually rotated into do-while form first, which makes it easy to insert a "loop guard". Then loop invariant code motion is done.

```cpp
if (0 < n) {  // loop guard
  auto v = *p;
  do {
    use(v);
    ++i;
  } while (i < n);
}
```

### Loop unrolling

A loop contains the loop body plus various branches, which the modern CPU has to do some branch prediction on. Unrolling the loop directly trades some code size for running time.

```cpp
for (int i = 0; i < 3; i++) {
  a[i] = i;
}
```

becomes:

```cpp
a[0] = 0;
a[1] = 1;
a[2] = 2;
```

### Loop unswitching

Loop unswitching moves a condition inside a loop to outside the loop, and then puts a copy of the loop in each of the two branches. This makes vectorizing and parallelizing the loop more likely (simple loops are usually easier to vectorize).

```cpp
// clang-format off
void before(int x) {
  for(;/* i in some range */;) {
    /* A */;
    if (/* condition */ x % 2) {
      /* B */;
    }
    /* C */;
  }
}

void after(int x) {
  if (/* condition */ x % 2) {
    for(;/* i in some range */;) {
      /* A */;
      /* B */; // run B directly, no check inside the loop
      /* C */;
    }
  } else {
     for(;/* i in some range */;) {
      /* A */; 
               // don't run B
      /* C */;
    }
  }
}
```

### Code layout optimizations

When a program runs, its execution paths can be split into cold and hot paths. A jump by the CPU is, in most cases, slower than just running instructions in order; compiler writers usually call the latter "fallthrough". Code that runs often is called hot code, and the rest is called cold code. In OI code, things like special handling of boundary conditions inside a loop, or error handling, are cold code.

A basic block is the basic unit of control flow. A procedure is made of several basic blocks, which form a directed graph. When generating the executable, the compiler has to choose a layout for placing the basic blocks, and how to arrange that layout is the focus of this optimization.

In principle, hot code should be placed together and cold code kept apart. This makes better use of the instruction cache, because hot code gets better locality.

```cpp
// clang-format off
int hotpath; // <-- hot!
if (/* boundary condition */ false) {
    // <-- cold!
}
int hotpath_again;  // <-- hot!
```

#### Basic block placement

We use labels to write a kind of "pseudo machine code". This C++ program can be translated in two ways:

???+ note "Layout 1"
    ```cpp
    // clang-format off
    hotblock1:
        Stmts; // <-- hot!
        if (/* boundary condition does not hold */ true)
            goto hotblock2; // happens often! ------+
    coldblock:                           /*   |   */
        Stmt; // <- cold                      |
        Stmt; // <- cold                      |
        Stmt; // <- cold                      |  jumps over many instructions, expensive!
        Stmt; // <- cold                      |
        Stmt; // <- cold                      |
        Stmt; // <- cold                      |
        Stmt; // <- cold                      |
    hotblock2:                          /*    |   */
        Stmts; // <- hot!           <----------+
    ```

The other layout is:

???+ note "Layout 2"
    ```cpp
    // clang-format off
    hotblock1:
        Stmts; // <-- hot!
        if (/* boundary condition */ false)
            goto coldblock; // rarely happens
    hotblock2:                         /*   |  cheap!  */
        Stmts; // <- hot!  <-----------------+
    coldblock:
        Stmt; // <- cold
        Stmt; // <- cold
        Stmt; // <- cold
        Stmt; // <- cold
        Stmt; // <- cold
    ```

In the second layout, the two hot blocks are placed together, so it runs more efficiently.

To tell the compiler whether a branch is likely to be taken, you can use C++20 `[[likely]]` and `[[unlikely]]`: <https://en.cppreference.com/w/cpp/language/attributes/likely>

If the contest does not use C++20 or later, you can use `__builtin_expect` (a GNU extension).

```cpp
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

if (unlikely(/* some boundary condition check */ false)) {
  // cold code
}
```

#### Hot/cold splitting

When a procedure contains both hot and cold paths, and the cold code is long, it is better to make the cold code a function call rather than let it break up the hot path. This also tells us not to be too clever and make every function `inline`. Cold code gets in the way of execution speed much more than a function call does.

???+ note "Bad code layout"
    ```cpp
    // clang-format off
    void foo() {
          // clang-format off
    hotblock1:
        Stmts; // <-- hot!
        if (/* boundary condition does not hold */ true)
            goto hotblock2; // happens often! ------+
    coldblock:                           /*   |   */
        Stmt; // <- cold                      |
        Stmt; // <- cold                      |
        Stmt; // <- cold                      |  jumps over many instructions, expensive!
        Stmt; // <- cold                      |
        Stmt; // <- cold                      |
        Stmt; // <- cold                      |
        Stmt; // <- cold                      |
    hotblock2:                          /*    |   */
        Stmts; // <- hot!           <----------+
    }
    ```

???+ note "Good code layout"
    ```cpp
    // clang-format off
    void foo() {
    hotblock1:
      Stmts;  // <-- hot!
      if (/* boundary condition */ false)
        coldBlock();  // split the cold code out, so the hot path is more cache-friendly
    hotblock2:
      Stmts;  // <- hot!
    }
    
    void coldBlock() {
      Stmt;  // <- cold
      Stmt;  // <- cold
      Stmt;  // <- cold
      Stmt;  // <- cold
      Stmt;  // <- cold
      Stmt;  // <- cold
      Stmt;  // <- cold
    }
    ```

Hot/cold splitting is really the reverse of function inlining. The existence of this optimization shows that inlining a function does not always make a program faster. If the inlined code is cold, it can even make the program slower! Some compilers have options to force inlining, but they are not recommended. Inside the compiler there is a static analysis that computes the probability of each basic block and branch, plus a cost model for function calls, and uses them to decide whether to inline. Deciding on inlining yourself is not necessarily better than the compiler's decision.

In fact, without extra information, compilers usually assume a branch is equally likely to be taken or not, and use that to propagate how hot or cold each control-flow path is. Part of PGO (Profile Guided Optimization) is running several performance tests and experiments to find the real branch probabilities in the actual environment. This information lets the code layout be better.

### Function inlining

A function call usually passes arguments through registers and the stack, and both the caller and the callee have to save some register state. This set of rules is usually called the calling convention. So a function call costs some time. Inlining a function means writing the function body directly into the caller, without making a real function call.

```cpp
int add(int x) { return x + 1; }

int foo() {
  int a = 1;
  a = add(a);
}
```

`add()` can be inlined into `foo()`:

```cpp
int foo() {
  int a = 1;
  a = a + 1;  // <-- the body of add(), with no argument passing
}
```

#### `always_inline`,`__force_inline`

<https://clang.llvm.org/docs/AttributeReference.html#always-inline-force-inline>

Some compilers let you inline function calls manually by putting `__attribute__((always_inline))` before the function. This is not necessarily faster than a function call; in this case the compiler trusts that the programmer has good enough judgment.

### Tail call optimization

When a function call is in the tail position of a function body, it is called a tail call. Some special optimizations can be done for calls of this form. Most architectures have a Frame Pointer (a.k.a. FP) and a Stack Pointer (a.k.a. SP), which maintain the function's call frame. If the call is at the tail of the function, we don't need to keep the outer function's call record; the inner function can simply replace it.

#### Replacing function calls with jump instructions

On most architectures, a function call has to save the current program counter `$pc` and some caller-saved registers so that it can return to where it was. A tail call doesn't need this and is translated directly into a jump instruction, because the tail call never returns to the place where the function was running.

A simple example: <https://godbolt.org/z/e7b1safaW>

```cpp
int test(int a);

int tailCall(int x) { return test(x); }
```

```nasm
tailCall(int):                           ; @tailCall(int)
        jmp     test(int)@PLT                    ; TAILCALL
```

#### Automatic tail-recursion rewriting

If a function's tail call is to itself, the function is tail-recursive. More broadly, indirect recursion (recursion formed by two or more functions together) where all the calls are tail calls also counts as tail recursion. The compiler can optimize tail recursion into a non-recursive form, saving the extra stack space and function call cost. Many contestants love writing non-recursive code; without optimization, this can greatly reduce the constant factor. But with optimization on, the binary generated from recursive code is about as good as hand-written non-recursive code.

```cpp
int fac(int n) {
  if (n < 2) return 1;
  return /* uses */ n * fac(n - 1); /* uses the variable n, so it can't be tail-call optimized directly! */
}
```

Note that this function is not tail-recursive, but it can be rewritten as:

```cpp
int fac(int acc, int n) {
  if (n < 2) return acc;
  return fac(acc * n, n - 1);
}
```

The new code is tail-recursive.

Modern compilers can do this for you automatically. If your code can be rewritten into tail-recursive form, the compiler can recognize it and do the rewrite.

#### Tail recursion elimination -Rpass=tailcallelim

Once a function is tail-recursive, the recursive call can be removed directly: with some static analysis, the function is turned into a non-recursive form. We won't dig into how compiler writers do this. From experience, for most OI code that has both a recursive and a non-recursive version, the recursive one can usually be optimized automatically into the non-recursive one. Here are some concrete examples:

???+ note "[GCD](https://godbolt.org/z/8Wb6WEnzv)"
    ```cpp
    int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
    ```

???+ note "[Fibonacci sequence](https://godbolt.org/z/4enof6Wcb)"
    ```cpp
    // the fib(n - 2) term is expanded
    // fib(n - 1) can't be made non-recursive; the optimized code is still exponential
    int fib(int n) {
      if (n < 2) return 1;
      return fib(n - 1) + fib(n - 2);
    }
    ```

???+ note "[Factorial](https://godbolt.org/z/n64e75xrf)"
    ```cpp
    // expanded into a scalar loop, then auto-vectorized; the generated code uses SIMD
    unsigned fac(unsigned n) {
      if (n < 2) return 1;
      return n * fac(n - 1);
    }
    ```

After optimization, these functions compile to exactly the same assembly as the non-recursive versions; the recursion is eliminated entirely. For OI contestants, this means that with O2 enabled you can safely write recursive versions of algorithms, and they won't differ from non-recursive ones. But if your function itself cannot be rewritten in non-recursive form, the compiler can't help either.

### Strength reduction

A common compiler optimization. The simplest example is turning `x * 2` into `x << 1`; the second form is quite common in OI. The compiler does this kind of optimization automatically: with optimization on, `x * 2` and `x << 1` are exactly equivalent. Strength reduction turns expensive instructions into cheaper ones.

#### Scalar operator transformations

##### Shifts instead of multiplication

```cpp
int a;
a = x * 2;   // bad!
a = x << 1;  // good!
```

Note that signed and unsigned numbers differ noticeably in shifting and in type promotion. The sign bit gets special treatment in shifts, which come in two types: arithmetic and logical. This shows up clearly when writing binary search, segment trees and similar code with lots of division by two: signed integer division cannot be optimized directly into a single right shift.

```cpp
int l, r;
/* codes */
int mid = (l + r) / 2; /* if the compiler can't assume l, r are non-negative, it generates worse code */
                       // can't be optimized to
                       // mid = (l + r) >> 1
                       // counterexample:
                       // mid = -127
                       // mid / 2 = -63
                       // mid >> 1 = -64
```

```cpp
int mid = (l + r);
int sign = mid >> 31; /* logical right shift, gets the sign bit */
mid += sign;
mid >>= 1; /* arithmetic right shift */
```

Possible solutions:

-   Use `unsigned l, r;` — indices should be unsigned anyway
-   Use shifts in the source code

##### Multiplication instead of division

```cpp
int x = a / 3;
```

This can be transformed into `x = a * 0x55555556 >> 32`. For details, see [this Zhihu article](https://zhuanlan.zhihu.com/p/151038723) or the [original paper](https://dl.acm.org/doi/10.1145/773473.178249).

#### Induction variable strength reduction (IndVars)

The compiler automatically recognizes induction variables in a loop and turns related expensive computations into cheap ones

```cpp
int a = 0;
for (int i = 1; i < 10; i++) {
  a = 3 * i;  // bad!
  a = a + 3;  // good!
}
```

Writing `a = 3 * i` directly is very common in OI, and the compiler can figure out automatically that it is equivalent to `a = a + 3`, replacing the multiplication with a cheaper addition. Analyzing how loop variables change from iteration to iteration is called SCEV (Scalar Evolution).

SCEV can also optimize some loops:

```cpp
int test(int n) {
  int ans = 1;
  for (int i = 0; i < n; i++) {
    ans += i * (i + 1);
  }
  return ans;
}
```

This function is optimized into an $O(1)$ closed-form sum; see <https://godbolt.org/z/ET8d89vvK>. Currently only LLVM-based compilers do this; GCC is more conservative.

```nasm
test(int):                               # @test(int)
        test    edi, edi
        jle     .LBB0_1
        lea     eax, [rdi - 1]
        lea     ecx, [rdi - 2]
        imul    rcx, rax
        lea     eax, [rdi - 3]
        imul    rax, rcx
        shr     rax
        imul    eax, eax, 1431655766
        and     ecx, -2
        lea     eax, [rax + 2*rcx]
        lea     eax, [rax + 2*rdi]
        dec     eax
        ret
.LBB0_1:
        mov     eax, 1
        ret
```

### Auto-vectorization

SIMD (single instruction, multiple data) is a great way to get parallelism on a single core. These instructions use the CPU's SIMD registers, which are wider than general-purpose registers, so you can, for example, put 4 integers in at once and compute on all of them. OI contestants don't need to know the details of auto-vectorization. Generally speaking, Clang auto-vectorizes more aggressively than GCC:

```cpp
// https://godbolt.org/z/h1hx5sWoE
void test(int *a, int *b, int n) {
  for (int i = 0; i < n; i++) {
    a[i] += b[i];
  }
}
```

#### `__restrict` type specifier (GNU, MSVC)

The memory regions that two arbitrary pointers point to may overlap. In that case, a runtime check is needed to see whether vector code can be used. The figure below shows an example of overlapping pointers:

![](./images/overlap.png)

`__restrict` is a promise that lets the compiler assume the memory regions pointed to by two pointers never overlap.

```cpp
void test(int* __restrict a, int* __restrict b, int n) {
  for (int i = 0; i < n; i++) {
    a[i] += b[i];
  }
}
```

`__restrict` is not part of the C++ standard, but all major compilers support it. This keyword affects the quality of auto-vectorized code, and you can use it when you badly need constant-factor optimization.

## Common language misuses related to compiler optimization

### inline

With O2 enabled, function inlining is usually done automatically by the compiler. `inline` inside a struct definition is completely redundant. If the contest you are preparing for enables O2, there is no need to declare anything inline. If O2 is not enabled, using `inline` won't make the compiler actually inline either.

In modern C++, the `inline` keyword is treated as having meaning about linkage and exported symbols, not about inlining functions.

### register: a fake register hint

Modern compilers simply ignore your `register` keyword. Your own idea of register allocation is usually not as smart as the compiler running a register allocation algorithm. This keyword was deprecated in C++11 and removed in C++17[^p0001r1].

<https://en.cppreference.com/w/cpp/keyword/register>

## Undefined behavior and compiler optimization

The compiler may assume a C++ program has no [undefined behavior](https://en.cppreference.com/w/cpp/language/ub) (UB). So when compiling a program that does have UB, the compiler may produce unexpected results. At the same time, by assuming there is no UB, the compiler can optimize more aggressively and freely.

Common kinds of UB are:

1.  [Signed overflow](https://users.cs.utah.edu/~regehr/papers/overflow12.pdf);
2.  Using an uninitialized variable;
3.  Out-of-bounds access;
4.  Dereferencing a null pointer;
5.  An infinite loop with no side effects.

For other kinds of UB and more examples, see the further reading.

### Signed overflow

```cpp
int f(int x) { return x * 2 / 2; }
```

The compiler may assume the program never has signed overflow, so this function may be optimized to

```cpp
int f(int x) { return x; }
```

Examples: <https://godbolt.org/z/WKv3W5hvM>, <https://godbolt.org/z/qqE9nxP1j>.

You can turn this assumption off with the [`-fwrapv`](https://gcc.gnu.org/onlinedocs/gcc-13.2.0/gcc/Code-Gen-Options.html#index-fwrapv) option. Examples: <https://godbolt.org/z/5x3K5KGnr>, <https://godbolt.org/z/4r4a4EzMW>.

### Using an uninitialized variable

```cpp
int f(int x) {
  int a;
  if (x)  // either x nonzero or UB
    a = 42;
  return a;
}
```

The compiler may assume the program never uses an uninitialized variable, so `a` must have been initialized, and this function may be optimized to

```cpp
int f(int) { return 42; }
```

Examples: <https://godbolt.org/z/8WYMYYjdG>, <https://godbolt.org/z/qvGd1nvv9>.

### Out-of-bounds access

```cpp
int table[4] = {};

bool exists_in_table(int v) {
  // return true in one of the first 4 iterations or UB due to out-of-bounds
  // access
  for (int i = 0; i <= 4; i++)
    if (table[i] == v) return true;
  return false;
}
```

The compiler may assume the program never accesses out of bounds, so this function must return before any out-of-bounds access happens, and it may be optimized to

```cpp
bool exists_in_table(int) { return true; }
```

Example: <https://godbolt.org/z/xfePeYsE3>.

### Dereferencing a null pointer

```cpp
int f(int* p) {
  int x = *p;
  if (!p)
    return x;  // Either UB above or this branch is never taken
  else
    return 0;
}
```

The compiler may assume the program never dereferences a null pointer, so `!p` is always `false`, and this function may be optimized to

```cpp
int f(int*) { return 0; }
```

Examples: <https://godbolt.org/z/GY1jvsrb5>, <https://godbolt.org/z/4ronPsnxf>.

### Infinite loops with no side effects

???+ note "Checking Fermat's Last Theorem"
    By [Fermat's Last Theorem](https://en.wikipedia.org/wiki/Fermat%27s_Last_Theorem), the Diophantine equation $a^3=b^3+c^3$ has no solutions in positive integers. The program below tries to enumerate the integers in $[1,1000]$ to check whether the equation holds. If it returns `true`, it has found an integer solution in $[1,1000]$, and Fermat's Last Theorem would be false.
    
    ```cpp
    #include <iostream>
    
    bool fermat() {
      const int max_value = 1000;
    
      // Endless loop with no side effects is UB
      for (int a = 1, b = 1, c = 1; true;) {
        if (((a * a * a) == ((b * b * b) + (c * c * c))))
          return true;  // disproved :()
        a++;
        if (a > max_value) {
          a = 1;
          b++;
        }
        if (b > max_value) {
          b = 1;
          c++;
        }
        if (c > max_value) c = 1;
      }
    
      return false;  // not disproved
    }
    
    int main() {
      std::cout << "Fermat's Last Theorem ";
      fermat() ? std::cout << "has been disproved!\n"
               : std::cout << "has not been disproved.\n";
    }
    ```

The compiler may assume the program has no infinite loops without side effects. So it concludes that the for loop in `fermat()` must end at some point and return `true`, and the program may end up printing:

```text
Fermat's Last Theorem has been disproved!
```

Examples: <https://godbolt.org/z/d834MK7bz>, <https://godbolt.org/z/Eov9nsKqf>.

## Sanitizer

A sanity checker. At run time it checks your program for undefined behavior, out-of-bounds array access, null pointers and more.
When debugging locally, it is a good idea to turn on some sanitizers; they can greatly cut your debugging time. These sanitizers were developed by Google, and most of them work in both GCC and Clang. Sanitizers are more mature in LLVM, so contestants are encouraged to use the Clang compiler locally for this kind of debugging.

### Address Sanitizer -fsanitize=address

<https://clang.llvm.org/docs/AddressSanitizer.html>

Both GCC and Clang support this sanitizer. It checks for:

-   Out-of-bounds access
-   Use after free (use-after-free)
-   Use after return (use-after-return)
-   Double free (double-free)
-   Memory leaks (memory-leaks)
-   Use after leaving scope  (use-after-scope)

Turning on these checks makes your program about 2x slower.

### Undefined Behavior Sanitizer -fsanitize=undefined

<https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html>

The Undefined Behavior Sanitizer (a.k.a. UBSan) checks your code for undefined behavior. Both GCC and Clang support it. It automatically checks whether your program has undefined behavior. UBSan's checks include:

-   Shift overflow, such as shifting a 32-bit integer left by 72 bits
-   Signed integer overflow
-   Overflow when converting a floating-point number to an integer

UBSan's checks are optional. For their effect on the program, see the linked page.

## Miscellaneous

### Compiler Explorer

Watch the behavior and assembly output of different compilers here: <https://godbolt.org>

## Further reading

1.  [The LLVM Project Blog: What Every C Programmer Should Know About Undefined Behavior #1/3](https://blog.llvm.org/2011/05/what-every-c-programmer-should-know.html)
2.  [The LLVM Project Blog: What Every C Programmer Should Know About Undefined Behavior #2/3](https://blog.llvm.org/2011/05/what-every-c-programmer-should-know_14.html)
3.  [The LLVM Project Blog: What Every C Programmer Should Know About Undefined Behavior #3/3](https://blog.llvm.org/2011/05/what-every-c-programmer-should-know_21.html)

## References and notes

[^p0001r1]: [Remove Deprecated Use of the register Keyword (open-std.org)](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/p0001r1.html)
