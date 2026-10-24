Bit manipulation means unary and binary operations on the binary representation of integers. They fall into two kinds: **bitwise operations** and **shifts**. Bit manipulation is one of the most basic kinds of operations in a CPU, and it is usually very fast.

## Integers and bit sequences

See also: [integer types](../lang/var.md#整数类型), [complement representations](./numeral-sys/base.md#补数法)

A fixed-length sequence made up only of `0` and `1` is called a bit sequence. The leftmost bit is called the most significant bit, and the rightmost bit is called the least significant bit.

Computers use bit sequences to represent integers within a certain range. There are only $2^N$ bit sequences of length $N$, so they can be put in one-to-one correspondence with only $2^N$ integers. Such correspondences come in two kinds: **signed** and **unsigned**. Signed means the corresponding integers include negative numbers; unsigned means all the corresponding integers are non-negative.

-   For the unsigned correspondence, we simply use the binary representation of the integer as the bit sequence, padding the high positions with `0` if it is too short.

    Under the unsigned correspondence, a bit sequence of length $N$ can represent integers in $[0,2^N-1]$.

-   For the signed correspondence, there are two representation rules: **ones' complement** and **two's complement**.

    Non-negative integers are represented the same way as in the unsigned rule. For a negative integer, take the bit sequence of its negation (its absolute value) and **invert every bit** (turn `0` into `1` and `1` into `0`); the result is the ones' complement. Then convert the ones' complement to an integer using the unsigned correspondence, add one, convert back to a bit sequence using the unsigned correspondence, and discard any bits beyond the original length; the resulting sequence is the two's complement.

    Under ones' complement, a bit sequence of length $N$ can represent integers in $[-2^{N-1}+1,2^{N-1}-1]$.

    Under two's complement, a bit sequence of length $N$ can represent integers in $[-2^{N-1},2^{N-1}-1]$.

Take $3$-bit sequences as an example:

| Bit sequence   | Unsigned integer | Signed integer (ones' complement) | Signed integer (two's complement) |
| ----- | ----- | --------- | --------- |
| `000` | $0$   | $0$       | $0$       |
| `001` | $1$   | $1$       | $1$       |
| `010` | $2$   | $2$       | $2$       |
| `011` | $3$   | $3$       | $3$       |
| `100` | $4$   | $-3$      | $-4$      |
| `101` | $5$   | $-2$      | $-3$      |
| `110` | $6$   | $-1$      | $-2$      |
| `111` | $7$   | $-0$      | $-1$      |

The biggest problem with ones' complement is that it has $-0$, a "negative number" that does not really exist, so in general we only use two's complement. When representing signed integers, the sign is determined only by the most significant bit, so this bit is called the **sign bit**.

Converting a bit sequence back to an integer is also easy: non-negative numbers need nothing special; for ones' complement, inverting the bits gives the negation; for two's complement, inverting the bits and adding one gives the negation.

## Bitwise operations

A bitwise operation applies some [Boolean function](./boolean-algebra.md#布尔函数) to bit sequences bit by bit. Formally, for a Boolean function $f:\mathbf{B}^k\to \mathbf{B}$, a bitwise operation is a function of the form

$$
\begin{aligned}
    F:\left(\mathbf{B}^m\right)^k&\to \mathbf{B}^m\\
    ((p_{1,1},\dots,p_{m,1}),\dots,(p_{1,k},\dots,p_{m,k}))&\mapsto (f(p_{1,1},\dots,p_{1,k}),\dots,f(p_{m,1},\dots,p_{m,k}))
\end{aligned}
$$

where $m$ is the length of the bit sequences. As with Boolean functions, we usually only study unary and binary bitwise operations. Unless stated otherwise, bitwise operations below are unary or binary.

In general, we treat **bitwise NOT**, **bitwise AND**, **bitwise OR** and **bitwise XOR** as the basic bitwise operations; all other bitwise operations can be built by combining them.

| Bitwise operation  | Math notation                        | Corresponding Boolean function  | C++ operator         | Explanation                      |
| ---- | ----------------------------- | -------- | --------------- | ----------------------- |
| Bitwise NOT | $\operatorname{NOT}$          | $\lnot$  | `~`             | $0$ becomes $1$, $1$ becomes $0$   |
| Bitwise AND  | $\operatorname{AND}$          | $\land$  | `&`             | $1$ only when both corresponding bits are $1$   |
| Bitwise OR  | $\operatorname{OR}$           | $\lor$   | <code>\|</code> | $1$ when at least one of the two corresponding bits is $1$ |
| Bitwise XOR | $\oplus$, $\operatorname{XOR}$ | $\oplus$ | `^`             | $1$ only when the two corresponding bits differ        |

???+ warning "Warning"
    Do not confuse bitwise operations with Boolean functions.

For example:

-   $\operatorname{NOT} 01010111=10101000$,
-   $01010011 \operatorname{AND} 00110010=00010010$,
-   $01010011 \operatorname{OR}  00110010=01110011$,
-   $01010011 \operatorname{XOR} 00110010=01100001$.

In these four bitwise operations each bit is computed independently, so they directly inherit the properties of the corresponding Boolean functions.

For convenience, when the length of the bit sequences is known, we can also apply bitwise operations directly to integers, for example:

$$
\begin{aligned}
    \operatorname{NOT} 5&=-6,\\
    \operatorname{NOT} (-5)&=4,\\
    5 \operatorname{AND} 6 &=4,\\
    5 \operatorname{OR} 6 &=7,\\
    5 \operatorname{XOR} 6 &=3.
\end{aligned}
$$

Assuming $x,y\geq 0$, we can also write bitwise operations as sums:

$$
\begin{aligned}
    \operatorname{NOT} x&=\sum_{n=0}^{\lfloor\log_{2}x\rfloor}2^n\left(\left(\left\lfloor\frac{x}{2^n}\right\rfloor\bmod 2+1\right)\bmod 2\right)\\
    &=\sum_{n=0}^{\lfloor\log_{2}x\rfloor}\left(2^{\left\lfloor\log_{2}x\right\rfloor +1}-1-x\right)\\
    x\operatorname{AND} y&=\sum_{n=0}^{\lfloor\log_{2}\max\{x,y\}\rfloor}2^n\left(\left\lfloor\frac{x}{2^n}\right\rfloor\bmod 2\right)\left(\left\lfloor{\frac{y}{2^n}}\right\rfloor\bmod 2\right)\\
    x\operatorname{OR} y&=\sum_{n=0}^{\lfloor\log_{2}\max\{x,y\}\rfloor}2^n\left(\left(\left\lfloor\frac{x}{2^n}\right\rfloor\bmod 2\right)+\left(\left\lfloor{\frac{y}{2^n}}\right\rfloor\bmod 2\right)-\left(\left\lfloor\frac{x}{2^n}\right\rfloor\bmod 2\right)\left(\left\lfloor{\frac{y}{2^n}}\right\rfloor\bmod 2\right)\right)\\
    x\operatorname{XOR} y&=\sum_{n=0}^{\lfloor\log_{2}\max\{x,y\}\rfloor}2^n\left(\left(\left(\left\lfloor\frac{x}{2^n}\right\rfloor\bmod 2\right)+\left(\left\lfloor{\frac{y}{2^n}}\right\rfloor\bmod 2\right)\right)\bmod 2\right)\\
    &=\sum_{n=0}^{\lfloor\log_{2}\max\{x,y\}\rfloor}2^n\left(\left(\left\lfloor\frac{x}{2^n}\right\rfloor +\left\lfloor\frac{y}{2^n}\right\rfloor\right)\bmod 2\right)
\end{aligned}
$$

When there is no ambiguity, we drop the word "bitwise" below.

## Shifts

See also: [C++ bitwise operators](../lang/op.md#位操作符).

A shift is a binary operation that "moves a bit sequence left or right bit by bit". The first argument is a bit sequence, and the second is usually a non-negative integer. Moving left is called a **left shift**, and moving right is called a **right shift**. Depending on how the vacated positions are filled, shifts are divided into **arithmetic shifts**, **logical shifts** and **circular shifts (rotations)**. Specifically,

-   a logical shift fills the vacated positions with 0,
-   an arithmetic right shift fills them with the sign bit, and an arithmetic left shift is the same as a logical left shift,
-   a circular shift fills them with the bits that were shifted out.

For example, for the $8$-bit sequence `10 01 01 10`:

| Operation         | Result            |
| ---------- | ------------- |
| Arithmetic left shift by $2$ | `01 01 10 00` |
| Arithmetic right shift by $2$ | `11 10 01 01` |
| Logical left shift by $2$ | `01 01 10 00` |
| Logical right shift by $2$ | `00 10 01 01` |
| Circular left shift by $2$ | `01 01 10 10` |
| Circular right shift by $2$ | `10 10 01 01` |

In C++, `a << b` is a left shift and `a >> b` is a right shift. For which shift rules are used, see [C++ bitwise operators](../lang/op.md#位操作符).

Circular shifts can be implemented with the following code:

???+ note "Implementation"
    ```cpp
    --8<-- "docs/math/code/bit/bit_1.cpp:core"
    ```

## Applications of bit manipulation

Bit manipulation is generally used for three things:

1.  Doing certain computations efficiently, replacing slower methods. See [compiler optimizations #strength reduction](../lang/optimizations.md#强度削减-strength-reduction).
2.  [Representing sets](./binary-set.md) (often used in [bitmask DP](../dp/state.md)).
3.  The problem itself asks for bit operations.

Note that replacing other operations with bit manipulation often does not bring much speedup and can make the code more complicated, so think before using it.

### Applications involving powers of 2

Since bit manipulation works on the binary representation, there are many applications involving integer powers of 2.

Multiplying (dividing) a number by a non-negative integer power of 2:

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:mul"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:mul"
    ```

??? warning "Warning"
    Ordinary division rounds toward $0$, while a right shift here rounds down (note the difference). The two give the same result when the number is at least $0$, but differ when it is negative. For example, `-1 / 2` is $0$, while `-1 >> 1` is $-1$.

### Absolute value

On some machines, this is faster than `n > 0 ? n : -n`.

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:abs"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:abs"
    ```

### Maximum/minimum of two numbers

On some machines, this is faster than `a > b ? a : b`.

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:minmax"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:minmax"
    ```

### Checking whether two non-zero numbers have the same sign

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:sgn"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:sgn"
    ```

### Swapping two numbers

???+ note "This method has limitations"
    This method can only swap two integers, so its use is limited.
    
    For swapping in general, just call the `std::swap` function from the `algorithm` library.

```cpp
--8<-- "docs/math/code/bit/bit_2.cpp:swap"
```

### Working with the binary digits of a number

Get one binary digit of a number:

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:get_bit"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:get_bit"
    ```

Set one binary digit of a number to $0$:

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:unset_bit"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:unset_bit"
    ```

Set one binary digit of a number to $1$:

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:set_bit"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:set_bit"
    ```

Flip one binary digit of a number:

=== "C++"
    ```cpp
    --8<-- "docs/math/code/bit/bit_2.cpp:flap_bit"
    ```

=== "Python"
    ```python
    --8<-- "docs/math/code/bit/bit_2.py:flap_bit"
    ```

These operations treat a $32$-bit integer variable as a Boolean array of length $32$.

## Hamming weight

The Hamming weight of a string of symbols is the number of symbols that differ from the zero-symbol (defined on the alphabet being used). For a binary number, its Hamming weight is the number of $1$s in it (that is, its `popcount`).

We can compute the Hamming weight of a number with a loop: repeatedly remove the last binary digit of the number (that is, shift right by $1$), keep an answer variable, and update it during the division depending on whether the lowest bit is $1$.

The code is as follows:

```cpp
--8<-- "docs/math/code/bit/bit_2.cpp:popcnt1"
```

We can also compute the Hamming weight with the `lowbit` operation: keep subtracting the `lowbit`[^note1] of the number from it until it becomes $0$.

The code is as follows:

```cpp
--8<-- "docs/math/code/bit/bit_2.cpp:popcnt2"
```

### Constructing a permutation in increasing order of Hamming weight

In [bitmask DP](../dp/state.md), enumerating states in increasing order of popcount can sometimes avoid enumerating the same state twice. This is one major use of a permutation ordered by increasing Hamming weight.

Below we look at how to construct a permutation ordered by increasing Hamming weight in $O(n)$ time.

We know that the smallest integer with Hamming weight $n$ is $2^n-1$. If we can find, in constant time, the next integer with the same Hamming weight, then by enumerating the Hamming weight and repeatedly finding the next number starting from $2^n-1$, we can construct the required permutation of $0\sim n$ in $O(n)$ time.

To find the next number after $x$ with the same Hamming weight, use the following idea, taking $(10110)_2$ as an example:

-   Move the rightmost $1$ of $(10110)_2$ one place to the left. If it cannot move, move the $1$ to its left instead, and so on. This gives $(11010)_2$.

-   In $(11010)_2$, take all the $1$s from the original position of the last moved $1$ down to the lowest bit, and move them all to the far right. Here the last moved $1$ was originally at the third position, so the last three bits $010$ become $001$, giving $(11001)_2$.

This process can be sped up with bit manipulation:

```cpp
--8<-- "docs/math/code/bit/bit_3.cpp:hamming1"
```

-   In the first step, we add the `lowbit` of $x$ to $x$. In binary, this replaces the rightmost run of consecutive $1$s in $x$ with a single $1$ just to its left. For the binary number $(10110)_2$ above, adding its `lowbit` gives $(11000)_2$. This is actually the first half of our answer.
-   Next we need to fill in the $1$s at the end of the answer. The `lowbit` of $t$ is where the leftmost $1$ of the rightmost run of $1$s in $x$ moved to, and the `lowbit` of $x$ is the rightmost position of that run. Again with $(10110)_2$: $t = (11000)_2$, $\operatorname{lowbit}(t) = (01000)_2$, $\operatorname{lowbit}(x)=(00010)_2$.
-   The division that follows is the hardest part of this trick to understand, but it is also the key part. Suppose that in the rightmost run of $1$s of the **original number**, the highest $1$ is at bit $r$ (counting from $0$) and the lowest $1$ is at bit $l$. Then the `lowbit` of $t$ is `1 << (r+1)` and the `lowbit` of $x$ is `1 << l`, so `(((t&-t)/(x&-x))>>1)` gives `(1<<(r+1))/(1<<l)/2 = (1<<r)/(1<<l) = 1<<(r-l)`. In binary, this is a $1$ followed by $r-l$ zeros, and the number of zeros is exactly the length of the run of $1$s minus $1$. With our example number, $\frac{\operatorname{lowbit(t)/2}}{\operatorname{lowbit(x)}} = \frac{(00100)_2}{(00010)_2} = (00010)_2$. Subtracting $1$ from this gives the low bits we need to fill in, and ORing it with the earlier number gives the answer.

So the full code that enumerates the permutation of $0\sim n$ in increasing order of Hamming weight is:

```cpp
--8<-- "docs/math/code/bit/bit_3.cpp:hamming2_begin"
--8<-- "docs/math/code/bit/bit_3.cpp:hamming2_end"
```

Note the special case for $0$: $0$ has no next number with the same Hamming weight.

## Related classes and functions in C++

### GCC built-in functions

GCC also has some built-in functions for bit manipulation:

-   `int __builtin_ffs(int x)`: returns the position of the last $1$ at the end of the binary form of $x$, numbered from $1$ (the lowest bit is position $1$). Returns $0$ when $x$ is $0$.
-   `int __builtin_clz(unsigned int x)`: returns the number of leading $0$s in the binary form of $x$. The result is undefined when $x$ is $0$.
-   `int __builtin_ctz(unsigned int x)`: returns the number of trailing $0$s in the binary form of $x$. The result is undefined when $x$ is $0$.
-   `int __builtin_clrsb(int x)`: if the sign bit of $x$ is $0$, returns the number of leading $0$s in the binary form of $x$ minus one; otherwise returns the number of leading $1$s minus one.
-   `int __builtin_popcount(unsigned int x)`: returns the number of $1$s in the binary form of $x$.
-   `int __builtin_parity(unsigned int x)`: returns the parity of the number of $1$s in the binary form of $x$.

All of these functions can take the suffix `l` or `ll` (as in `__builtin_popcountll`) to change the argument type to (`unsigned`)`long` or (`unsigned`)`long long` (the return type is still `int`).
For example, we sometimes want the base-2 logarithm of a number. Ignoring the special case `0`, this is the number of binary digits of the number `-1`. The number of binary digits of an `N`-bit integer `n` is `N - __builtin_clz(n)`, so `N - 1 - __builtin_clz(n)` gives the base-2 logarithm of `n`.

Since these are built-in functions that the compiler optimizes heavily, they run very fast (some take only a single instruction).

### More bits

If the bit sequence you need is very long, you can use [`std::bitset`](../lang/csl/bitset.md).

## Recommended problems

-   [Luogu P1225 Black and White Pieces Game](https://www.luogu.com.cn/problem/P1225)

## References and notes

1.  [Bit Twiddling Hacks](https://graphics.stanford.edu/~seander/bithacks.html)
2.  [Bit Operation Builtins (Using the GNU Compiler Collection (GCC))](https://gcc.gnu.org/onlinedocs/gcc/Bit-Operation-Builtins.html)
3.  [Bitwise operation - Wikipedia](https://en.wikipedia.org/wiki/Bitwise_operation)

[^note1]: The first $1$ from the low end of the binary representation of a number, together with the zeros after it. For example, the `lowbit` of $(1010)_2$ is $(0010)_2$. See [Fenwick tree](../ds/fenwick.md) for details.
