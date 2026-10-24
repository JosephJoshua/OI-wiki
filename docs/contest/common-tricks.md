author: H-J-Granger, Ir1d, ChungZH, Marcythm, StudyingFather, billchenchina, Suyun514, Psycho7, greyqz, Xeonacid, partychicken

This page lists some small tricks that are useful in contests.

## Using locality

Locality means that a program tends to access data items near other recently accessed data items, or the recently accessed data items themselves. There are two kinds of locality: temporal locality and spatial locality.

For details, see [Loop Unroll](../lang/optimizations.md#loop-unrolling), [Code Layout Optimizations](../lang/optimizations.md#code-layout-optimizations) and similar sections.

## Loop macros

The following code can be simplified with a macro:

```cpp
for (int i = 0; i < N; i++) {
  // loop body omitted
}

// simplified with a macro
#define f(x, y, z) for (int x = (y), __ = (z); x < __; ++x)

// Now a loop can be written simply as `f(i, 0, N)`. For example:
// a is a STL container
f(i, 0, a.size()) { ... }
```

Here is another fairly useful macro:

```cpp
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
```

## Make good use of namespaces

Using namespaces makes a program easier to read and to debug.

??? note "Example problem: NOI 2018 Dragon Slayer"
    ```cpp
    // NOI 2018 Dragon Slayer, partial-credit code for 40 points
    #include <algorithm>
    #include <cmath>
    #include <cstring>
    #include <iostream>
    using namespace std;
    long long n, m, a[100005], p[100005], aw[100005], atk[100005];
    
    namespace one_game {
    // you can also declare variables inside a namespace
    void solve() {
      for (int y = 0;; y++)
        if ((a[1] + p[1] * y) % atk[1] == 0) {
          cout << (a[1] + p[1] * y) / atk[1] << endl;
          return;
        }
    }
    }  // namespace one_game
    
    namespace p_1 {
    void solve() {
      if (atk[1] == 1) {  // solve 1-2
        sort(a + 1, a + n + 1);
        cout << a[n] << endl;
        return;
      } else if (m == 1) {  // solve 3-4
        long long k = atk[1], kt = ceil(a[1] * 1.0 / k);
        for (int i = 2; i <= n; i++)
          k = aw[i - 1], kt = max(kt, (long long)ceil(a[i] * 1.0 / k));
        cout << k << endl;
      }
    }
    }  // namespace p_1
    
    int main() {
      int T;
      cin >> T;
      while (T--) {
        memset(a, 0, sizeof(a));
        memset(p, 0, sizeof(p));
        memset(aw, 0, sizeof(aw));
        memset(atk, 0, sizeof(atk));
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> p[i];
        for (int i = 1; i <= n; i++) cin >> aw[i];
        for (int i = 1; i <= m; i++) cin >> atk[i];
        if (n == 1 && m == 1)
          one_game::solve();  // solve 8-13
        else if (p[1] == 1)
          p_1::solve();  // solve 1-4 or 14-15
        else
          cout << -1 << endl;
      }
      return 0;
    }
    ```

## Debugging with macros

When testing locally, programmers often add debugging statements. Before submitting to the OJ, they have to remove all of them so that the debug output doesn't affect how the judge checks the program's output, which takes a lot of time. In this situation, you can save time by defining a macro. The rough structure looks like this:

```cpp
#define DEBUG
#ifdef DEBUG
// do something when DEBUG is defined
#endif
// or
#ifndef DEBUG
// do something when DEBUG isn't defined
#endif
```

`#ifdef` checks whether the identifier has been defined with `#define` in the program; if it has, the code that follows is used. `#ifndef` uses the code that follows only if the identifier has not been defined.

This way, you just put your debugging code inside `#ifdef DEBUG` and the code you actually submit inside `#ifndef DEBUG`, which makes local testing convenient. When submitting, you only need to comment out the `#define DEBUG` line. You can also skip defining the identifier in the program and instead define `DEBUG` at compile time with the `-DDEBUG` compiler option. Then you don't need to change the program at all when submitting.

Many OJs compile with the `-DONLINE_JUDGE` option. Making good use of this can save you a lot of time.

## Stress testing

Stress testing (comparing against a brute-force solution) is a way to check or debug a program by comparing the outputs of two programs. You compare your program's output with the output of another program to decide whether your program is correct.

Stress testing has to be run many times, so you should automate it with a batch script.

Specifically, stress testing needs a [test data generator](../tools/testlib/generator.md) and the two programs whose outputs you want to compare.

Each time the generator runs, it writes the generated data to the input file. Both programs read that data through redirection and write their output to given files. Finally, the `fc` command on Windows (`diff` on Linux) compares the files to check whether the program is correct. If you find a mistake, you can debug directly with the data that was just generated.

The rough structure of a stress-testing program is as follows:

```cpp
#include <cstdio>
#include <cstdlib>

int main() {
  // For Windows
  // don't use file input/output when stress testing
  // of course, this program can also be rewritten as a batch script
  while (true) {
    system("gen > test.in");  // the generator writes data to the input file
    system("test1.exe < test.in > a.out");  // get the output of program 1
    system("test2.exe < test.in > b.out");  // get the output of program 2
    if (system("fc a.out b.out")) {
      // this line compares the outputs
      // fc returns 0 if the outputs are identical, nonzero if they differ
      system("pause");  // so you can look at the differences
      return 0;
      // the input data is saved in test.in, so you can debug with it directly
    }
  }
}
```

## Memory pools

When allocating memory dynamically, calling `new`/`malloc` frequently costs a lot of time and space, and can even create lots of memory fragmentation that hurts performance. A program that is otherwise correct may get TLE/MLE because of it.

In this case you can use a technique called a "memory pool": before you actually need memory, request a block of a certain size in advance as a reserve. Whenever you need dynamic allocation, just take a piece from that reserve.

In most OI problems, you can work out the maximum amount of memory you will need in advance and allocate it all at once.

Example:

```cpp
// allocate an array of 32-bit signed integers:
int* newarr(int sz) {
  static int pool[MAXN], *allocp = pool;
  return allocp += sz, allocp - sz;
}

// creating a node in a dynamically allocated segment tree:
Node* newnode() {
  static Node pool[MAXN << 1], *allocp = pool - 1;
  return ++allocp;
}
```

## References

[Luogu Daily #86](https://studyingfather.blog.luogu.org/some-coding-tips-for-oiers)

*Introduction to Algorithm Contests: Exercises and Solutions* (Chinese book)
