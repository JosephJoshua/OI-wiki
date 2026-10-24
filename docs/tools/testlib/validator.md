Prerequisites: [General](./general.md)

This page gives a short introduction to the concept and usage of validators.

## Overview

A validator checks whether generated test data is valid. When you have made the tests for a problem but worry that they might be invalid (breaking the problem's constraints: overflow, a disconnected graph, not a tree...), problem setters usually check them with a validator.[^ref1]

Because Codeforces supports hacks, every problem on Codeforces must have a validator. The same goes for UOJ. [Polygon](../polygon.md) has built-in support for validators.

## Usage

Just run `./val` from the command line. The data is read from stdin. To read from a file, use `./val < a.in`.

If the data is fine, nothing is printed and the exit code is 0; otherwise an error message is printed and a nonzero value is returned.

## Tips

-   When writing a validator, you cannot assume anything about the data being validated, because it may contain anything. So the problem setter must check for all kinds of invalid cases (Testlib makes this much simpler).
    -   For example, if the input is a tree with $n$ vertices, the main job is to check that $n$ is in range and that the input is a tree. But never stop checking after you have checked the range of $n$: you must also check the ranges of the endpoints of the edges that follow, or the validator may RE.
    -   Even if it wouldn't RE, you should still check, or your error message will be wrong. In the example above, without the check the error might be "not a tree", but the correct error should be "an edge endpoint is not in $[1,n]$".
-   You cannot assume anything about how contestants read input. So you must make sure that data passing validation matches the input format exactly.
    -   For example, a contestant may read numbers character by character and read exactly one space between numbers. So when writing a validator, every whitespace character in the data (such as spaces and line breaks) must be read explicitly in the validator.
-   Don't forget `inf.readEof()` at the end.
-   If the problem allows hacks (in other words, other people will see the validator's error messages), make the error messages as friendly as possible.
    -   Use "item names" when reading variables.
    -   When the expression being checked is not easy to understand, use ensuref instead of ensure.

## Example

Here is the validator for [CF Gym 100541A - Stock Market](https://codeforces.com/gym/100541/problem/A):

```cpp
#include "testlib.h"

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  int testCount = inf.readInt(1, 10, "testCount");
  inf.readEoln();

  for (int i = 0; i < testCount; i++) {
    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    inf.readInt(1, 1000000, "w");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
      inf.readInt(1, 1000, "p_i");
      if (i < n - 1) inf.readSpace();
    }
    inf.readEoln();
  }

  inf.readEof();
}
```

## External links

-   [More validator examples](https://github.com/MikeMirzayanov/testlib/tree/master/validators)
-   [The GitHub repository of `testlib.h`: MikeMirzayanov/testlib](https://github.com/MikeMirzayanov/testlib)

## References and notes

[^ref1]: [Validators with testlib.h - Codeforces](https://codeforces.com/blog/entry/18426)
