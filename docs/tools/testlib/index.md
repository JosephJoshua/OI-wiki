author: Xeonacid, sshwy

If you are setting a competitive programming problem in C++, Testlib is an excellent helper for writing the related programs (generator, validator, checker, interactor). It is an essential tool for problem setters in Russia and some other countries, and many contests use it: ROI, ICPC regionals, all Codeforces rounds...

The Testlib library is a single file, `testlib.h`. To use it, just add `#include "testlib.h"` at the start of your program.

What Testlib is used for:

-   Writing a [Generator](./generator.md), which generates test data.
-   Writing a [Validator](./validator.md), which checks whether the generated data meets the problem's requirements, such as value ranges and format.
-   Writing an [Interactor](./interactor.md), which interacts with the solution in interactive problems.
-   Writing a [Checker](./checker.md), also known as a [Special Judge](../special-judge.md).

Testlib is fully compatible with [Polygon](https://polygon.codeforces.com/), the problem-setting platform developed by Codeforces.

`testlib.h` was ported from `testlib.pas` in 2005 and has been updated ever since. Testlib is compatible with almost all compilers, such as VC++ and GCC g++, and supports C++11.

**This article is mainly translated from [Testlib - Codeforces](https://codeforces.com/testlib). The GitHub repository of `testlib.h` is [MikeMirzayanov/testlib](https://github.com/MikeMirzayanov/testlib).**
