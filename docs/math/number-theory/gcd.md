## Definition

The greatest common divisor is usually abbreviated as gcd.

A common divisor of a set of integers is a number that divides every number in the set. $\pm 1$ is a common divisor of any set of integers.

The greatest common divisor of a set of integers is the largest of all its common divisors.

For integers $a,b$ that are not both $0$, we write their greatest common divisor as $\gcd(a,b)$. When there is no ambiguity, we can simply write $(a,b)$.

For integers $a_1,\dots,a_n$ that are not all $0$, we write their greatest common divisor as $\gcd(a_1,\dots,a_n)$. When there is no ambiguity, we can simply write $(a_1,\dots,a_n)$.

For properties of the greatest common divisor and the least common multiple, see [Number Theory Basics](./basic.md#greatest-common-divisor-and-least-common-multiple).

So how do we compute the greatest common divisor? Let's first look at the case of two numbers.

### Euclidean algorithm

#### How it works

Given two numbers $a$ and $b$, how do we find their greatest common divisor?

Without loss of generality, assume $a > b$.

Notice that if $b$ is a divisor of $a$, then $b$ is the greatest common divisor of the two.
Now consider the case where $b$ does not divide $a$, that is, $a = b \times q + r$ with $r < b$.

We can prove that $\gcd(a,b)=\gcd(b,a \bmod b)$, as follows:

???+ note "Proof"
    Let $a=bk+c$; clearly $c=a \bmod b$. Let $d \mid a,~d \mid b$. Then $c=a-bk, \frac{c}{d}=\frac{a}{d}-\frac{b}{d}k$.
    
    From the right-hand side, $\frac{c}{d}$ is an integer, i.e., $d \mid c$. So every common divisor of $a,b$ is also a common divisor of $b,a \bmod b$.
    
    We also need to prove the converse:
    
    Let $d \mid b,~d\mid (a \bmod b)$. As before, we get $\frac{a\bmod b}{d}=\frac{a}{d}-\frac{b}{d}k,~\frac{a\bmod b}{d}+\frac{b}{d}k=\frac{a}{d}$.
    
    The left-hand side is clearly an integer, so $\frac{a}{d}$ is also an integer, i.e., $d \mid a$. So every common divisor of $b,a\bmod b$ is also a common divisor of $a,b$.
    
    Since the two pairs have exactly the same common divisors, their greatest common divisors are also the same.
    
    Therefore $\gcd(a,b)=\gcd(b,a\bmod b)$.

Now that we have $\gcd(a, b) = \gcd(b, r)$, and the two numbers never get larger, we get a recursive way to compute the greatest common divisor of two numbers.

#### Implementation

=== "C++"
    ```cpp
    // Version 1
    int gcd(int a, int b) {
      if (b == 0) return a;
      return gcd(b, a % b);
    }
    
    // Version 2
    int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
    ```

=== "Java"
    ```java
    // Version 1
    public int gcd(int a, int b) {
        if (b == 0) return a;
        return gcd(b, a % b);
    }
    
    // Version 2
    public int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
    ```

=== "Python"
    ```python
    def gcd(a, b):
        if b == 0:
            return a
        return gcd(b, a % b)
    ```

We recurse until `b == 0` (i.e., `a % b == 0` in the previous step), and then return the value.

Based on the recursive method above, we can also write an iterative version:

=== "C++"
    ```cpp
    int gcd(int a, int b) {
      while (b != 0) {
        int tmp = a;
        a = b;
        b = tmp % b;
      }
      return a;
    }
    ```

=== "Java"
    ```java
    public int gcd(int a, int b) {
        while(b != 0) {
            int tmp = a;
            a = b;
            b = tmp % b;
        }
        return a;
    }
    ```

=== "Python"
    ```python
    def gcd(a, b):
        while b != 0:
            a, b = b, a % b
        return a
    ```

All of the algorithms above are called the Euclidean algorithm.

Also, in C++17, we can use [`std::gcd`](https://en.cppreference.com/w/cpp/numeric/gcd) and [`std::lcm`](https://en.cppreference.com/w/cpp/numeric/lcm) from the [`<numeric>`](https://en.cppreference.com/w/cpp/header/numeric) header to compute the greatest common divisor and the least common multiple.

???+ warning "Note"
    With some compilers, in C++14 you can use the function `std::__gcd(a,b)` to compute the greatest common divisor, but it is only a private helper function for `std::rotate`.[^1] Using it may lead to unexpected problems, so it is generally not recommended.

If two numbers $a$ and $b$ satisfy $\gcd(a, b) = 1$, we say that $a$ and $b$ are coprime.

#### Properties

How fast is the Euclidean algorithm? Below we prove that when the input is two $n$-bit binary integers, the time complexity of the Euclidean algorithm is $O(n)$. (In other words, assuming $a, b$ are of the same order of magnitude, the time complexity is $O(\log\max(a, b))$.)

???+ note "Proof"
    When we compute $\gcd(a,b)$, there are two cases:
    
    -   $a < b$. In this case $\gcd(a,b)=\gcd(b,a)$;
    -   $a \geq b$. In this case $\gcd(a,b)=\gcd(b,a \bmod b)$, and taking $a$ modulo $b$ at least halves $a$. This means this step happens at most $O(\log a) = O(n)$ times.
    
    The first case is always followed by the second case, so the first case happens **no more** often than the second case.
    
    Therefore we get the result after at most $O(n)$ recursive calls.

In fact, if we use the Euclidean algorithm to compute the greatest common divisor of two adjacent terms of the [Fibonacci sequence](../combinatorics/fibonacci.md), the algorithm hits its worst-case complexity.

### Subtraction-based method (Gengxiang Jiansun Shu)

Taking a big integer modulo another is slow, while addition and subtraction are fast. For big integers, we can compute the greatest common divisor using addition and subtraction instead of multiplication and division.

#### How it works

Given two numbers $a$ and $b$, find $\gcd(a,b)$.

Without loss of generality, assume $a \ge b$. If $a = b$, then $\gcd(a,b)=a=b$.
Otherwise, $\forall d\mid a, d\mid b$, we can prove that $d\mid a-b$.

Therefore, **all** common divisors of $a$ and $b$ are common divisors of $a-b$ and $b$, and $\gcd(a,b) = \gcd(a-b, b)$.

#### Optimization: Stein's algorithm

If $a\gg b$, the subtraction method hits its worst-case $O(n)$ complexity.

Here is an optimization: if $2\mid a,2\mid b$, then $\gcd(a,b) = 2\gcd\left(\dfrac a2, \dfrac b2\right)$.

Otherwise, if $2\mid a$ (the case $2\mid b$ is symmetric), then since the case $2\mid b$ has already been handled, we have $2 \nmid b$. Therefore $\gcd(a,b)=\gcd\left(\dfrac a2,b\right)$.

The optimized algorithm (i.e., Stein's algorithm) has time complexity $O(\log n)$.

???+ note "Proof"
    If $2\mid a$ or $2\mid b$, each recursive step halves at least one of $a,b$.
    
    Otherwise, $2\mid a-b$, which brings us back to the previous case.
    
    The algorithm recurses at most $O(\log n)$ times.

#### Implementation

For a big-integer template, see [Arbitrary-Precision Arithmetic](../bignum.md).

The big-integer type needs to support: subtraction, comparison, left shift, right shift (can be replaced by multiplying/dividing by a small integer), and counting trailing zero bits in binary (can be done by brute force by checking parity).

??? note "C++"
    ```cpp
    Big gcd(Big a, Big b) {
      if (a == 0) return b;
      if (b == 0) return a;
      // Count how many factors of 2 a and b share; countr_zero gives the number of trailing zero bits
      int atimes = countr_zero(a);
      int btimes = countr_zero(b);
      int mintimes = min(atimes, btimes);
      a >>= atimes;
      for (;;) {
        // The common factors of 2 in a and b are already counted, so a can never be even from here on
        b >>= btimes;
        // Make sure a <= b
        if (a > b) swap(a, b);
        b -= a;
        if (b == 0) break;
        btimes = countr_zero(b);
      }
      return a << mintimes;
    }
    ```

The code above is based on the C++17 `std::gcd` implementations in [libstdc++](https://github.com/gcc-mirror/gcc/blob/1667962ae755db27965778b8c8c684c6c0c4da21/libstdc%2B%2B-v3/include/std/numeric#L173) and [MSVC](https://github.com/microsoft/STL/blob/9aca22477df4eed3222b4974746ee79129eb44e7/stl/inc/numeric#L591). For values in the range of `unsigned int` and `unsigned long long`, if `countr_zero` can be computed very quickly, Stein's algorithm is faster than the Euclidean algorithm; otherwise it may be slower.

???+ note "About countr_zero"
    1.  gcc has the [built-in functions](../bit.md#gcc-built-in-functions) `__builtin_ctz` (32-bit) and `__builtin_ctzll` (64-bit), which can replace `countr_zero` in the code above;
    2.  Since C++20, the header `<bit>` provides [`std::countr_zero`](https://en.cppreference.com/w/cpp/numeric/countr_zero);
    3.  If you don't want to use non-standard functions and cannot use C++20, the code below is an implementation that runs in $O(1)$ after preprocessing, in the Word-RAM with multiplication model:
    
    ```cpp
    constexpr int loghash[64] = {0,  32, 48, 56, 60, 62, 63, 31, 47, 55, 59, 61, 30,
                                 15, 39, 51, 57, 28, 46, 23, 43, 53, 58, 29, 14, 7,
                                 35, 49, 24, 44, 54, 27, 45, 22, 11, 37, 50, 25, 12,
                                 38, 19, 41, 52, 26, 13, 6,  3,  33, 16, 40, 20, 42,
                                 21, 10, 5,  34, 17, 8,  36, 18, 9,  4,  2,  1};
    
    int countr_zero(unsigned long long x) {
      return loghash[(x & -x) * 0x9150D32D8EB9EFC0Ui64 >> 58];
    }
    ```
    
    For big integers, if they are implemented like a `bitset`, then together with the `countr_zero` implementation above, this can be done in `O(n / w)` time. But if the number cannot easily be split into binary bits, we can only find the largest power-of-$2$ factor by brute force, and the time complexity depends on the implementation. For example:
    
    ```cpp
    // A binary Big stored in little-endian order; we must be able to iterate over every element
    int countr_zero(Big a) {
      int ans = 0;
      for (auto x : a) {
        if (x != 0) {
          ans += 32;  // Bit width of each element's data type
        } else {
          return ans + countr_zero(x);
        }
      }
      return ans;
    }
    
    // Brute force; if you use it, consider inlining it into gcd for a better constant factor
    int countr_zero(Big a) {
      int ans = 0;
      while ((a & 1) == 0) {
        a >>= 1;
        ++ans;
      }
      return ans;
    }
    ```

For more discussion on how fast different `gcd` implementations are, see [Fastest way to compute the greatest common divisor](https://lemire.me/blog/2013/12/26/fastest-way-to-compute-the-greatest-common-divisor/).

### GCD of multiple numbers

How do we compute the greatest common divisor of many numbers? Clearly, the answer must divide every number, so it must also divide every pair of adjacent numbers. By induction, we can prove that repeatedly taking two numbers, computing their gcd, and putting the result back does not change the final answer.

## Least common multiple

Next we show how to compute the least common multiple (LCM).

### Definition

A common multiple of a set of integers is a number that is a multiple of every number in the set. 0 is a common multiple of any set of integers.

The least common multiple of a set of integers is the smallest of all its positive common multiples.

For integers $a,b$, we write their least common multiple as $\operatorname{lcm}(a,b)$. When there is no ambiguity, we can simply write $[a,b]$.

For integers $a_1,\dots,a_n$, we write their least common multiple as $\operatorname{lcm}(a_1,\dots,a_n)$. When there is no ambiguity, we can simply write $[a_1,\dots,a_n]$.

### Two numbers

Let $a = p_1^{k_{a_1}}p_2^{k_{a_2}} \cdots p_s^{k_{a_s}}$, $b = p_1^{k_{b_1}}p_2^{k_{b_2}} \cdots p_s^{k_{b_s}}$.

We see that for $a$ and $b$, their greatest common divisor equals

$p_1^{\min(k_{a_1}, k_{b_1})}p_2^{\min(k_{a_2}, k_{b_2})} \cdots p_s^{\min(k_{a_s}, k_{b_s})}$

and their least common multiple equals

$p_1^{\max(k_{a_1}, k_{b_1})}p_2^{\max(k_{a_2}, k_{b_2})} \cdots p_s^{\max(k_{a_s}, k_{b_s})}$

Since $k_a + k_b = \max(k_a, k_b) + \min(k_a, k_b)$,

we conclude that $\gcd(a, b) \times \operatorname{lcm}(a, b) = a \times b$.

To find the least common multiple of two numbers, just find their greatest common divisor first.

### Multiple numbers

Once we have the $\gcd$ of two numbers, computing their least common multiple takes $O(1)$. So for many numbers, there is no need to find one common greatest common divisor first. The most direct way: just as, when computing the $\gcd$ of many numbers, we put the $\gcd$ of two numbers back into the sequence and continue with the remaining numbers, here we instead put the least common multiple back into the sequence.

## Extended Euclidean algorithm

The extended Euclidean algorithm (EXGCD) is commonly used to find one solution of $ax+by=\gcd(a,b)$.

### How it works

Let

$ax_1+by_1=\gcd(a,b)$

$bx_2+(a\bmod b)y_2=\gcd(b,a\bmod b)$

By the Euclidean theorem, $\gcd(a,b)=\gcd(b,a\bmod b)$.

So $ax_1+by_1=bx_2+(a\bmod b)y_2$.

Also, $a\bmod b=a-(\lfloor\frac{a}{b}\rfloor\times b)$,

so $ax_1+by_1=bx_2+(a-(\lfloor\frac{a}{b}\rfloor\times b))y_2$

$ax_1+by_1=ay_2+bx_2-\lfloor\frac{a}{b}\rfloor\times by_2=ay_2+b(x_2-\lfloor\frac{a}{b}\rfloor y_2)$

Since $a=a,b=b$, we get $x_1=y_2,y_1=x_2-\lfloor\frac{a}{b}\rfloor y_2$.

Keep substituting $x_2,y_2$ recursively until $b$ is $0$, then return $x=1,y=0$ and work back up.

### Implementation

=== "C++"
    ```cpp
    int Exgcd(int a, int b, int &x, int &y) {
      if (!b) {
        x = 1;
        y = 0;
        return a;
      }
      int d = Exgcd(b, a % b, x, y);
      int t = x;
      x = y;
      y = t - (a / b) * y;
      return d;
    }
    ```

=== "Python"
    ```python
    def Exgcd(a, b):
        if b == 0:
            return a, 1, 0
        d, x, y = Exgcd(b, a % b)
        return d, y, x - (a // b) * y
    ```

The function returns the $\gcd$, and computes $x,y$ along the way.

### Range of the values

The equation $ax+by=\gcd(a,b)$ has infinitely many solutions, and clearly some of them overflow long long.  
Fortunately, if $b\not= 0$, the solution found by the extended Euclidean algorithm always satisfies $|x|\le b,|y|\le a$.  
Below is a proof of this property.

??? note "Proof"
    -   When $\gcd(a,b)=b$, we have $a\bmod b=0$, so the recursion stops at the next level.  
        We get $x_1=0,y_1=1$, and clearly $a,b\ge 1\ge |x_1|,|y_1|$.
    -   When $\gcd(a,b)\not= b$, assume $|x_2|\le (a\bmod b),|y_2|\le b$.  
        Since $x_1=y_2,y_1=x_2-{\left\lfloor\dfrac{a}{b}\right\rfloor}y_2$,   
        we have $|x_1|=|y_2|\le b,|y_1|\le|x_2|+|{\left\lfloor\dfrac{a}{b}\right\rfloor}y_2|\le (a\bmod b)+{\left\lfloor\dfrac{a}{b}\right\rfloor}|y_2|$  
        $\le a-{\left\lfloor\dfrac{a}{b}\right\rfloor}b+{\left\lfloor\dfrac{a}{b}\right\rfloor}|y_2|\le a-{\left\lfloor\dfrac{a}{b}\right\rfloor}(b-|y_2|)$   
        $a\bmod b=a-{\left\lfloor\dfrac{a}{b}\right\rfloor}b\le a-{\left\lfloor\dfrac{a}{b}\right\rfloor}(b-|y_2|)\le a$   
        Therefore $|x_1|\le b,|y_1|\le a$ holds.

### Iterative extended Euclidean algorithm

First, when $x = 1$, $y = 0$, $x_1 = 0$, $y_1 = 1$, clearly

$$
\begin{cases}
    ax + by     & = a \\
    ax_1 + by_1 & = b
\end{cases}
$$

holds.

We know $a\bmod b = a - (\lfloor \frac{a}{b} \rfloor \times b)$. Let $q = \lfloor \frac{a}{b} \rfloor$. Following the iterative gcd, each iteration can be written as:

$$
(a, b) \rightarrow (b, a - qb)
$$

Replacing $a$ in the iteration with $ax + by = a$ and $b$ with $ax_1 + by_1 = b$, we get:

$$
\begin{aligned}
                & \begin{cases}
                      ax + by     & = a \\
                      ax_1 + by_1 & = b
                  \end{cases}                    \\
    \rightarrow & \begin{cases}
                      ax_1 + by_1               & = b      \\
                      a(x - qx_1) + b(y - qy_1) & = a - qb
                  \end{cases}
\end{aligned}
$$

This gives the iterative exgcd.

Since the iterative method avoids recursion, the code runs a bit faster than the recursive version.

```cpp
int gcd(int a, int b, int& x, int& y) {
  x = 1, y = 0;
  int x1 = 0, y1 = 1, a1 = a, b1 = b;
  while (b1) {
    int q = a1 / b1;
    tie(x, x1) = make_tuple(x1, x - q * x1);
    tie(y, y1) = make_tuple(y1, y - q * y1);
    tie(a1, b1) = make_tuple(b1, a1 - q * b1);
  }
  return a1;
}
```

If you look closely at $a_1$ and $b_1$, you will see that they take exactly the same values as in the iterative Euclidean algorithm, and the following equations hold at all times (before the while loop and at the end of every iteration): $x \cdot a +y \cdot b =a_1$ and $x_1 \cdot a +y_1 \cdot b= b_1$. Therefore the algorithm correctly computes the $\gcd$.

At the end, $a_1$ is the $\gcd$ we want, and $x \cdot a +y \cdot b = g$.

#### Matrix interpretation

For positive integers $a$ and $b$, one step of the Euclidean algorithm, $\gcd(a,b)=\gcd(b,a\bmod b)$, can be written in matrix form as

$$
\begin{bmatrix}
b\\a\bmod b
\end{bmatrix}
=
\begin{bmatrix}
0&1\\1&-\lfloor a/b\rfloor
\end{bmatrix}
\begin{bmatrix}
a\\b
\end{bmatrix}
$$

Here the floor $\lfloor c\rfloor$ is the largest integer not greater than $c$. We define the transformation $\begin{bmatrix}a\\b\end{bmatrix}\mapsto \begin{bmatrix}0&1\\1&-\lfloor a/b\rfloor\end{bmatrix}\begin{bmatrix}a\\b\end{bmatrix}$.

It is easy to see that the Euclidean algorithm just applies this transformation over and over, so

$$
\begin{bmatrix}
\gcd(a,b)\\0
\end{bmatrix}
=
\left(
\cdots 
\begin{bmatrix}
0&1\\1&-\lfloor a/b\rfloor
\end{bmatrix}
\begin{bmatrix}
1&0\\0&1
\end{bmatrix}
\right)
\begin{bmatrix}
a\\b
\end{bmatrix}
$$

Let

$$
\begin{bmatrix}
x_1&x_2\\x_3&x_4
\end{bmatrix}
=
\cdots 
\begin{bmatrix}
0&1\\1&-\lfloor a/b\rfloor
\end{bmatrix}
\begin{bmatrix}
1&0\\0&1
\end{bmatrix}
$$

Then

$$
\begin{bmatrix}
\gcd(a,b)\\0
\end{bmatrix}
=
\begin{bmatrix}
x_1&x_2\\x_3&x_4
\end{bmatrix}
\begin{bmatrix}
a\\b
\end{bmatrix}
$$

which satisfies $a\cdot x_1+b\cdot x_2=\gcd(a,b)$, i.e., the extended Euclidean algorithm. Note that multiplying by an identity matrix at the end does not change the result. This suggests that we can maintain a $2\times 2$ identity matrix from the start and write a simpler iterative method:

```cpp
int exgcd(int a, int b, int &x, int &y) {
  int x1 = 1, x2 = 0, x3 = 0, x4 = 1;
  while (b != 0) {
    int c = a / b;
    std::tie(x1, x2, x3, x4, a, b) =
        std::make_tuple(x3, x4, x1 - x3 * c, x2 - x4 * c, b, a - b * c);
  }
  x = x1, y = x2;
  return a;
}
```

This formulation is simpler than the recursive one.

## Applications

-   [10104 - Euclid Problem](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1045)
-   [GYM - (J) once upon a time](http://codeforces.com/gym/100963)
-   [UVa - 12775 - Gift Dilemma](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4628)

## References and links

[^1]: [libstdc++: std Namespace Reference](https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.4/a00978.html#a2686a128df5a576cb53a1ed5f674607)
