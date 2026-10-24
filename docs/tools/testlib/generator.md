A generator produces test data. When the data is large and making it by hand would wear you out, a generator creates it for us automatically.

## A simple example

Generate two integers in $[1,n]$:

```cpp
// clang-format off

#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  int n = atoi(argv[1]);
  cout << rnd.next(1, n) << " ";
  cout << rnd.next(1, n) << endl;
}
```

## Why use Testlib?

Some people say you don't need Testlib to write a generator, and that it's useless here. That is actually wrong. A good generator should satisfy this: **for the same input, it gives the same output in any environment**. Writing a generator means generating random values. The tools we usually use, `rand()` or C++11's `mt19937/uniform_int_distribution`, may give different outputs on different operating systems, with different compilers, at different run times, and so on (for the very common `srand(time(nullptr))` this is obvious), which makes test generation non-deterministic.

Note that once you use Testlib, you can no longer use standard library random functions such as `srand()` and `rand()`; otherwise you get a compile error. So, **make sure every random-related function you use comes from Testlib, not from the standard library.**

The random functions in Testlib guarantee that the same calls produce the same values, regardless of the generator itself or the platform. They also make it very convenient to generate random values with all kinds of requirements. For example, `rnd.next("[a-z]{1,10}")` generates a string of length in $[1,10]$ whose characters are `a` to `z`. Handy, isn't it?

## What can Testlib do?

Before anything else, call `registerGen(argc, argv, 1)` to initialize Testlib (where `1` is the version of the generator used; usually keep it as is). Then we can use the `rnd` object to generate random values. The random seed is taken from a hash of the command-line arguments. For a generator `g.cpp`, `g 100`(Unix-Like) and `g.exe "100"`(Windows) produce the same output, while `g 100 0` produces a different one.

The `rnd` object has type `random_t`. You can create a new random generator object, but usually you don't need to.

The object has many useful member functions. Here are some examples:

| Call                                         | Meaning                                                                                                                                                                                                                                                 |
| -------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `rnd.next(4)`                                | Generates an integer in $[0,4)$ uniformly at random                                                                                                                                                                                                     |
| `rnd.next(4, 100)`                           | Generates an integer in $[4,100]$ uniformly at random                                                                                                                                                                                                   |
| `rnd.next(10.0)`                             | Generates a floating-point number in $[0,10.0)$ uniformly at random                                                                                                                                                                                     |
| <code>rnd.next("one \| two \| three")</code> | Returns one of the three strings `one`,`two`,`three` uniformly at random                                                                                                                                                                                |
| `rnd.wnext(4, t)`                            | `wnext()` generates a non-uniform distribution (with a shifted expected value)[^note1]. $t$ is the number of calls to `next()`, and the maximum of the generated values is taken. For example, `rnd.wnext(3, 1)` is the same as `max({rnd.next(3), rnd.next(3)})`; `rnd.wnext(4, 2)` is the same as `max({rnd.next(4), rnd.next(4), rnd.next(4)})`. If $t<0$, it makes $-t$ calls and takes the minimum; if $t=0$, it is the same as `next()`. |
| `rnd.any(container)`                         | Returns a reference to a uniformly random element of a container with random-access iterators (such as `std::vector` and `std::string`)                                                                                                                 |

Appendix: the formal definition of `rnd.wnext(i,t)`:

$$
\operatorname{wnext}(i,t)=
\begin{cases}
\operatorname{next}(i) & t=0 \\
\max(\operatorname{next}(i),\operatorname{wnext}(i,t-1)) & t>0 \\
\min(\operatorname{next}(i),\operatorname{wnext}(i,t+1)) & t<0
\end{cases}
$$

Also, don't use `std::random_shuffle()`; use Testlib's `shuffle()` instead, which also takes a pair of iterators. It shuffles the sequence with `rnd`, so it meets the "good generator" requirement above.

## Example: generating a tree

Below is the main code for generating a tree. It takes two parameters: the number of vertices and the "elongation". For example, with $n=10,t=1000$ it will likely generate a chain; with $n=10,t=-1000$ it will likely generate a star.

```cpp
#define forn(i, n) for (int i = 0; i < int(n); i++)

registerGen(argc, argv, 1);

int n = atoi(argv[1]);
int t = atoi(argv[2]);

vector<int> p(n);

/* Set the parents of vertices 1..n-1 */
forn(i, n) if (i > 0) p[i] = rnd.wnext(i, t);

printf("%d\n", n);

/* Shuffle vertices 1..n-1 */
vector<int> perm(n);
forn(i, n) perm[i] = i;
shuffle(perm.begin() + 1, perm.end());

/* Add edges using the shuffled vertex order */
vector<pair<int, int>> edges;
for (int i = 1; i < n; i++)
  if (rnd.next(2))
    edges.push_back(make_pair(perm[i], perm[p[i]]));
  else
    edges.push_back(make_pair(perm[p[i]], perm[i]));

/* Shuffle the edges */
shuffle(edges.begin(), edges.end());

for (int i = 0; i + 1 < n; i++)
  printf("%d %d\n", edges[i].first + 1, edges[i].second + 1);
```

## Generating many tests at once

Just as without Testlib, redirect the output stream before writing each test. Testlib also provides a helper function `startTest(test_index)`, which redirects the output stream to the file `test_index`.

## Some notes

-   Follow the problem's format strictly, including spaces and line breaks. Note that the file should end with a line break.
-   For large data, prefer `printf` over `cout` for better performance. (Turning off stream synchronization is not recommended when using Testlib.)
-   Don't rely on UB (Undefined Behavior). For instance, in the example at the start of this page, if the output were written as `cout << rnd.next(1, n) << " " << rnd.next(1, n) << endl;`, the order of the `rnd.next()` calls would be undefined.

## New feature: parsing command-line arguments

Previously, we usually wrote code like `int n = atoi(argv[3]);`, but this isn't good, for these reasons:

-   It is unsafe when there is no third command-line argument;
-   The third command-line argument may not be a valid 32-bit integer.

Now you can write: `int n = opt<int>(3)`. You can also use `int64_t m = opt<int64_t>(1);`, `bool t = opt<bool>(2);`, `string s = opt(4);` and so on.

testlib also supports named arguments. With many arguments, something like `g 10 20000 a true` is less readable than `g -n10 -m200000 -t=a -increment`.

In that case, you can now use the following code in your generator:

```cpp
int n = opt<int>("n");
long long n = opt<long long>("m");
string t = opt("t");
bool increment = opt<bool>("increment");
```

You can freely mix reading arguments by index and by name.

The following ways of writing named arguments are supported:

-   `--key=value` or `-key=value`;
-   `--key value` or `-key value`, if `value` is not the start of a new argument (it doesn't start with a hyphen `-`, or one/two hyphens are not followed by a letter);
-   `--k12345` or `-k12345`, if the key `k` is a single letter followed by a number;
-   `-prop` or `--prop`, to enable a bool property.

Here are some examples:

```text
g1 -n1
g2 --len=4 --s=oops
g3 -inc -shuffle -n=5
g4 --length 5 --total 21 -ord
```

## More examples

You can find them on [GitHub](https://github.com/MikeMirzayanov/testlib/tree/master/generators).

**This article is mainly translated from [Генераторы на testlib.h - Codeforces](https://codeforces.com/blog/entry/18291). The new feature section is translated from [Testlib: Opts—parsing command line options](https://codeforces.com/blog/entry/72702). The GitHub repository of `testlib.h` is [MikeMirzayanov/testlib](https://github.com/MikeMirzayanov/testlib).**

[^note1]: In fact, when `i` is a floating-point number, `rnd.wnext(i, t)` follows a [Beta distribution](https://en.wikipedia.org/wiki/Beta_distribution) on $[0,i)$: when $t>0$, it follows $i\cdot \mathrm{Beta}(t+1,1)$; when $t<0$, it follows $i\cdot \mathrm{Beta}(1,t+1)$.
