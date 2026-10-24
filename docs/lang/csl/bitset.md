author: i-Yirannn, Xeonacid, ouuan

## Introduction

`std::bitset` is a fixed-size container in the standard library that stores `0/1` values. Strictly speaking, it is not part of the STL.

??? note "bitset and the STL"
    > The C++ standard library provides some special container classes, the so-called container adapters (stack, queue, priority queue). In addition, a few classes provide a container-like interface (for example, strings, bitsets, and valarrays). All these classes are covered separately.1 Container adapters and bitsets are covered in Chapter 12.
    >
    > The C++ standard library provides not only the containers for the STL framework but also some containers that fit some special needs and provide simple, almost self-explanatory, interfaces. You can group these containers into either the so-called container adapters, which adapt standard STL containers to fit special needs, or a bitset, which is a containers for bits or Boolean values. There are three standard container adapters: stacks, queues, and priority queues. In priority queues, the elements are sorted automatically according to a sorting criterion. Thus, the "next" element of a priority queue is the element with the "highest" value. A bitset is a bitfield with an arbitrary but fixed number of bits. Note that the C++ standard library also provides a special container with a variable size for Boolean values: vector.
    
    (from *The C++ Standard Library, 2nd Edition*)
    
    So `bitset` is not part of the STL, but a "Special Container" in the standard library. In fact, as a container it does not meet the requirements of an STL container. Nor is it an adapter, since it does not rely on another STL container as its underlying implementation.

Memory is addressed by bytes (`byte`), not by bits (`bit`). So a `bool` variable, even though it can only represent `0/1`, still takes 1 byte of memory.

`bitset` uses a fixed optimization so that the eight bits of one byte can each store one `0/1` value.

Compared with a 4-byte `int` variable, when storing only `0/1`, a `bitset` uses only $\frac{1}{32}$ of the space, and computing some kinds of information also takes only $\frac 1{32}$ of the time.

In some cases `bitset` can make a program run faster. Whether it improves the complexity or the constant factor depends on how you look at complexity. The complexity of `bitset` is usually written in one of the following ways (assume the original complexity is $O(n)$):

1.  $O(n)$. This notation treats `bitset` as not improving the complexity at all.
2.  $O(\frac n{32})$. This notation is not very rigorous (constants should not appear in complexity), but it shows that `bitset` can cut the time needed to $\frac 1{32}$.
3.  $O(\frac n w)$, where $w=32$ (the word size of the computer). This notation is fairly widely accepted.
4.  $O(\frac n {\log w})$, where $w$ is the size of an integer variable on the computer.

Also, `vector<bool>`, a specialization of `vector`, stores data the same way as `bitset`. The difference is that it supports allocating space dynamically, while `bitset`, like an ordinary static array, has its size fixed at compile time. However, `bitset` has some handy library functions that are not only convenient but can sometimes use SIMD to reduce the constant factor. Also, some behavior of `vector<bool>` differs from `vector` (for example, for `std::vector<bool> vec`, `&vec[0] + i` is not equal to `&vec[i]`). So `vector<bool>` is generally not used.

## Usage

See [std::bitset - cppreference.com](https://en.cppreference.com/w/cpp/utility/bitset).

### Header

```cpp
#include <bitset>
```

### Specifying the size

```cpp
std::bitset<1000> bs;  // a bitset with 1000 bits
```

### Constructors

-   `bitset()`: every bit is `false`.
-   `bitset(unsigned long val)`: set to the binary form of `val`.
-   `bitset(const string& str)`: set to the $01$ string `str`.

### Operators

-   `operator []`: accesses a specific bit.

-   `operator ==`/`operator !=`: compares whether the contents of two `bitset`s are exactly the same.

-   `operator &`/`operator &=`/`operator |`/`operator |=`/`operator ^`/`operator ^=`/`operator ~`: bitwise AND/OR/XOR/NOT.

    Note: **a `bitset` can only do bitwise operations with another `bitset`**. To do bitwise operations with an integer, first convert the integer to a `bitset`.

-   `operator <<`/`operator >>`/`operator <<=`/`operator >>=`: binary left shift/right shift.

`bitset` also supports C++ stream I/O, which means you can read and print it with `cin/cout`.

### Member functions

-   `count()`: returns the number of `true` bits.
-   `size()`: returns the size of the `bitset`.
-   `test(pos)`: does the same as `at()` in `vector`; its difference from the `[]` operator is bounds checking.
-   `any()`: returns `true` if some bit is `true`, otherwise `false`.
-   `none()`: returns `true` if all bits are `false`, otherwise `false`.
-   `all()`: returns `true` if all bits are `true`, otherwise `false`.
-   1.  `set()`: sets the whole `bitset` to `true`.
    2.  `set(pos, val = true)`: sets one bit to `true`/`false`.
-   1.  `reset()`: sets the whole `bitset` to `false`.
    2.  `reset(pos)`: sets one bit to `false`. Same as `set(pos, false)`.
-   1.  `flip()`: flips every bit. ($0\leftrightarrow1$, equivalent to XOR with a `bitset` of all $1$s.)
    2.  `flip(pos)`: flips one bit.
-   `to_string()`: returns its string representation.
-   `to_ulong()`: returns its `unsigned long` representation (`long` is the same as `int` on NT and 32-bit POSIX systems, and the same as `long long` on 64-bit POSIX).
-   `to_ullong()`: (since **C++11**) returns its `unsigned long long` representation.

In addition, libstdc++ has some fairly useful internal member functions[^bitset1]:

-   `_Find_first()`: returns the index of the first `true` bit in the `bitset`; if there is no `true`, returns the size of the `bitset`.
-   `_Find_next(pos)`: returns the index of the first `true` after `pos` (at an index strictly greater than `pos`); if there is no `true` after `pos`, returns the size of the `bitset`.

## Applications

### [LibreOJ β Round #2 "Greedy Only Passes the Samples"](https://loj.ac/problem/515)

This problem can be solved with DP, and the transition is simple:

$f(i,j)$ means whether the sum of squares of the first $i$ numbers can equal $j$. Then $f(i,j)=\bigvee\limits_{k=a}^bf(i-1,j-k^2)$ (OR them together).

But doing this directly takes $O(n^5)$ time, which (it seems) is too slow.

Notice that `bitset` can speed this up: just shift left and OR the results together:

??? note "Submission: [std::bitset](https://loj.ac/submission/395274)"
    ```cpp
    #include <bitset>
    #include <cstdio>
    #include <iostream>
    
    using namespace std;
    
    constexpr int N = 101;
    
    int n, a[N], b[N];
    bitset<N * N * N> f[N];
    
    int main() {
      int i, j;
    
      cin >> n;
    
      for (i = 1; i <= n; ++i) cin >> a[i] >> b[i];
    
      f[0][0] = 1;
    
      for (i = 1; i <= n; ++i) {
        for (j = a[i]; j <= b[i]; ++j) {
          f[i] |= (f[i - 1] << (j * j));
        }
      }
    
      cout << f[n].count();
    
      return 0;
    }
    ```

Since libstdc++ packs `__CHAR_BIT__ * sizeof(unsigned long)` bits per word[^bitset2], which is $32$ on some platforms, you can write your own `bitset` (it only needs the "shift left then OR" operation) that packs $64$ bits (`__CHAR_BIT__ * sizeof(unsigned long long)`) for a further speedup:

??? note "Submission: [hand-written bitset](https://loj.ac/submission/395619)"
    ```cpp
    #include <cstdio>
    #include <iostream>
    
    using namespace std;
    
    constexpr int N = 101;
    constexpr int W = 64;
    
    struct Bitset {
      unsigned long long a[N * N * N >> 6];
    
      void shiftor(const Bitset &y, int p, int l, int r) {
        int t = p - p / W * W;
        int tt = (t == 0 ? 0 : W - t);
        int to = (r + p) / W;
        int qaq = (p + W - 1) / W;
    
        for (int i = (l + p) / W; i <= to; ++i) {
          if (i - qaq >= 0) a[i] |= y.a[i - qaq] >> tt;
    
          a[i] |= ((y.a[i - qaq + 1] & ((1ull << tt) - 1)) << t);
        }
      }
    } f[N];
    
    int main() {
      int n, a, b, l = 0, r = 0, ans = 0;
    
      scanf("%d", &n);
    
      f[0].a[0] = 1;
    
      for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &a, &b);
    
        for (int j = a; j <= b; ++j) f[i].shiftor(f[i - 1], j * j, l, r);
    
        l += a * a;
        r += b * b;
      }
    
      for (int i = l / W; i <= r / W; ++i)
        ans += __builtin_popcount(f[n].a[i] & 0xffffffffu) +
               __builtin_popcount(f[n].a[i] >> 32);
    
      printf("%d", ans);
    
      return 0;
    }
    ```

Also, brute force with a few pruning tricks passes too:

??? note "Submission: [brute force with a few pruning tricks](https://loj.ac/submission/395673)"
    ```cpp
    #include <cstdio>
    #include <iostream>
    
    using namespace std;
    
    constexpr int N = 101;
    constexpr int W = 64;
    
    bool f[N * N * N];
    
    int main() {
      int n, i, j, k, a, b, l = 0, r = 0, ans = 0;
    
      scanf("%d", &n);
    
      f[0] = true;
    
      for (i = 1; i <= n; ++i) {
        scanf("%d%d", &a, &b);
        l += a * a;
        r += b * b;
    
        for (j = r; j >= l; --j) {
          f[j] = false;
    
          for (k = a; k <= b; ++k) {
            if (j - k * k < l - a * a) break;
    
            if (f[j - k * k]) {
              f[j] = true;
              break;
            }
          }
        }
      }
    
      for (i = l; i <= r; ++i) ans += f[i];
    
      printf("%d", ans);
    
      return 0;
    }
    ```

### [CF1097F Alex and a TV Show](https://codeforces.com/contest/1097/problem/F)

#### Problem summary

You are given $n$ multisets and four kinds of operations:

1.  Set a multiset to a single number.
2.  Set a multiset to the sum (union) of two other multisets.
3.  Set a multiset to the $\gcd$ of one number chosen from each of two other multisets. That is: $A=\{\gcd(x,y)|x\in B,y\in C\}$.
4.  Ask for the count of some number in a multiset, **modulo 2**.

There are $10^5$ multisets, $10^6$ operations, and values up to $7000$.

#### Solution

Seeing "modulo $2$", you can think of maintaining each multiset with a `bitset`.

Then operation $1$ is a direct assignment, operation $2$ is XOR (because we work modulo $2$), and operation $4$ is a direct lookup. But... what about operation $3$?

We can try maintaining, for each multiset, the multiset formed by all divisors of its elements. Then operation $3$ is just a bitwise AND.

We can precompute, for each number in the value range, the `bitset` formed by its divisors. That handles operation $1$. Operation $2$ is still XOR.

The remaining question is how to get the count of a number in a multiset from the multiset of its divisors.

Let the original multiset be $A$ and the multiset of its divisors be $A'$. We want the count of $x$ in $A$. Working it out with [Möbius inversion](../../math/number-theory/mobius.md):

$$
\begin{aligned}&\sum\limits_{i\in A}[\frac i x=1]\\=&\sum\limits_{i\in A}\sum\limits_{d|\frac i x}\mu(d)\\=&\sum\limits_{d\in A',x|d}\mu(\frac d x)\end{aligned}
$$

Since we work modulo $2$, $-1$ and $1$ are the same, so we only need to check whether $\frac d x$ has a square factor. So for each number in the value range, we can precompute a `bitset` of the positions among its multiples whose quotient by it has no square factor. To get the answer, AND the two bitsets and then call `count()`.

This way, each query takes $O(\frac v w)$ time ($v=7000,\,w=32$).

As for the precomputation, $O(v\sqrt v)$ or $O(v^2)$ precomputation is fairly simple. The $\log$ precomputation is shown in the code below; its cost is a harmonic series, so it is $O(v\log v)$.

??? note "Reference code"
    ```cpp
    #include <bitset>
    #include <cctype>
    #include <cmath>
    #include <cstdio>
    #include <iostream>
    
    using namespace std;
    
    int read() {
      int out = 0;
      char c;
      while (!isdigit(c = getchar()));
      for (; isdigit(c); c = getchar()) out = out * 10 + c - '0';
      return out;
    }
    
    constexpr int N = 100005;
    constexpr int M = 1000005;
    constexpr int V = 7005;
    
    bitset<V> pre[V], pre2[V], a[N], mu;
    int n, m, tot;
    char ans[M];
    
    int main() {
      int i, j, x, y, z;
    
      n = read();
      m = read();
    
      mu.set();
      for (i = 2; i * i < V; ++i) {
        for (j = 1; i * i * j < V; ++j) {
          mu[i * i * j] = 0;
        }
      }
      for (i = 1; i < V; ++i) {
        for (j = 1; i * j < V; ++j) {
          pre[i * j][i] = 1;
          pre2[i][i * j] = mu[j];
        }
      }
    
      while (m--) {
        switch (read()) {
          case 1:
            x = read();
            y = read();
            a[x] = pre[y];
            break;
          case 2:
            x = read();
            y = read();
            z = read();
            a[x] = a[y] ^ a[z];
            break;
          case 3:
            x = read();
            y = read();
            z = read();
            a[x] = a[y] & a[z];
            break;
          case 4:
            x = read();
            y = read();
            ans[tot++] = ((a[x] & pre2[y]).count() & 1) + '0';
            break;
        }
      }
    
      printf("%s", ans);
    
      return 0;
    }
    ```

### Combining with the sieve of Eratosthenes

Because `bitset` reads and writes consecutive bits quickly, it is well suited to building prime tables together with the [sieve of Eratosthenes](../../math/number-theory/sieve.md#sieve-of-eratosthenes).

It is also simple to use: just replace the boolean array in the sieve of Eratosthenes with a `bitset`.

??? note "Speed test"
    Tested with [Quick C++ Benchmarks](https://quick-bench.com), using the compiler `GCC 13.2` with flags `-std=c++20 -O2`.
    
    | Algorithm                                                                   | Function name            |
    | --------------------------------------------------------------------------- | ------------------------ |
    | Sieve of Eratosthenes + C-style bool array, sieved primes not stored        | `Eratosthenes_CArray`    |
    | Sieve of Eratosthenes +`vector<bool>`, sieved primes not stored             | `Eratosthenes_vector`    |
    | Sieve of Eratosthenes +`bitset`, sieved primes not stored                   | `Eratosthenes_bitset`    |
    | Sieve of Eratosthenes + C-style bool array, sieved primes stored            | `Eratosthenes_CArray_sp` |
    | Sieve of Eratosthenes +`vector<bool>`, sieved primes stored                 | `Eratosthenes_vector_sp` |
    | Sieve of Eratosthenes +`bitset`, sieved primes stored                       | `Eratosthenes_bitset_sp` |
    | Euler sieve + C-style bool array                                            | `Euler_CArray`           |
    | Euler sieve +`vector<bool>`                                                 | `Euler_vector`           |
    | Euler sieve +`bitset`                                                       | `Euler_bitset`           |
    
    -   When the sieve of Eratosthenes **stores** the sieved primes:
    
        -   [Test results](https://quick-bench.com/q/iQL9FhsZ6PVV81HKABsidRw8hB8) for $N=5 \times 10^7 + 1$:
    
            ![](./images/bitset-5e7sp.png)
        -   [Test results](https://quick-bench.com/q/pwEamEFUW-6nXeXEALRsYPd8FWI) for $N=10^8 + 1$:
    
            ![](./images/bitset-1e8sp.png)
    -   When the sieve of Eratosthenes **does not store** the sieved primes:
    
        -   [Test results](https://quick-bench.com/q/rg2mCUxT02a44w9fWvHtZoNTJyU) for $N=5 \times 10^7 + 1$:
    
            ![](./images/bitset-5e7.png)
        -   [Test results](https://quick-bench.com/q/lusNWxWsR0VXoRBof7uBtqfvJuY) for $N=10^8 + 1$:
    
            ![](./images/bitset-1e8.png)
    
    From the test results we can see:
    
    1.  The sieve of Eratosthenes, with time complexity $O(n \log \log n)$, can even beat the $O(n)$ Euler sieve after being optimized with `bitset` or `vector<bool>`;
    2.  In most cases, using `bitset` or `vector<bool>` with the Euler sieve gives no noticeable speedup;
    3.  `bitset` gives a slightly bigger speedup than `vector<bool>`.

??? note "Reference code"
    Requires [google/benchmark](https://github.com/google/benchmark) to be installed.
    
    ```cpp
    #include <benchmark/benchmark.h>
    #include <bits/stdc++.h>
    using namespace std;
    using u32 = uint32_t;
    using u64 = uint64_t;
    
    #define ERATOSTHENES_STORAGE_PRIME
    #define ENABLE_EULER
    constexpr u32 N = 5e7 + 1;
    
    #ifndef ERATOSTHENES_STORAGE_PRIME
    
    void Eratosthenes_CArray(benchmark::State &state) {
      static bool is_prime[N];
      for (auto _ : state) {
        fill(is_prime, is_prime + N, true);
        is_prime[0] = is_prime[1] = false;
        for (u32 i = 2; (u64)i * i < N; ++i)
          if (is_prime[i])
            for (u32 j = i * i; j < N; j += i) is_prime[j] = false;
        benchmark::DoNotOptimize(0);
      }
    }
    
    BENCHMARK(Eratosthenes_CArray);
    
    void Eratosthenes_vector(benchmark::State &state) {
      static vector<bool> is_prime(N);
      for (auto _ : state) {
        fill(is_prime.begin(), is_prime.end(), true);
        is_prime[0] = is_prime[1] = false;
        for (u32 i = 2; (u64)i * i < N; ++i)
          if (is_prime[i])
            for (u32 j = i * i; j < N; j += i) is_prime[j] = false;
        benchmark::DoNotOptimize(0);
      }
    }
    
    BENCHMARK(Eratosthenes_vector);
    
    void Eratosthenes_bitset(benchmark::State &state) {
      static bitset<N> is_prime;
      for (auto _ : state) {
        is_prime.set();
        is_prime.reset(0);
        is_prime.reset(1);
        for (u32 i = 2; (u64)i * i < N; ++i)
          if (is_prime[i])
            for (u32 j = i * i; j < N; j += i) is_prime.reset(j);
        benchmark::DoNotOptimize(0);
      }
    }
    
    BENCHMARK(Eratosthenes_bitset);
    
    #else
    
    void Eratosthenes_CArray_sp(benchmark::State &state) {
      static bool is_prime[N];
      for (auto _ : state) {
        vector<u32> prime;
        fill(is_prime, is_prime + N, true);
        is_prime[0] = is_prime[1] = false;
        for (u32 i = 2; (u64)i * i < N; ++i)
          if (is_prime[i])
            for (u32 j = i * i; j < N; j += i) is_prime[j] = false;
        for (u32 i = 2; i < N; ++i)
          if (is_prime[i]) prime.push_back(i);
        benchmark::DoNotOptimize(prime);
      }
    }
    
    BENCHMARK(Eratosthenes_CArray_sp);
    
    void Eratosthenes_vector_sp(benchmark::State &state) {
      static vector<bool> is_prime(N);
      for (auto _ : state) {
        vector<u32> prime;
        fill(is_prime.begin(), is_prime.end(), true);
        is_prime[0] = is_prime[1] = false;
        for (u32 i = 2; (u64)i * i < N; ++i)
          if (is_prime[i])
            for (u32 j = i * i; j < N; j += i) is_prime[j] = false;
        for (u32 i = 2; i < N; ++i)
          if (is_prime[i]) prime.push_back(i);
        benchmark::DoNotOptimize(prime);
      }
    }
    
    BENCHMARK(Eratosthenes_vector_sp);
    
    void Eratosthenes_bitset_sp(benchmark::State &state) {
      static bitset<N> is_prime;
      for (auto _ : state) {
        vector<u32> prime;
        is_prime.set();
        is_prime.reset(0);
        is_prime.reset(1);
        for (u32 i = 2; (u64)i * i < N; ++i)
          if (is_prime[i])
            for (u32 j = i * i; j < N; j += i) is_prime.reset(j);
        for (u32 i = 2; i < N; ++i)
          if (is_prime[i]) prime.push_back(i);
        benchmark::DoNotOptimize(prime);
      }
    }
    
    BENCHMARK(Eratosthenes_bitset_sp);
    
    #endif
    
    #ifdef ENABLE_EULER
    
    void Euler_CArray(benchmark::State &state) {
      static bool not_prime[N];
      for (auto _ : state) {
        vector<u32> prime;
        fill(not_prime, not_prime + N, false);
        not_prime[0] = not_prime[1] = true;
        for (u32 i = 2; i < N; ++i) {
          if (!not_prime[i]) prime.push_back(i);
          for (u32 pri_j : prime) {
            if (i * pri_j >= N) break;
            not_prime[i * pri_j] = true;
            if (i % pri_j == 0) break;
          }
        }
        benchmark::DoNotOptimize(prime);
      }
    }
    
    BENCHMARK(Euler_CArray);
    
    void Euler_vector(benchmark::State &state) {
      static vector<bool> not_prime(N);
      for (auto _ : state) {
        vector<u32> prime;
        fill(not_prime.begin(), not_prime.end(), false);
        not_prime[0] = not_prime[1] = true;
        for (u32 i = 2; i < N; ++i) {
          if (!not_prime[i]) prime.push_back(i);
          for (u32 pri_j : prime) {
            if (i * pri_j >= N) break;
            not_prime[i * pri_j] = true;
            if (i % pri_j == 0) break;
          }
        }
        benchmark::DoNotOptimize(prime);
      }
    }
    
    BENCHMARK(Euler_vector);
    
    void Euler_bitset(benchmark::State &state) {
      static bitset<N> not_prime;
      for (auto _ : state) {
        vector<u32> prime;
        not_prime.reset();
        not_prime.set(0);
        not_prime.set(1);
        for (u32 i = 2; i < N; ++i) {
          if (!not_prime[i]) prime.push_back(i);
          for (u32 pri_j : prime) {
            if (i * pri_j >= N) break;
            not_prime.set(i * pri_j);
            if (i % pri_j == 0) break;
          }
        }
        benchmark::DoNotOptimize(prime);
      }
    }
    
    BENCHMARK(Euler_bitset);
    
    #endif
    
    static void Noop(benchmark::State &state) {
      for (auto _ : state) benchmark::DoNotOptimize(0);
    }
    
    BENCHMARK(Noop);
    BENCHMARK_MAIN();
    ```

### Combining with tree blocking

Combining `bitset` with tree blocking solves a class of problems that ask for the union of information over several paths in a tree. See [Data structures/Tree blocking](../../ds/tree-decompose.md).

### Combining with Mo's algorithm

See [Misc/Mo's algorithm with bitset](../../misc/mo-algo-with-bitset.md).

### Computing high-dimensional partial orders

See [FHR's slides](https://github.com/OI-wiki/libs/blob/master/lang/csl/FHR-分块bitset求高维偏序.pdf).

## References and notes

[^bitset1]: [libstdc++: SGI STL extensions](https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.4/a00994.html#g32541eb0d6581b915af48b5a51006dff)

[^bitset2]: [libstdc++: std::bitset<\_Nb> Class Template Reference](https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.4/a00219.html)
