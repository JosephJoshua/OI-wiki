author: Xeonacid, NachtgeistW, 2014CAIS01, sshwy, Chrogeek, Menci, yzy-1

This page explains how to write a special judge (spj) for several judging tools and OJs.

## Introduction

A **Special Judge** (spj for short, also called a checker) is a program that checks whether an answer is valid when a problem has multiple correct answers.

???+ warning "Warning"
    An spj should also check whether there is extra content at the end of the file, and whether the output format is correct (for example, the problem requires numbers to be separated by a single space, but the contestant used newlines). However, currently only Testlib makes the former easy, and almost nobody deliberately checks the latter.
    
    Watch out for NaN when comparing floating-point numbers. A careless comparison can let a solution get AC just by printing NaN.
    
    When reading the contestant's file, check that the required content was actually read correctly, so the spj doesn't hit a runtime error. (Some OJs treat a runtime error in the spj as a system error.)

???+ note "Note"
    All examples below use C++, with the setting "the difference between the reference answer and the contestant's answer must be less than 1e-3, the file name is num, and each test is worth 10 points".

## Testlib

See also: [Testlib/Introduction](./testlib/index.md), [Testlib/Checker](./testlib/checker.md)

Testlib is a C++ library that helps problem setters write competitive programming problems in C++.

Judging tools/OJs that require Testlib for the spj: Codeforces, Luogu, UOJ, etc.

Judging tools/OJs that can use Testlib for the spj: LibreOJ ([Lyrio](https://github.com/lyrio-dev)), Lemon, Nowcoder, etc.

The modified Testlib needed by SYZOJ 2 is hosted on [pastebin](https://pastebin.com/3GANXMG7)[^1], but this modified version does not change interactive mode. [syzoj/testlib](https://github.com/syzoj/testlib) hosts a Testlib that supports interactive mode on SYZOJ 2.

The modified Testlib needed by Lemon is hosted at [GitHub - GitPinkRabbit/Testlib-for-Lemons](https://github.com/GitPinkRabbit/Testlib-for-Lemons). Note that with this version, you register the checker with `registerLemonChecker()` instead of `registerTestlibCmd()`. This version is based on [matthew99's old version](https://paste.ubuntu.com/p/JsTspHHnmB/) and adds some newer Testlib features. If you use LemonLime, you can use the original Testlib.

The modified Testlib needed by DOMJudge is hosted at [cn-xcpc-tools/testlib-for-domjudge](https://github.com/cn-xcpc-tools/testlib-for-domjudge). This version of Testlib works both as a Special Judge checker and as an interactor for interactive problems.

The modified Testlib needed by Arbiter is hosted at [testlib-for-arbiter](https://github.com/HeRaNO/ChickenRibs/tree/master/testlib-for-arbiter).

For most other judging tools/OJs, you need to adapt Testlib to their spj format and upload testlib.h together with the spj, or put testlib.h in the include directory.

```cpp
#include "testlib.h"
//
#include <cmath>

int main(int argc, char *argv[]) {
  /*
   * inf: input
   * ouf: contestant output
   * ans: reference output
   */
  registerTestlibCmd(argc, argv);

  double pans = ouf.readDouble(), jans = ans.readDouble();

  if (abs(pans - jans) < 1e-3)
    quitf(_ok, "Good job\n");
  else
    quitf(_wa, "Too big or too small, expected %f, found %f\n", jans, pans);
}
```

## Lemon

???+ note "Note"
    Lemon has a ready-made modified [Testlib](#testlib); using Testlib is recommended.
    
    The latest LemonLime supports writing checkers with the original Testlib. If you use LemonLime, using Testlib is recommended.

```cpp
#include <cmath>
#include <cstdio>

int main(int argc, char* argv[]) {
  /*
   * argv[1]: input
   * argv[2]: contestant output
   * argv[3]: reference output
   * argv[4]: score of a single test
   * argv[5]: write the final score (0 ~ argv[4])
   * argv[6]: write the error report
   */
  FILE* fin = fopen(argv[1], "r");
  FILE* fout = fopen(argv[2], "r");
  FILE* fstd = fopen(argv[3], "r");
  FILE* fscore = fopen(argv[5], "w");
  FILE* freport = fopen(argv[6], "w");

  double pans, jans;
  fscanf(fout, "%lf", &pans);
  fscanf(fstd, "%lf", &jans);

  if (abs(pans - jans) < 1e-3) {
    fprintf(fscore, "%s", argv[4]);
    fprintf(freport, "Good job\n");
  } else {
    fprintf(fscore, "%d", 0);
    fprintf(freport, "Too big or too small, expected %f, found %f\n", jans,
            pans);
  }
}
```

## Cena

```cpp
#include <cmath>
#include <cstdio>

int main(int argc, char* argv[]) {
  /*
   * FILENAME.in: input
   * FILENAME.out: contestant output
   * argv[1]: score of a single test
   * argv[2]: reference output
   * score.log: write the final score (0 ~ argv[1])
   * report.log: write the error report
   */
  FILE* fin = fopen("num.in", "r");
  FILE* fout = fopen("num.out", "r");
  FILE* fstd = fopen(argv[2], "r");
  FILE* fscore = fopen("score.log", "w");
  FILE* freport = fopen("report.log", "w");

  double pans, jans;
  fscanf(fout, "%lf", &pans);
  fscanf(fstd, "%lf", &jans);

  if (abs(pans - jans) < 1e-3) {
    fprintf(fscore, "%s", argv[1]);
    fprintf(freport, "Good job\n");
  } else {
    fprintf(fscore, "%d", 0);
    fprintf(freport, "Too big or too small, expected %f, found %f\n", jans,
            pans);
  }
}
```

## CCR

```cpp
#include <cmath>
#include <cstdio>

int main(int argc, char* argv[]) {
  /*
   * stdin: input
   * argv[2]: reference output
   * argv[3]: contestant output
   * stdout:L1: write the final score ratio (0 ~ 1)
   * stdout:L2: write the error report
   */
  FILE* fout = fopen(argv[3], "r");
  FILE* fstd = fopen(argv[2], "r");

  double pans, jans;
  fscanf(fout, "%lf", &pans);
  fscanf(fstd, "%lf", &jans);

  if (abs(pans - jans) < 1e-3) {
    printf("%d\n", 1);
    printf("Good job\n");
  } else {
    printf("%d\n", 0);
    printf("Too big or too small, expected %f, found %f\n", jans, pans);
  }
}
```

## Arbiter

```cpp
#include <cmath>
#include <cstdio>

int main(int argc, char* argv[]) {
  /*
   * argv[1]: input
   * argv[2]: contestant output
   * argv[3]: reference output
   * /tmp/_eval.score:L1: write the error report
   * /tmp/_eval.score:L2: write the final score
   */
  FILE* fout = fopen(argv[2], "r");
  FILE* fstd = fopen(argv[3], "r");
  FILE* fscore = fopen("/tmp/_eval.score", "w");

  double pans, jans;
  fscanf(fout, "%lf", &pans);
  fscanf(fstd, "%lf", &jans);

  if (abs(pans - jans) < 1e-3) {
    fprintf(fscore, "Good job\n");
    fprintf(fscore, "%d", 10);
  } else {
    fprintf(fscore, "Too big or too small, expected %f, found %f\n", jans,
            pans);
    fprintf(fscore, "%d", 0);
  }
}
```

## HUSTOJ

```cpp
#include <cmath>
#include <cstdio>

#define AC 0
#define WA 1

int main(int argc, char* argv[]) {
  /*
   * argv[1]: input
   * argv[2]: reference output
   * argv[3]: contestant output
   * exit code: return the verdict
   */
  FILE* fin = fopen(argv[1], "r");
  FILE* fout = fopen(argv[3], "r");
  FILE* fstd = fopen(argv[2], "r");

  double pans, jans;
  fscanf(fout, "%lf", &pans);
  fscanf(fstd, "%lf", &jans);

  if (abs(pans - jans) < 1e-3)
    return AC;
  else
    return WA;
}
```

## QDUOJ

QDUOJ is a bit more troublesome by comparison. Its problems with an spj have no reference output, so you have to put the reference solution (std) inside the spj and compute the reference output before checking.

```cpp
#include <cmath>
#include <cstdio>

#define AC 0
#define WA 1
#define ERROR -1

double solve(...) {
  // std
}

int main(int argc, char* argv[]) {
  /*
   * argv[1]: input
   * argv[2]: contestant output
   * exit code: return the verdict
   */
  FILE* fin = fopen(argv[1], "r");
  FILE* fout = fopen(argv[2], "r");

  double pans, jans;
  fscanf(fout, "%lf", &pans);

  jans = solve(...);
  if (abs(pans - jans) < 1e-3)
    return AC;
  else
    return WA;
}
```

## HDOJ

HDOJ is basically the same as QDUOJ: you also implement the std in the spj and compare it with the contestant's output. Unlike QDUOJ, however, HDOJ gives the final verdict by comparing the answer file with what the spj prints to standard output. So for the output file, you only need to upload what the spj prints when the answer is correct.

HDOJ requires you to upload a binary compiled on Windows, not the source code.

```cpp
#include <cmath>
#include <cstdio>

double solve(FILE* fin) {
  // std, read input from fin
}

int main(int argc, char* argv[]) {
  /*
   * argv[1]: input
   * stdin: contestant output
   */
  FILE* fin = fopen(argv[1], "r");

  double pans, jans;
  if (scanf("%lf", &pans) != 1) {
    printf("WA\n");
    goto finish;
  }

  jans = solve(fin);
  if (abs(pans - jans) < 1e-3)
    printf("AC\n");
  else
    printf("WA\n");

finish:
  fclose(fin);
  return 0;
}
```

The corresponding answer file is:

```text
AC
```

## SYZOJ 2

???+ note "Note"
    SYZOJ 2 has a ready-made modified [Testlib](#testlib); using Testlib is recommended.
    
    The latest version of LibreOJ is no longer based on SYZOJ but on [Lyrio](https://github.com/lyrio-dev/lyrio). Lyrio supports writing checkers with the original Testlib, which is the more general and recommended approach.

```cpp
#include <cmath>
#include <cstdio>

int main(int argc, char* argv[]) {
  /*
   * in: input
   * user_out: contestant output
   * answer: reference output
   * code: contestant code
   * stdout: write the final score (0 ~ 100)
   * stderr: write the error report
   */
  FILE* fin = fopen("input", "r");
  FILE* fout = fopen("user_out", "r");
  FILE* fstd = fopen("answer", "r");
  FILE* fcode = fopen("code", "r");

  double pans, jans;
  fscanf(fout, "%lf", &pans);
  fscanf(fstd, "%lf", &jans);

  if (abs(pans - jans) < 1e-3) {
    printf("%d", 100);
    fprintf(stderr, "Good job\n");
  } else {
    printf("%d", 0);
    fprintf(stderr, "Too big or too small, expected %f, found %f\n", jans,
            pans);
  }
}
```

## Nowcoder

???+ note "Note"
    Nowcoder has a ready-made modified [Testlib](#testlib); using Testlib is recommended.

See also: [How to set a Special Judge programming problem on Nowcoder (in Chinese)](https://www.nowcoder.com/discuss/84666)

```cpp
#include <cmath>
#include <cstdio>

#define AC 0
#define WA 1

int main(int argc, char* argv[]) {
  /*
   * input: input
   * user_output: contestant output
   * output: reference output
   * exit code: return the verdict
   */
  FILE* fin = fopen("input", "r");
  FILE* fout = fopen("user_output", "r");
  FILE* fstd = fopen("output", "r");

  double pans, jans;
  fscanf(fout, "%lf", &pans);
  fscanf(fstd, "%lf", &jans);

  if (abs(pans - jans) < 1e-3)
    return AC;
  else
    return WA;
}
```

## DOMJudge

???+ note "Note"
    DOMJudge supports an spj written in any language; see the [problemarchive.org output validator format](https://www.problemarchive.org/wiki/index.php/Output_validator).
    
    DOMJudge has a ready-made modified [Testlib](#testlib); using Testlib is recommended.

Documentation on the Testlib used by DOMJudge and on importing Polygon problem packages: <https://github.com/cn-xcpc-tools/testlib-for-domjudge>

DOMJudge's [default validator](https://github.com/Kattis/problemtools/blob/master/support/default_validator/) has built-in floating-point comparison with tolerance; just add `float_tolerance 1e-3` to `validator_flags` in the problem configuration.

```cpp
#include <cmath>
#include <cstdio>

#define AC 42
#define WA 43
char reportfile[50];

int main(int argc, char* argv[]) {
  /*
   * argv[1]: input
   * argv[2]: reference output
   * argv[3]: folder for judge messages
   * stdin: contestant output
   */
  FILE* fin = fopen(argv[1], "r");
  FILE* fstd = fopen(argv[2], "r");
  sprintf(reportfile, "%s/judgemessage.txt", argv[3]);
  FILE* freport = fopen(reportfile, "w");

  double pans, jans;
  scanf("%lf", &pans);
  fscanf(fstd, "%lf", &jans);

  if (abs(pans - jans) < 1e-3) {
    fprintf(freport, "Good job\n");
    return AC;
  } else {
    fprintf(freport, "Too big or too small, expected %f, found %f\n", jans,
            pans);
    return WA;
  }
}
```

You can also write it with the header [validate.h](https://github.com/Kattis/problemtools/blob/master/examples/different/output_validators/different_validator/validate.h) provided by Kattis Problem Tools, to implement more complex features.

## References

[^1]: [LibreOJ now supports testlib checkers! (in Chinese)](https://loj.ac/article/124)
